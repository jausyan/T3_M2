#!/usr/bin/env python3
"""Mock TEKNOFEST 'AI in Aviation' competition server (guidebook section 8).

Replicates the real competition API so the ROS2 pipeline can rehearse
against the exact same input it will see in the online round:

    GET  /frames        JSON list of session frames (Figure 16 format)
    GET  /media/<jpg>   one video frame (served only in order: you must POST a
                        result for frame k before you may download frame k+1)
    POST /prediction    result JSON (Figure 17 format) - stores your estimate
    GET  /score         Mission 2 average error (Formula 2) for what you sent

Modes:
  synthetic (default)  renders a nadir flight over a generated world with
                       exact ground truth: takeoff, cruise, altitude changes,
                       yaw, blur bursts and frozen frames (as per guidebook).
  images               serves your own frames (--images-dir), optionally with
                       --truth CSV (frame,x,y,z). Without truth: health=1 and
                       translations 0.0 for all frames (pipeline smoke test
                       only, no scoring).

Only needs python3 + numpy + Pillow (no Flask, no cv2).

Example (quick rehearsal, 600 frames of which 200 healthy):
    python3 mock_server.py --frames 600 --healthy 200
Competition-sized session:
    python3 mock_server.py --frames 2250 --healthy 450
"""
import argparse
import csv
import io
import json
import math
import os
import re
import sys
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

import numpy as np
from PIL import Image, ImageDraw, ImageFilter

# --------------------------------------------------------------------------
# synthetic world + flight
# --------------------------------------------------------------------------

