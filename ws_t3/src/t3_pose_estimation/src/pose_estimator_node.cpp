// pose_estimator_node
//
// Mission 2 (guidebook 2.2): estimate aircraft displacement x,y,z in metres
// relative to the first frame, from the downward-facing camera only.
//
// Method (monocular VO, self-calibrating against the healthy window):
//   * KLT optical flow between consecutive frames on GFTT corners.
//   * Per-frame similarity transform (scale s, rotation dth, translation t)
//     on undistorted/normalised points: valid model for a near-nadir camera
//     over locally planar ground.
//   * Integrate an UNSCALED increment u_k = -r_k * R(-Th_k) * t_k where
//     r_k = r_{k-1}/s_k is altitude relative to the first frame and Th_k the
//     accumulated image rotation. Altitude increment v_k = r_k - r_{k-1}.
//     (Exact for a planar scene and a nadir camera; the unknown initial
//     altitude, heading offset and axis handedness are absorbed below.)
//   * While health_status == 1 the server provides reference positions
//     (first ~450 frames): fit a constant 2x2 matrix A with d_k ~= A u_k and
//     a scalar a_z with dz_k ~= a_z v_k by linear least squares. The output
//     pose is re-anchored to the reference every healthy frame.
//   * While health_status == 0: dead-reckon pose += A u_k from the last
//     anchor.
//
// Robustness (the guidebook promises blur, frozen and repeated frames):
//   * frozen frames are detected and only EXTRAPOLATED (constant velocity,
//     nothing committed); the next real measurement spans the whole gap and
//     is committed once.
//   * calibration samples are gated: no gap-spanning pairs, enough RANSAC
//     inliers, and |d|/|u| must agree with the running median ratio. One
//     bad sample would otherwise bias A quadratically.
//   * A is used in full (absorbs handedness + heading) only when the healthy
//     motion excites both axes; otherwise a similarity fit (scale+rotation,
//     mirrored or not) from the same sums is used.

#include <array>
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/transform_broadcaster.h>

#include "t3_interfaces/msg/frame_info.hpp"
#include "t3_interfaces/msg/pose_estimate.hpp"

class PoseEstimatorNode : public rclcpp::Node
{
public:
  PoseEstimatorNode()
  : Node("pose_estimator_node")
  {
    calib_file_ = declare_parameter<std::string>("calib_file", "");
    fallback_fov_deg_ = declare_parameter<double>("fallback_fov_deg", 66.0);
    max_features_ = static_cast<int>(declare_parameter<int64_t>("max_features", 600));
    min_tracked_ = static_cast<int>(declare_parameter<int64_t>("min_tracked", 25));
    refresh_below_ = static_cast<int>(declare_parameter<int64_t>("refresh_below", 200));
    gftt_quality_ = declare_parameter<double>("gftt_quality", 0.01);
    gftt_min_dist_ = declare_parameter<double>("gftt_min_dist", 12.0);
    ransac_px_ = declare_parameter<double>("ransac_px", 3.0);
    freeze_diff_thresh_ = declare_parameter<double>("freeze_diff_thresh", 0.35);
    max_step_m_ = declare_parameter<double>("max_step_m", 15.0);
    min_full_samples_ = static_cast<int>(declare_parameter<int64_t>("min_full_samples", 40));
    min_sim_samples_ = static_cast<int>(declare_parameter<int64_t>("min_sim_samples", 15));
    cond_ratio_ = declare_parameter<double>("cond_ratio", 0.05);
    min_inlier_frac_ = declare_parameter<double>("min_inlier_frac", 0.5);
    min_u_for_calib_ = declare_parameter<double>("min_u_for_calib", 0.005);

    frame_sub_ = create_subscription<t3_interfaces::msg::FrameInfo>(
      "/t3/frame_info", 10,
      std::bind(&PoseEstimatorNode::on_frame, this, std::placeholders::_1));

    prediction_pub_ = create_publisher<t3_interfaces::msg::PoseEstimate>("/t3/prediction", 10);
    pose_pub_ = create_publisher<geometry_msgs::msg::PoseStamped>("/t3/pose_estimated", 10);
    path_est_pub_ = create_publisher<nav_msgs::msg::Path>("/t3/path_estimated", 10);
    path_ref_pub_ = create_publisher<nav_msgs::msg::Path>("/t3/path_reference", 10);
    debug_pub_ = create_publisher<sensor_msgs::msg::Image>("/t3/debug_image", 10);
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    path_est_.header.frame_id = "map";
    path_ref_.header.frame_id = "map";

    load_calibration();
    RCLCPP_INFO(get_logger(), "pose_estimator_node ready");
  }

private:
  enum class Increment { MEASURED, FROZEN, FAILED };

