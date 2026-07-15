// frame_client_node
//
// Bridges the TEKNOFEST competition HTTP API (guidebook section 8) to ROS2:
//   1. GET  <server>/frames            -> JSON list of all session frames (Figure 16)
//   2. GET  <image_url>                -> JPEG/PNG frame (one at a time, in order)
//   3. publish t3_interfaces/FrameInfo -> pose_estimator_node
//   4. wait for t3_interfaces/PoseEstimate for that frame
//   5. POST <server>/prediction        -> result JSON (Figure 17)
//
// The competition rule "no next frame without submitting a result for the
// current one" is enforced by this sequential loop.

#include <chrono>
#include <cmath>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <curl/curl.h>
#include <json/json.h>

#include <opencv2/imgcodecs.hpp>
#include <cv_bridge/cv_bridge.h>
#include <rclcpp/rclcpp.hpp>

#include "t3_interfaces/msg/frame_info.hpp"
#include "t3_interfaces/msg/pose_estimate.hpp"

using namespace std::chrono_literals;

namespace
{
size_t curl_write_cb(char * ptr, size_t size, size_t nmemb, void * userdata)
{
  auto * out = static_cast<std::string *>(userdata);
  out->append(ptr, size * nmemb);
  return size * nmemb;
}
}  // namespace

class FrameClientNode : public rclcpp::Node
{
public:
  FrameClientNode()
  : Node("frame_client_node")
  {
    server_url_ = declare_parameter<std::string>("server_url", "http://127.0.0.1:5000");
    frames_endpoint_ = declare_parameter<std::string>("frames_endpoint", "/frames");
    results_endpoint_ = declare_parameter<std::string>("results_endpoint", "/prediction");
    user_url_ = declare_parameter<std::string>("user_url", "http://127.0.0.1:5000/users/1/");
    send_results_ = declare_parameter<bool>("send_results", true);
    fetch_score_ = declare_parameter<bool>("fetch_score", true);
    prediction_timeout_sec_ = declare_parameter<double>("prediction_timeout_sec", 20.0);
    min_frame_period_sec_ = declare_parameter<double>("min_frame_period_sec", 0.0);
    http_retries_ = static_cast<int>(declare_parameter<int64_t>("http_retries", 5));

    // strip trailing '/' so concatenation with endpoints is predictable
    while (!server_url_.empty() && server_url_.back() == '/') {
      server_url_.pop_back();
    }

    frame_pub_ = create_publisher<t3_interfaces::msg::FrameInfo>("/t3/frame_info", 10);
    image_pub_ = create_publisher<sensor_msgs::msg::Image>("/t3/image_raw", 10);
    prediction_sub_ = create_subscription<t3_interfaces::msg::PoseEstimate>(
      "/t3/prediction", 50,
      [this](const t3_interfaces::msg::PoseEstimate::SharedPtr msg) {
        std::lock_guard<std::mutex> lk(pred_mutex_);
        last_prediction_ = *msg;
        pred_cv_.notify_all();
      });

    curl_global_init(CURL_GLOBAL_DEFAULT);
    worker_ = std::thread([this]() { run_session(); });
  }

  ~FrameClientNode() override
  {
    stop_ = true;
    pred_cv_.notify_all();
    if (worker_.joinable()) {
      worker_.join();
    }
    curl_global_cleanup();
  }

private:
  // ---------------------------------------------------------------- HTTP
  bool http_get(const std::string & url, std::string & body, long * code = nullptr)
  {
    CURL * curl = curl_easy_init();
    if (!curl) {return false;}
    body.clear();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (code) {*code = http_code;}
    curl_easy_cleanup(curl);
    return res == CURLE_OK && http_code >= 200 && http_code < 300;
  }

