<<<<<<< HEAD
# T3 — TEKNOFEST AI in Aviation: Mission 2 (Position Estimation)

ROS2 (Humble, C++) pipeline for **Mission 2** of the TEKNOFEST 2026
*Artificial Intelligence in Aviation* competition (`guidebook.pdf`, section 2.2):
estimate the aircraft's displacement **x, y, z in metres relative to the first
frame** using only the downward-facing camera, and submit results over the
competition HTTP API. Mission 2 is worth **40 %** of the total score.

## How it works

```
[competition / mock server :5000]  <-- HTTP+JSON, guidebook section 8
        |  GET /frames (Figure 16)   GET image   POST /prediction (Figure 17)
        v
frame_client_node (C++)      one frame at a time, never skips the
        |                     "one result per frame" rule
        |  /t3/frame_info (image + reference translation + health_status)
        v
pose_estimator_node (C++)    monocular visual odometry:
        |                     KLT optical flow -> per-frame similarity
        |                     transform on normalised points -> unscaled
        |                     increments. While health=1 the increments are
        |                     calibrated against the server reference (a 2x2
        |                     matrix A ~ initial-altitude x heading, and a_z
        |                     for z). While health=0 it dead-reckons from the
        |                     last healthy anchor. Frozen frames are detected
        |                     and bridged; blur outliers are gated out.
        |  /t3/prediction  -> back to the client, POSTed to the server
        |  /t3/pose_estimated, /t3/path_estimated, /t3/path_reference,
        |  /t3/debug_image, TF map->base_link
        v
      RViz2 (rviz/t3_mission2.rviz): blue = estimated path,
      magenta = reference path, camera view with tracked features
```

Key insight: a monocular camera cannot recover metric scale, but the
guidebook guarantees the first ~1 minute (450 of 2250 frames) has healthy
reference positions. The estimator fits the scale/heading calibration during
that window and re-anchors to the reference every healthy frame, so drift
only accumulates after `health_status` drops to 0.

## Repository layout

```
T3/
├── guidebook.pdf                     competition technical specification
├── README.md                         this file
├── mock_server/mock_server.py        replica of the competition server
└── ws_t3/                            ROS2 workspace
    └── src/
        ├── t3_interfaces/            FrameInfo.msg, PoseEstimate.msg
        └── t3_pose_estimation/
            ├── src/frame_client_node.cpp
            ├── src/pose_estimator_node.cpp
            ├── launch/mission2.launch.py
            ├── config/params.yaml            all tunables + server URL
            ├── config/camera_synthetic.yaml  intrinsics (swap on comp. day)
            └── rviz/t3_mission2.rviz
```

## Prerequisites

ROS2 Humble plus a few system packages (all already installed on this PC):

```bash
sudo apt install ros-humble-desktop ros-humble-cv-bridge \
     libopencv-dev libcurl4-openssl-dev libjsoncpp-dev \
     python3-numpy python3-pil
```

## Build

```bash
cd ~/Documents/T3/ws_t3
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

## Rehearsal run (exactly like the online competition)

**Terminal 1 — mock server** (renders a synthetic nadir flight with exact
ground truth: takeoff, altitude changes, yaw, blur bursts, frozen frames):

```bash
cd ~/Documents/T3
# quick session: 400 frames, first 150 healthy
python3 mock_server/mock_server.py --frames 400 --healthy 150
# competition-sized session:
python3 mock_server/mock_server.py --frames 2250 --healthy 450
```

**Terminal 2 — pipeline + RViz:**

```bash
cd ~/Documents/T3/ws_t3
source /opt/ros/humble/setup.bash && source install/setup.bash
ros2 launch t3_pose_estimation mission2.launch.py \
    server_url:=http://127.0.0.1:5000