  // ------------------------------------------------------------ calibration
  void load_calibration()
  {
    if (!calib_file_.empty()) {
      cv::FileStorage fs(calib_file_, cv::FileStorage::READ);
      if (fs.isOpened()) {
        fs["camera_matrix"] >> K_;
        fs["distortion_coefficients"] >> D_;
        if (!K_.empty()) {
          K_.convertTo(K_, CV_64F);
          if (!D_.empty()) {D_.convertTo(D_, CV_64F);}
          have_K_ = true;
          RCLCPP_INFO(
            get_logger(), "Camera intrinsics loaded from %s (fx=%.1f)",
            calib_file_.c_str(), K_.at<double>(0, 0));
          return;
        }
      }
      RCLCPP_WARN(get_logger(), "Could not read calib file '%s'", calib_file_.c_str());
    }
    RCLCPP_WARN(
      get_logger(),
      "No intrinsics: will assume %.0f deg horizontal FOV from first image "
      "(the fitted matrix A absorbs focal-length error for x/y, so this is safe)",
      fallback_fov_deg_);
  }

  void ensure_intrinsics(const cv::Mat & img)
  {
    if (have_K_) {return;}
    const double w = img.cols, h = img.rows;
    const double f = 0.5 * w / std::tan(0.5 * fallback_fov_deg_ * CV_PI / 180.0);
    K_ = (cv::Mat_<double>(3, 3) << f, 0, w / 2.0, 0, f, h / 2.0, 0, 0, 1);
    D_ = cv::Mat::zeros(1, 5, CV_64F);
    have_K_ = true;
  }

  // --------------------------------------------------------------- pipeline
  void on_frame(const t3_interfaces::msg::FrameInfo::SharedPtr msg)
  {
    cv_bridge::CvImageConstPtr cv_img;
    try {
      cv_img = cv_bridge::toCvShare(msg->image, msg, "bgr8");
    } catch (const std::exception & e) {
      RCLCPP_ERROR(get_logger(), "cv_bridge: %s", e.what());
      return;
    }
    cv::Mat gray;
    cv::cvtColor(cv_img->image, gray, cv::COLOR_BGR2GRAY);
    ensure_intrinsics(gray);

    std::string mode = "INIT";
    int tracked = 0, inliers = 0;
    std::vector<cv::Point2f> p_prev_vis, p_cur_vis;
    // extra displacement shown/sent on top of the committed pose_ (frozen
    // frames only: extrapolated, never committed)
    double extrap[3] = {0, 0, 0};

    if (!prev_gray_.empty()) {
      const Increment inc =
        compute_increment(gray, tracked, inliers, p_prev_vis, p_cur_vis);

      switch (inc) {
        case Increment::MEASURED: {
          mode = "VO";
          const int span = frozen_streak_ + 1;  // frames of true motion covered
          frozen_streak_ = 0;

          // calibration: only clean single-frame pairs while healthy
          if (msg->ref_valid && prev_ref_valid_ && span == 1 &&
            inliers >= static_cast<int>(min_inlier_frac_ * tracked))
          {
            accumulate_calibration(
              msg->ref_x - prev_ref_[0], msg->ref_y - prev_ref_[1],
              msg->ref_z - prev_ref_[2]);
          }

          if (!msg->ref_valid) {
            commit_step(u_[0], u_[1], v_, span);
          }
          last_u_[0] = u_[0] / span;   // per-frame velocity for extrapolation
          last_u_[1] = u_[1] / span;
          last_v_ = v_ / span;
          break;
        }
        case Increment::FROZEN: {
          // identical image: the NEXT real measurement will span this gap,
          // so only extrapolate the prediction, commit nothing.
          mode = "FROZEN";
          ++frozen_streak_;
          if (!msg->ref_valid && have_fit()) {
            const int n = frozen_streak_;
            extrap[0] = (A_[0][0] * last_u_[0] + A_[0][1] * last_u_[1]) * n;
            extrap[1] = (A_[1][0] * last_u_[0] + A_[1][1] * last_u_[1]) * n;
            extrap[2] = az_ * last_v_ * n;
          }
          break;
        }
        case Increment::FAILED: {
          // motion between the previous and this image is lost for good
          // (e.g. heavy blur): commit a constant-velocity guess for the
          // whole unmeasured span.
          mode = "CV-FALLBACK";
          const int span = frozen_streak_ + 1;
          frozen_streak_ = 0;
          if (!msg->ref_valid) {
            commit_step(last_u_[0] * span, last_u_[1] * span, last_v_ * span, span);
          }
          break;
        }
      }

      if (msg->ref_valid) {
        // while the server position is healthy, trust it completely
        pose_[0] = msg->ref_x;
        pose_[1] = msg->ref_y;
        pose_[2] = msg->ref_z;
        frozen_streak_ = 0;
        mode += "+ANCHOR";
      }
    } else if (msg->ref_valid) {
      pose_[0] = msg->ref_x;
      pose_[1] = msg->ref_y;
      pose_[2] = msg->ref_z;
    }

    if (msg->frame_index % 50 == 0) {
      RCLCPP_INFO(
        get_logger(),
        "dbg #%ld %s r=%.3f th=%.1fdeg fit=%s A=[%.2f %.2f; %.2f %.2f] az=%.2f n=%d",
        static_cast<long>(msg->frame_index), mode.c_str(), r_,
        theta_ * 180.0 / CV_PI, fit_name_.c_str(),
        A_[0][0], A_[0][1], A_[1][0], A_[1][1], az_, calib_samples_);
    }

    prev_gray_ = gray.clone();
    prev_ref_valid_ = msg->ref_valid;
    prev_ref_[0] = msg->ref_x;
    prev_ref_[1] = msg->ref_y;
    prev_ref_[2] = msg->ref_z;

    publish_outputs(*msg, mode, tracked, inliers, cv_img->image, p_prev_vis, p_cur_vis, extrap);
  }