def build_texture(size, ppm, rng):
    """Aerial-looking ground texture: fields, roads, buildings."""
    small = (rng.random((size // 64, size // 64, 3)) * 60 + 60).astype(np.uint8)
    base = np.array(
        Image.fromarray(small).resize((size, size), Image.BILINEAR), dtype=np.uint8)
    # green/brown tint
    base[..., 1] = np.clip(base[..., 1].astype(int) + 40, 0, 255).astype(np.uint8)
    img = Image.fromarray(base)
    d = ImageDraw.Draw(img)

    # field patches
    for _ in range(140):
        x0, y0 = rng.integers(0, size, 2)
        w, h = rng.integers(120, 900, 2)
        tone = rng.integers(0, 4)
        col = [(90, 120, 60), (140, 130, 90), (70, 100, 55), (160, 150, 120)][tone]
        jit = int(rng.integers(-15, 15))
        col = tuple(int(np.clip(c + jit, 0, 255)) for c in col)
        d.rectangle([int(x0), int(y0), int(x0 + w), int(y0 + h)], fill=col)

    # road grid + diagonals (strong straight features help but also test VO)
    road_col = (72, 72, 74)
    step = int(150 * ppm)
    for x in range(step // 2, size, step):
        d.line([(x, 0), (x, size)], fill=road_col, width=int(6 * ppm))
    for y in range(step // 2, size, step):
        d.line([(0, y), (size, y)], fill=road_col, width=int(6 * ppm))
    for _ in range(6):
        x0, y0, x1, y1 = rng.integers(0, size, 4)
        d.line([(int(x0), int(y0)), (int(x1), int(y1))],
               fill=(80, 78, 76), width=int(5 * ppm))

    # buildings with a shadow
    for _ in range(500):
        x0, y0 = rng.integers(0, size, 2)
        w, h = rng.integers(int(6 * ppm), int(30 * ppm), 2)
        d.rectangle([int(x0 + 4), int(y0 + 4), int(x0 + w + 4), int(y0 + h + 4)],
                    fill=(40, 40, 42))
        g = int(rng.integers(120, 220))
        d.rectangle([int(x0), int(y0), int(x0 + w), int(y0 + h)], fill=(g, g - 10, g - 20))

    # cars: small bright rectangles
    for _ in range(1500):
        x0, y0 = rng.integers(0, size, 2)
        col = tuple(int(c) for c in rng.integers(60, 255, 3))
        d.rectangle([int(x0), int(y0), int(x0 + 2 * ppm), int(y0 + 4 * ppm)], fill=col)

    tex = np.asarray(img, dtype=np.uint8).copy()
    noise = rng.integers(-8, 8, tex.shape, dtype=np.int16)
    return np.clip(tex.astype(np.int16) + noise, 0, 255).astype(np.uint8)


def build_trajectory(n_frames, fps, rng, half_extent):
    """Smooth 3D flight: x,y waypoint cruise + takeoff and altitude changes."""
    n_wp = max(4, n_frames // 150)
    wps = rng.uniform(-half_extent, half_extent, size=(n_wp, 2))
    wps[0] = (0.0, 0.0)

    # resample the polyline to a constant cruise speed
    speed = rng.uniform(8.0, 12.0)                # m/s
    step = speed / fps
    pts = [wps[0]]
    for a, b in zip(wps[:-1], wps[1:]):
        dist = float(np.linalg.norm(b - a))
        for t in np.arange(step, dist, step):
            pts.append(a + (b - a) * t / dist)
    while len(pts) < n_frames:
        pts.append(pts[-1] + (rng.random(2) - 0.5))
    xy = np.array(pts[:n_frames])

    # smooth (also makes the start gentle)
    k = 25
    ker = np.ones(k) / k
    xy = np.stack([np.convolve(np.pad(c, (k, k), mode='edge'), ker, 'same')[k:-k]
                   for c in xy.T], axis=1)
    xy -= xy[0]                                    # displacement starts at 0
    xy = np.clip(xy, -half_extent, half_extent)

    # altitude: takeoff ramp then slow sinusoid
    t = np.arange(n_frames)
    z0, cruise = 25.0, 55.0
    ramp = np.clip(t / (8.0 * fps), 0, 1)          # 8 s climb
    alt = z0 + (cruise - z0) * ramp \
        + 10.0 * np.sin(t / (40.0 * fps) * 2 * math.pi) * ramp \
        + 4.0 * np.sin(t / (13.0 * fps) * 2 * math.pi + 1.0) * ramp

    yaw = 0.35 * np.sin(t / (55.0 * fps) * 2 * math.pi) \
        + 0.15 * np.sin(t / (17.0 * fps) * 2 * math.pi + 2.0)
    return xy, alt, yaw


def render_frames(args, outdir):
    """Render the synthetic session. Returns (names, truth, health)."""
    rng = np.random.default_rng(args.seed)
    ppm = 8.0
    size = 6000
    half_world = size / (2 * ppm)                  # 375 m
    W, H, f = args.width, args.height, args.focal
    max_alt = 95.0
    margin = max_alt / f * math.hypot(W / 2, H / 2) + 10
    half_extent = half_world - margin

    print(f"[mock] building world texture ({size}x{size}) ...", flush=True)
    tex = build_texture(size, ppm, rng)
    xy, alt, yaw = build_trajectory(args.frames, args.fps, rng, half_extent)

    # normalised pixel grids (constant)
    nx = (np.arange(W) - W / 2.0) / f
    ny = (np.arange(H) - H / 2.0) / f
    NX, NY = np.meshgrid(nx, ny)

    # distortion schedule (guidebook 2.1: blur + frozen/repeated frames)
    blur_frames, freeze_frames = set(), set()
    for _ in range(max(1, args.frames // 300)):
        s = int(rng.integers(args.healthy, max(args.healthy + 1, args.frames - 20)))
        blur_frames.update(range(s, min(s + 12, args.frames)))
    for _ in range(max(1, args.frames // 400)):
        s = int(rng.integers(args.healthy, max(args.healthy + 1, args.frames - 10)))
        freeze_frames.update(range(s, min(s + 4, args.frames)))

    names, truth = [], []
    prev_jpg = None
    print(f"[mock] rendering {args.frames} frames to {outdir} ...", flush=True)
    for k in range(args.frames):
        x, y = xy[k]
        Z, psi = float(alt[k]), float(yaw[k])
        c, s = math.cos(psi), math.sin(psi)
        GX = Z * (c * NX - s * NY) + x
        GY = Z * (s * NX + c * NY) + y
        TX = np.clip((GX + half_world) * ppm, 0, size - 1).astype(np.int32)
        TY = np.clip((GY + half_world) * ppm, 0, size - 1).astype(np.int32)
        frame = tex[TY, TX]

        name = f"frame_{k:06d}.jpg"
        path = os.path.join(outdir, name)
        if k in freeze_frames and prev_jpg is not None:
            with open(path, 'wb') as fh:
                fh.write(prev_jpg)                 # exact repeat of previous frame
        else:
            im = Image.fromarray(frame)
            if k in blur_frames:
                im = im.filter(ImageFilter.GaussianBlur(2.5))
            buf = io.BytesIO()
            im.save(buf, 'JPEG', quality=85)
            prev_jpg = buf.getvalue()
            with open(path, 'wb') as fh:
                fh.write(prev_jpg)

        names.append(name)
        truth.append((float(x), float(y), float(Z - alt[0])))
        if (k + 1) % 200 == 0 or k + 1 == args.frames:
            print(f"[mock]   {k + 1}/{args.frames}", flush=True)

    health = make_health(args, rng)
    return names, truth, health


def make_health(args, rng):
    """health_status per frame: healthy window first, then unhealthy windows
    at unknown times (guidebook 2.2.2)."""
    health = [1] * args.frames
    rest = args.frames - args.healthy
    if rest <= 0:
        return health
    n_windows = 1 if rest < 300 else 2
    cursor = args.healthy + int(rng.integers(5, max(6, rest // 10)))
    for _ in range(n_windows):
        length = int(rest * rng.uniform(0.25, 0.45))
        for k in range(cursor, min(cursor + length, args.frames)):
            health[k] = 0
        cursor += length + int(rng.integers(20, 120))
        if cursor >= args.frames:
            break
    return health


def load_images_mode(args):
    exts = ('.jpg', '.jpeg', '.png', '.bmp')
    names = sorted(f for f in os.listdir(args.images_dir)
                   if f.lower().endswith(exts))
    if not names:
        sys.exit(f"[mock] no images found in {args.images_dir}")
    truth, scoring = None, False
    if args.truth:
        tr = {}
        with open(args.truth) as fh:
            for row in csv.reader(fh):
                if not row or not row[0].strip().lstrip('-').isdigit():
                    continue
                tr[int(row[0])] = (float(row[1]), float(row[2]), float(row[3]))
        truth = [tr.get(k, (0.0, 0.0, 0.0)) for k in range(len(names))]
        scoring = True
    else:
        truth = [(0.0, 0.0, 0.0)] * len(names)
        print("[mock] images mode without --truth: health=1 everywhere, scoring disabled")
    args.frames = len(names)
    args.healthy = min(args.healthy, args.frames)
    rng = np.random.default_rng(args.seed)
    health = make_health(args, rng) if scoring else [1] * len(names)
    return names, truth, health, scoring


# --------------------------------------------------------------------------
# HTTP server
# --------------------------------------------------------------------------

class State:
    def __init__(self):
        self.names = []
        self.truth = []
        self.health = []
        self.media_dir = ""
        self.base_url = ""
        self.video_name = "synthetic_V1"
        self.enforce = True
        self.scoring = True
        self.lock = threading.Lock()
        self.predictions = {}       # frame index -> (x, y, z)

    def frames_json(self):
        out = []
        for k, name in enumerate(self.names):
            healthy = self.health[k] == 1
            tx, ty, tz = self.truth[k]
            out.append({
                "url": f"{self.base_url}/frames/{k}/",
                "image_url": f"/media/{name}",
                "video_name": self.video_name,
                "session": f"{self.base_url}/session/1/",
                "translation_x": round(tx, 3) if healthy else "NaN",
                "translation_y": round(ty, 3) if healthy else "NaN",
                "translation_z": round(tz, 3) if healthy else "NaN",
                "health_status": self.health[k],
            })
        return out

    def next_needed(self):
        """First frame index that still has no prediction."""
        k = 0
        while k in self.predictions:
            k += 1
        return k

    def score(self):
        errs, missing = [], 0
        rows = []
        for k in range(len(self.names)):
            gt = self.truth[k]
            if k in self.predictions:
                p = self.predictions[k]
                e = math.dist(p, gt)
                errs.append((k, e))
                rows.append((k, self.health[k], *gt, *p, e))
            else:
                missing += 1
        if not errs:
            return {"error": "no predictions received yet"}
        all_e = [e for _, e in errs]
        unhealthy_e = [e for k, e in errs if self.health[k] == 0]
        with open(os.path.join(self.media_dir, "score_details.csv"), "w") as fh:
            w = csv.writer(fh)
            w.writerow(["frame", "health", "gt_x", "gt_y", "gt_z",
                        "est_x", "est_y", "est_z", "error_m"])
            w.writerows(rows)
        return {
            "formula2_average_error_m": round(sum(all_e) / len(all_e), 3),
            "unhealthy_only_average_error_m":
                round(sum(unhealthy_e) / len(unhealthy_e), 3) if unhealthy_e else 0.0,
            "max_error_m": round(max(all_e), 3),
            "frames_scored": len(all_e),
            "frames_missing": missing,
            "unhealthy_frames": self.health.count(0),
            "details_csv": os.path.join(self.media_dir, "score_details.csv"),
        }


STATE = State()


class Handler(BaseHTTPRequestHandler):
    def log_message(self, fmt, *a):     # quieter default log
        pass

    def _send(self, code, body, ctype="application/json"):
        data = body if isinstance(body, bytes) else json.dumps(body).encode()
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

    def do_GET(self):
        if self.path.rstrip("/") == "/frames" or self.path.rstrip("/") == "":
            if self.path.rstrip("/") == "":
                self._send(200, {"endpoints": ["/frames", "/media/<jpg>",
                                               "POST /prediction", "/score"]})
                return
            self._send(200, STATE.frames_json())
        elif self.path.startswith("/media/"):
            name = os.path.basename(self.path)
            try:
                k = STATE.names.index(name)
            except ValueError:
                self._send(404, {"error": "unknown frame"})
                return
            with STATE.lock:
                allowed = (not STATE.enforce) or k <= STATE.next_needed()
            if not allowed:
                self._send(403, {"error":
                    "competition rule: submit a result for the previous frame first"})
                return
            try:
                with open(os.path.join(STATE.media_dir, name), "rb") as fh:
                    self._send(200, fh.read(), "image/jpeg")
            except OSError:
                self._send(404, {"error": "file missing"})
        elif self.path.rstrip("/") == "/score":
            if not STATE.scoring:
                self._send(200, {"error": "scoring disabled (no ground truth)"})
                return
            with STATE.lock:
                self._send(200, STATE.score())
        else:
            self._send(404, {"error": "not found"})

    def do_POST(self):
        if self.path.rstrip("/") != "/prediction":
            self._send(404, {"error": "not found"})
            return
        try:
            n = int(self.headers.get("Content-Length", 0))
            body = json.loads(self.rfile.read(n))
        except (ValueError, json.JSONDecodeError):
            self._send(400, {"error": "invalid JSON"})
            return
        m = re.search(r"/frames/(\d+)/?", str(body.get("frame", "")))
        if not m:
            self._send(400, {"error": "missing/invalid 'frame' url"})
            return
        k = int(m.group(1))
        try:
            tr = body["detected_translations"][0]
            p = (float(tr["translation_x"]), float(tr["translation_y"]),
                 float(tr["translation_z"]))
        except (KeyError, IndexError, TypeError, ValueError):
            self._send(400, {"error": "missing detected_translations[0]"})
            return
        with STATE.lock:
            if k in STATE.predictions:
                # guidebook: only the FIRST result per frame is evaluated
                self._send(200, {"status": "duplicate ignored", "frame": k})
                return
            STATE.predictions[k] = p
        self._send(201, {"status": "ok", "frame": k})


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--port", type=int, default=5000)
    ap.add_argument("--host", default="127.0.0.1")
    ap.add_argument("--mode", choices=["synthetic", "images"], default="synthetic")
    ap.add_argument("--frames", type=int, default=600,
                    help="session length (competition: 2250)")
    ap.add_argument("--healthy", type=int, default=200,
                    help="guaranteed-healthy prefix (competition: 450)")
    ap.add_argument("--fps", type=float, default=7.5)
    ap.add_argument("--width", type=int, default=1280)
    ap.add_argument("--height", type=int, default=720)
    ap.add_argument("--focal", type=float, default=800.0,
                    help="must match config/camera_synthetic.yaml")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--outdir", default="t3_mock_frames")
    ap.add_argument("--images-dir", help="images mode: directory with frames")
    ap.add_argument("--truth", help="images mode: CSV frame,x,y,z ground truth")
    ap.add_argument("--no-enforce", action="store_true",
                    help="do not enforce the one-result-per-frame ordering rule")
    args = ap.parse_args()

    STATE.base_url = f"http://{args.host}:{args.port}"
    STATE.enforce = not args.no_enforce

    if args.mode == "images":
        if not args.images_dir:
            sys.exit("--mode images requires --images-dir")
        STATE.media_dir = os.path.abspath(args.images_dir)
        STATE.video_name = os.path.basename(STATE.media_dir)
        names, truth, health, scoring = load_images_mode(args)
        STATE.scoring = scoring
    else:
        STATE.media_dir = os.path.abspath(args.outdir)
        os.makedirs(STATE.media_dir, exist_ok=True)
        names, truth, health = render_frames(args, STATE.media_dir)
        with open(os.path.join(STATE.media_dir, "truth.csv"), "w") as fh:
            w = csv.writer(fh)
            w.writerow(["frame", "x", "y", "z", "health"])
            for k, (t, h) in enumerate(zip(truth, health)):
                w.writerow([k, *[round(v, 3) for v in t], h])

    STATE.names, STATE.truth, STATE.health = names, truth, health

    print(f"[mock] {len(names)} frames | healthy prefix: {args.healthy} | "
          f"unhealthy frames: {health.count(0)}")
    print(f"[mock] serving on {STATE.base_url}   (frames list: {STATE.base_url}/frames)")
    print(f"[mock] score after a run: {STATE.base_url}/score")
    ThreadingHTTPServer((args.host, args.port), Handler).serve_forever()


if __name__ == "__main__":
    main()