```

In RViz you'll see the magenta reference path and the blue estimated path on
top of each other; when `health_status` drops to 0 the magenta line stops and
the blue line continues on visual odometry alone.

**Score (Formula 2 of the guidebook)** — printed automatically by the client
when the session ends, or any time via:

```bash
curl http://127.0.0.1:5000/score
```

Per-frame errors are written to `score_details.csv` next to the rendered
frames. To watch slowly, add `min_frame_period_sec: 0.2` in `params.yaml`.

Using your own flight video instead of the synthetic world:

```bash
# extract frames first:  ffmpeg -i flight.mp4 -vf fps=7.5 frames/f_%06d.jpg
python3 mock_server/mock_server.py --mode images --images-dir frames \
    [--truth truth.csv]      # CSV: frame,x,y,z  (without it: no scoring)
```

## Competition-day checklist (guidebook sections 3 & 8)

1. Connect via **ethernet** (the venue network has no internet). Your laptop
   needs a working ethernet port. The server address is announced before the
   test session.
2. Put the announced values into `config/params.yaml`:
   - `server_url` (e.g. `http://127.0.0.25:5000`)
   - `user_url` (your team's user URL)
   - endpoints if they differ from `/frames` and `/prediction`
3. Put the **shared camera intrinsics** into a copy of
   `config/camera_synthetic.yaml` and launch with
   `calib_file:=/path/to/it`. (If intrinsics are missing, the node falls
   back to an FOV guess — x/y stay correct because the calibration matrix A
   absorbs focal-length error, but distortion correction is lost.)
4. Set `fetch_score: false` (the real server has no `/score` endpoint).
5. Launch: `ros2 launch t3_pose_estimation mission2.launch.py
   server_url:=http://<announced>`.
6. Rules already handled by the client: one result per frame, submitted
   before the next frame is requested; only the first result per frame
   counts; while `health_status = 1` the reference position itself is
   submitted (allowed by the guidebook, gives zero error on those frames).
7. Test session (75 min, 900-frame video) is for verifying exactly this
   loop — run it unchanged.

## Measured performance (synthetic rehearsals)

| Metric (Formula 2)                    | 400 frames / 80 unhealthy | 2250 frames / 1191 unhealthy |
|---------------------------------------|---------------------------|------------------------------|
| Average error, all frames             | 0.023 m                   | 1.09 m                       |
| Average error, dead-reckoning frames  | 0.111 m                   | 2.06 m                       |
| Maximum error                         | 0.218 m                   | 3.90 m                       |
| Results submitted                     | 400/400                   | 2250/2250                    |

The 2250-frame session dead-reckons for ~53 % of the flight (minutes-long
outage windows), which is why its error is larger.

Real imagery will be harder than the synthetic world (parallax from 3D
structure, moving vehicles, sea/forest textures), so expect larger numbers —
but the architecture (calibrate-while-healthy, re-anchor, robust gating) is
what keeps the error bounded.

## Machine-learning upgrade path

The guidebook explicitly allows learning-based systems (2.2.1). Ranked by
practicality for this codebase:

1. **Learned feature matching (recommended first step).** Replace
   GFTT + KLT inside `pose_estimator_node` with SuperPoint + LightGlue
   exported to ONNX (run from C++ with ONNX Runtime). The geometry and
   calibration stay identical; you gain robustness to night/thermal/snow/sea
   frames the classical tracker struggles with. Pretrained weights work —
   no training data needed.
2. **Learned drift corrector.** During the healthy minute, train a small
   regressor online on the residual between VO increments and the reference;
   apply it during dead-reckoning. Cheap, fits the existing structure.
3. **Learned monocular depth** (e.g. Depth Anything, ONNX) to stabilise the
   altitude channel over non-planar terrain.
4. **End-to-end learned VO** (TartanVO-style). Highest ceiling, but silent
   failure modes and needs training data matching the competition footage —
   risky as the primary system; keep the classical pipeline as fallback.

For Missions 1 and 3 (object detection, image matching) a YOLO-family
detector and a foundation-model matcher (e.g. LightGlue/OmniGlue) are the
natural companions; the `frame_client_node` already sends the
`detected_objects` / `detected_undefined_objects` arrays (empty for now), so
those models can be added without touching the transport layer.
=======
# T3_M2
>>>>>>> 4fd078d29665c024292e94d7d38af69ff7233932