  void commit_step(double ux, double uy, double v, int span)
  {
    if (!have_fit()) {return;}   // nothing to scale with yet: hold pose
    double sx = A_[0][0] * ux + A_[0][1] * uy;
    double sy = A_[1][0] * ux + A_[1][1] * uy;
    double sz = az_ * v;
    const double lim = max_step_m_ * span;
    const double n = std::hypot(sx, sy);
    if (n > lim) {
      sx *= lim / n;
      sy *= lim / n;
    }
    sz = std::clamp(sz, -lim, lim);
    pose_[0] += sx;
    pose_[1] += sy;
    pose_[2] += sz;
  }

  // Estimate the unscaled increment (u_, v_) between prev_gray_ and gray.
  Increment compute_increment(
    const cv::Mat & gray, int & tracked, int & inliers,
    std::vector<cv::Point2f> & p_prev_vis, std::vector<cv::Point2f> & p_cur_vis)
  {
    // frozen / repeated frame detection (guidebook 2.1: repeats & freezes)
    const double mean_diff = cv::norm(gray, prev_gray_, cv::NORM_L1) /
      static_cast<double>(gray.total());
    if (mean_diff < freeze_diff_thresh_) {
      return Increment::FROZEN;
    }

    if (static_cast<int>(prev_pts_.size()) < refresh_below_) {
      cv::goodFeaturesToTrack(
        prev_gray_, prev_pts_, max_features_, gftt_quality_, gftt_min_dist_);
    }
    if (static_cast<int>(prev_pts_.size()) < min_tracked_) {
      return Increment::FAILED;
    }

    std::vector<cv::Point2f> cur_pts;
    std::vector<uchar> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(
      prev_gray_, gray, prev_pts_, cur_pts, status, err,
      cv::Size(21, 21), 3,
      cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01));

    std::vector<cv::Point2f> p0, p1;
    for (size_t i = 0; i < status.size(); ++i) {
      if (status[i]) {
        p0.push_back(prev_pts_[i]);
        p1.push_back(cur_pts[i]);
      }
    }
    tracked = static_cast<int>(p0.size());
    prev_pts_ = p1;  // tracked points seed the next frame
    if (tracked < min_tracked_) {
      prev_pts_.clear();
      return Increment::FAILED;
    }
    p_prev_vis = p0;
    p_cur_vis = p1;