  bool http_post_json(const std::string & url, const std::string & json, std::string & resp)
  {
    CURL * curl = curl_easy_init();
    if (!curl) {return false;}
    resp.clear();
    struct curl_slist * headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(json.size()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    CURLcode res = curl_easy_perform(curl);
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return res == CURLE_OK && http_code >= 200 && http_code < 300;
  }

  bool http_get_retry(const std::string & url, std::string & body)
  {
    for (int attempt = 0; attempt < http_retries_ && !stop_; ++attempt) {
      long code = 0;
      if (http_get(url, body, &code)) {return true;}
      RCLCPP_WARN(
        get_logger(), "GET %s failed (HTTP %ld), attempt %d/%d",
        url.c_str(), code, attempt + 1, http_retries_);
      std::this_thread::sleep_for(500ms);
    }
    return false;
  }

  // ------------------------------------------------------------- helpers
  // translation values arrive either as numbers or as the string "NaN"
  static double parse_translation(const Json::Value & v, bool & valid)
  {
    if (v.isNumeric()) {
      const double d = v.asDouble();
      if (std::isfinite(d)) {
        valid = true;
        return d;
      }
    }
    valid = false;
    return 0.0;
  }

  std::string absolute_url(const std::string & maybe_relative) const
  {
    if (maybe_relative.rfind("http://", 0) == 0 || maybe_relative.rfind("https://", 0) == 0) {
      return maybe_relative;
    }
    if (!maybe_relative.empty() && maybe_relative[0] == '/') {
      return server_url_ + maybe_relative;
    }
    return server_url_ + "/" + maybe_relative;
  }

  // --------------------------------------------------------- session loop
  void run_session()
  {
    // 1. fetch the frame list
    const std::string list_url = server_url_ + frames_endpoint_;
    std::string body;
    RCLCPP_INFO(get_logger(), "Requesting frame list: %s", list_url.c_str());
    if (!http_get_retry(list_url, body)) {
      RCLCPP_FATAL(get_logger(), "Could not fetch the frame list. Is the server running?");
      return;
    }

    Json::Value root;
    Json::CharReaderBuilder rb;
    std::string errs;
    std::istringstream iss(body);
    if (!Json::parseFromStream(rb, iss, &root, &errs) || !root.isArray()) {
      RCLCPP_FATAL(get_logger(), "Frame list is not a JSON array: %s", errs.c_str());
      return;
    }
    const int total = static_cast<int>(root.size());
    RCLCPP_INFO(get_logger(), "Session has %d frames", total);

    int submitted = 0;
    for (int k = 0; k < total && !stop_ && rclcpp::ok(); ++k) {
      const Json::Value & item = root[k];
      const std::string frame_url = item.get("url", "").asString();
      const std::string image_url = absolute_url(item.get("image_url", "").asString());
      const int health = item.get("health_status", 0).asInt();

      bool vx = false, vy = false, vz = false;
      const double tx = parse_translation(item["translation_x"], vx);
      const double ty = parse_translation(item["translation_y"], vy);
      const double tz = parse_translation(item["translation_z"], vz);

      // 2. download and decode the image
      std::string img_bytes;
      if (!http_get_retry(image_url, img_bytes)) {
        RCLCPP_ERROR(get_logger(), "Frame %d: image download failed, skipping", k);
        continue;
      }
      std::vector<uchar> buf(img_bytes.begin(), img_bytes.end());
      cv::Mat img = cv::imdecode(buf, cv::IMREAD_COLOR);
      if (img.empty()) {
        RCLCPP_ERROR(get_logger(), "Frame %d: image decode failed, skipping", k);
        continue;
      }

      // 3. publish FrameInfo (image embedded so estimator needs no sync)
      t3_interfaces::msg::FrameInfo msg;
      msg.header.stamp = now();
      msg.header.frame_id = "camera";
      msg.frame_index = k;
      msg.frame_url = frame_url;
      msg.video_name = item.get("video_name", "").asString();
      msg.session = item.get("session", "").asString();
      msg.ref_x = tx;
      msg.ref_y = ty;
      msg.ref_z = tz;
      msg.ref_valid = vx && vy && vz && health == 1;
      msg.health_status = static_cast<int8_t>(health);
      msg.image = *cv_bridge::CvImage(msg.header, "bgr8", img).toImageMsg();
      image_pub_->publish(msg.image);
      frame_pub_->publish(msg);

      // 4. wait for the estimator's answer for exactly this frame
      t3_interfaces::msg::PoseEstimate pred;
      if (!wait_for_prediction(k, pred)) {
        RCLCPP_WARN(
          get_logger(),
          "Frame %d: no prediction within %.1fs — submitting last known pose",
          k, prediction_timeout_sec_);
        pred.frame_index = k;
        pred.frame_url = frame_url;
        pred.x = last_sent_.x;
        pred.y = last_sent_.y;
        pred.z = last_sent_.z;
      }
      last_sent_ = pred;

      // 5. POST the result (Figure 17 format)
      if (send_results_) {
        if (!post_result(pred, frame_url)) {
          RCLCPP_ERROR(get_logger(), "Frame %d: result POST failed", k);
        } else {
          ++submitted;
        }
      }

      if ((k + 1) % 50 == 0 || k + 1 == total) {
        RCLCPP_INFO(
          get_logger(), "Progress %d/%d  (health=%d  est=[%.2f %.2f %.2f])",
          k + 1, total, health, pred.x, pred.y, pred.z);
      }
      if (min_frame_period_sec_ > 0.0) {
        std::this_thread::sleep_for(
          std::chrono::duration<double>(min_frame_period_sec_));
      }
    }

    RCLCPP_INFO(get_logger(), "Session finished: %d/%d results submitted", submitted, total);

    // rehearsal only: the mock server can score our run (Formula 2)
    if (fetch_score_) {
      std::string score;
      if (http_get(server_url_ + "/score", score)) {
        RCLCPP_INFO(get_logger(), "SCORE: %s", score.c_str());
      }
    }
  }

  bool wait_for_prediction(int frame_index, t3_interfaces::msg::PoseEstimate & out)
  {
    std::unique_lock<std::mutex> lk(pred_mutex_);
    const bool ok = pred_cv_.wait_for(
      lk, std::chrono::duration<double>(prediction_timeout_sec_),
      [this, frame_index]() {
        return stop_ || (last_prediction_ && last_prediction_->frame_index == frame_index);
      });
    if (ok && last_prediction_ && last_prediction_->frame_index == frame_index) {
      out = *last_prediction_;
      return true;
    }
    return false;
  }

  bool post_result(const t3_interfaces::msg::PoseEstimate & pred, const std::string & frame_url)
  {
    Json::Value res;
    res["id"] = next_result_id_++;
    res["user"] = user_url_;
    res["frame"] = frame_url;
    res["detected_objects"] = Json::Value(Json::arrayValue);   // Mission 1, not used here
    Json::Value tr;
    tr["translation_x"] = pred.x;
    tr["translation_y"] = pred.y;
    tr["translation_z"] = pred.z;
    Json::Value translations(Json::arrayValue);
    translations.append(tr);
    res["detected_translations"] = translations;
    res["detected_undefined_objects"] = Json::Value(Json::arrayValue);  // Mission 3

    Json::StreamWriterBuilder wb;
    wb["indentation"] = "";
    const std::string payload = Json::writeString(wb, res);
    std::string resp;
    return http_post_json(server_url_ + results_endpoint_, payload, resp);
  }

  // parameters
  std::string server_url_, frames_endpoint_, results_endpoint_, user_url_;
  bool send_results_{true}, fetch_score_{true};
  double prediction_timeout_sec_{20.0}, min_frame_period_sec_{0.0};
  int http_retries_{5};

  // comms
  rclcpp::Publisher<t3_interfaces::msg::FrameInfo>::SharedPtr frame_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
  rclcpp::Subscription<t3_interfaces::msg::PoseEstimate>::SharedPtr prediction_sub_;

  std::thread worker_;
  std::atomic<bool> stop_{false};
  std::mutex pred_mutex_;
  std::condition_variable pred_cv_;
  std::optional<t3_interfaces::msg::PoseEstimate> last_prediction_;
  t3_interfaces::msg::PoseEstimate last_sent_;
  int next_result_id_{1};
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FrameClientNode>());
  rclcpp::shutdown();
  return 0;
}