    // normalised (undistorted) coordinates
    std::vector<cv::Point2f> n0, n1;
    cv::undistortPoints(p0, n0, K_, D_);
    cv::undistortPoints(p1, n1, K_, D_);

    const double f_mean = 0.5 * (K_.at<double>(0, 0) + K_.at<double>(1, 1));
    std::vector<uchar> inlier_mask;
    cv::Mat M = cv::estimateAffinePartial2D(
      n0, n1, inlier_mask, cv::RANSAC, ransac_px_ / f_mean, 3000, 0.995);
    if (M.empty()) {
      return Increment::FAILED;
    }
    inliers = cv::countNonZero(inlier_mask);
    if (inliers < min_tracked_) {
      return Increment::FAILED;
    }

    const double a = M.at<double>(0, 0), b = M.at<double>(1, 0);
    const double tx = M.at<double>(0, 2), ty = M.at<double>(1, 2);
    const double s = std::hypot(a, b);
    if (s < 0.5 || s > 2.0) {
      return Increment::FAILED;  // absurd altitude jump between two frames
    }
    const double dth = std::atan2(b, a);

    // integrate rotation and relative altitude
    theta_ += dth;
    const double r_new = r_ / s;
    v_ = r_new - r_;
    r_ = r_new;

    // u = -r * R(-theta) * t   (derivation in header comment)
    const double c = std::cos(-theta_), sn = std::sin(-theta_);
    u_[0] = -r_ * (c * tx - sn * ty);
    u_[1] = -r_ * (sn * tx + c * ty);
    return Increment::MEASURED;
  }

  // ----------------------------------------------------- scale calibration
  void accumulate_calibration(double dx, double dy, double dz)
  {
    const double un = std::hypot(u_[0], u_[1]);
    if (un < min_u_for_calib_) {return;}   // too little motion: only noise

    // ratio gate: |d|/|u| must agree with the running median (rejects blur
    // outliers and any leftover gap-spanning samples)
    const double dn = std::hypot(dx, dy);
    const double q = dn / un;
    if (ratios_.size() >= 15) {
      std::vector<double> tmp = ratios_;
      std::nth_element(tmp.begin(), tmp.begin() + tmp.size() / 2, tmp.end());
      const double med = tmp[tmp.size() / 2];
      if (med > 1e-9 && (q < 0.6 * med || q > 1.6 * med)) {
        return;
      }
    }
    if (ratios_.size() < 450) {ratios_.push_back(q);}

    Suu_[0][0] += u_[0] * u_[0]; Suu_[0][1] += u_[0] * u_[1];
    Suu_[1][0] += u_[1] * u_[0]; Suu_[1][1] += u_[1] * u_[1];
    Sdu_[0][0] += dx * u_[0];    Sdu_[0][1] += dx * u_[1];
    Sdu_[1][0] += dy * u_[0];    Sdu_[1][1] += dy * u_[1];
    Sdd_ += dx * dx + dy * dy;
    Svv_ += v_ * v_;
    Szv_ += dz * v_;
    ++calib_samples_;
    solve_calibration();
  }

  void solve_calibration()
  {
    if (calib_samples_ < min_sim_samples_) {return;}
    if (Svv_ > 1e-12) {
      az_ = Szv_ / Svv_;
    }

    // excitation check on Suu (eigenvalues of the 2x2 symmetric matrix)
    const double tr = Suu_[0][0] + Suu_[1][1];
    const double det = Suu_[0][0] * Suu_[1][1] - Suu_[0][1] * Suu_[1][0];
    const double disc = std::sqrt(std::max(0.0, tr * tr - 4.0 * det));
    const double lmin = 0.5 * (tr - disc), lmax = 0.5 * (tr + disc);

    if (calib_samples_ >= min_full_samples_ && lmax > 0.0 && lmin > cond_ratio_ * lmax) {
      // full unconstrained A = Sdu * Suu^-1 (absorbs heading + handedness
      // + any residual axis scaling)
      const double ridge = 1e-9 + 1e-6 * tr;
      const double m00 = Suu_[0][0] + ridge, m01 = Suu_[0][1];
      const double m10 = Suu_[1][0], m11 = Suu_[1][1] + ridge;
      const double d2 = m00 * m11 - m01 * m10;
      if (std::abs(d2) < 1e-18) {return;}
      const double i00 = m11 / d2, i01 = -m01 / d2;
      const double i10 = -m10 / d2, i11 = m00 / d2;
      A_[0][0] = Sdu_[0][0] * i00 + Sdu_[0][1] * i10;
      A_[0][1] = Sdu_[0][0] * i01 + Sdu_[0][1] * i11;
      A_[1][0] = Sdu_[1][0] * i00 + Sdu_[1][1] * i10;
      A_[1][1] = Sdu_[1][0] * i01 + Sdu_[1][1] * i11;
      fit_name_ = "full";
    } else if (tr > 1e-12) {
      // similarity (Procrustes) fit from the same sums: s*R(th), direct or
      // mirrored, whichever explains the data better. Works even when the
      // healthy motion is nearly one-dimensional.
      const double dot_r = Sdu_[0][0] + Sdu_[1][1];   // sum u . d
      const double crs_r = Sdu_[1][0] - Sdu_[0][1];   // sum u x d
      const double dot_m = Sdu_[0][0] - Sdu_[1][1];   // mirrored u' = (ux,-uy)
      const double crs_m = Sdu_[1][0] + Sdu_[0][1];
      const double gain_r = dot_r * dot_r + crs_r * crs_r;
      const double gain_m = dot_m * dot_m + crs_m * crs_m;
      if (gain_m > gain_r) {
        const double sc = std::sqrt(gain_m) / tr;
        const double th = std::atan2(crs_m, dot_m);
        const double c = std::cos(th), s = std::sin(th);
        A_[0][0] = sc * c;  A_[0][1] = sc * s;
        A_[1][0] = sc * s;  A_[1][1] = -sc * c;
      } else {
        const double sc = std::sqrt(gain_r) / tr;
        const double th = std::atan2(crs_r, dot_r);
        const double c = std::cos(th), s = std::sin(th);
        A_[0][0] = sc * c;  A_[0][1] = -sc * s;
        A_[1][0] = sc * s;  A_[1][1] = sc * c;
      }
      fit_name_ = "sim";
    } else {
      return;
    }

    if (!announced_) {
      announced_ = true;
      RCLCPP_INFO(
        get_logger(),
        "Scale calibration active (%s fit, %d samples): A=[%.2f %.2f; %.2f %.2f] "
        "a_z=%.2f (|A| ~ initial altitude in metres)",
        fit_name_.c_str(), calib_samples_, A_[0][0], A_[0][1], A_[1][0], A_[1][1], az_);
    }
  }

  bool have_fit() const {return fit_name_ != "none";}

  // ----------------------------------------------------------------- output
  void publish_outputs(
    const t3_interfaces::msg::FrameInfo & msg, const std::string & mode,
    int tracked, int inliers, const cv::Mat & bgr,
    const std::vector<cv::Point2f> & p0, const std::vector<cv::Point2f> & p1,
    const double extrap[3])
  {
    const double out[3] = {
      pose_[0] + extrap[0], pose_[1] + extrap[1], pose_[2] + extrap[2]};

    // prediction back to the client (this is what gets POSTed to the server)
    t3_interfaces::msg::PoseEstimate pred;
    pred.header = msg.header;
    pred.frame_index = msg.frame_index;
    pred.frame_url = msg.frame_url;
    pred.x = out[0];
    pred.y = out[1];
    pred.z = out[2];
    prediction_pub_->publish(pred);

    // RViz: pose + paths + TF
    geometry_msgs::msg::PoseStamped ps;
    ps.header.stamp = msg.header.stamp;
    ps.header.frame_id = "map";
    ps.pose.position.x = out[0];
    ps.pose.position.y = out[1];
    ps.pose.position.z = out[2];
    ps.pose.orientation.w = 1.0;
    pose_pub_->publish(ps);

    path_est_.header.stamp = ps.header.stamp;
    path_est_.poses.push_back(ps);
    path_est_pub_->publish(path_est_);

    if (msg.ref_valid) {
      geometry_msgs::msg::PoseStamped rp = ps;
      rp.pose.position.x = msg.ref_x;
      rp.pose.position.y = msg.ref_y;
      rp.pose.position.z = msg.ref_z;
      path_ref_.header.stamp = ps.header.stamp;
      path_ref_.poses.push_back(rp);
      path_ref_pub_->publish(path_ref_);
    }

    geometry_msgs::msg::TransformStamped tf;
    tf.header.stamp = ps.header.stamp;
    tf.header.frame_id = "map";
    tf.child_frame_id = "base_link";
    tf.transform.translation.x = out[0];
    tf.transform.translation.y = out[1];
    tf.transform.translation.z = out[2];
    tf.transform.rotation.w = 1.0;
    tf_broadcaster_->sendTransform(tf);

    // debug image with tracks + status text
    cv::Mat dbg = bgr.clone();
    for (size_t i = 0; i < p0.size(); ++i) {
      cv::line(dbg, p0[i], p1[i], cv::Scalar(0, 220, 0), 1, cv::LINE_AA);
      cv::circle(dbg, p1[i], 2, cv::Scalar(0, 120, 255), -1, cv::LINE_AA);
    }
    char text[256];
    std::snprintf(
      text, sizeof(text), "#%ld  %s  health=%d  trk=%d inl=%d",
      static_cast<long>(msg.frame_index), mode.c_str(), msg.health_status, tracked, inliers);
    cv::putText(
      dbg, text, {12, 28}, cv::FONT_HERSHEY_SIMPLEX, 0.7, {0, 0, 0}, 4, cv::LINE_AA);
    cv::putText(
      dbg, text, {12, 28}, cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 255, 255}, 1, cv::LINE_AA);
    std::snprintf(
      text, sizeof(text), "est x=%.1f y=%.1f z=%.1f m  fit=%s",
      out[0], out[1], out[2], fit_name_.c_str());
    cv::putText(
      dbg, text, {12, 56}, cv::FONT_HERSHEY_SIMPLEX, 0.7, {0, 0, 0}, 4, cv::LINE_AA);
    cv::putText(
      dbg, text, {12, 56}, cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 255, 255}, 1, cv::LINE_AA);
    debug_pub_->publish(*cv_bridge::CvImage(msg.header, "bgr8", dbg).toImageMsg());
  }

  // parameters
  std::string calib_file_;
  double fallback_fov_deg_, gftt_quality_, gftt_min_dist_, ransac_px_;
  double freeze_diff_thresh_, max_step_m_, cond_ratio_, min_inlier_frac_, min_u_for_calib_;
  int max_features_, min_tracked_, refresh_below_, min_full_samples_, min_sim_samples_;

  // camera
  cv::Mat K_, D_;
  bool have_K_{false};

  // VO state
  cv::Mat prev_gray_;
  std::vector<cv::Point2f> prev_pts_;
  double theta_{0.0};                   // accumulated image rotation [rad]
  double r_{1.0};                       // altitude relative to first frame (Z/Z0)
  std::array<double, 2> u_{0, 0};       // current unscaled planar increment
  double v_{0.0};                       // current unscaled altitude increment
  std::array<double, 2> last_u_{0, 0};  // per-frame velocity for extrapolation
  double last_v_{0.0};
  int frozen_streak_{0};

  // calibration  d ~= A u,  dz ~= a_z v
  double Suu_[2][2]{{0, 0}, {0, 0}}, Sdu_[2][2]{{0, 0}, {0, 0}};
  double Sdd_{0.0}, Svv_{0.0}, Szv_{0.0};
  double A_[2][2]{{0, 0}, {0, 0}}, az_{0.0};
  std::vector<double> ratios_;
  int calib_samples_{0};
  std::string fit_name_{"none"};
  bool announced_{false};

  // pose output (committed state)
  double pose_[3]{0, 0, 0};
  bool prev_ref_valid_{false};
  double prev_ref_[3]{0, 0, 0};

  nav_msgs::msg::Path path_est_, path_ref_;

  rclcpp::Subscription<t3_interfaces::msg::FrameInfo>::SharedPtr frame_sub_;
  rclcpp::Publisher<t3_interfaces::msg::PoseEstimate>::SharedPtr prediction_pub_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_pub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_est_pub_, path_ref_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr debug_pub_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PoseEstimatorNode>());
  rclcpp::shutdown();
  return 0;
}
