#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to t3_interfaces__msg__FrameInfo
/// One competition frame as received from the server (Figure 16 of the guidebook)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FrameInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,

    /// 0-based index in the session
    pub frame_index: i64,

    /// unique url of the frame ("url" field)
    pub frame_url: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub video_name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session: std::string::String,

    /// translation_x from server (0.0 when invalid)
    pub ref_x: f64,

    /// translation_y from server
    pub ref_y: f64,

    /// translation_z from server
    pub ref_z: f64,

    /// false when server sent "NaN" / health_status == 0
    pub ref_valid: bool,

    /// 1 = position system healthy, 0 = unhealthy
    pub health_status: i8,

    /// the decoded camera frame
    pub image: sensor_msgs::msg::Image,

}



impl Default for FrameInfo {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::FrameInfo::default())
  }
}

impl rosidl_runtime_rs::Message for FrameInfo {
  type RmwMsg = super::msg::rmw::FrameInfo;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        frame_index: msg.frame_index,
        frame_url: msg.frame_url.as_str().into(),
        video_name: msg.video_name.as_str().into(),
        session: msg.session.as_str().into(),
        ref_x: msg.ref_x,
        ref_y: msg.ref_y,
        ref_z: msg.ref_z,
        ref_valid: msg.ref_valid,
        health_status: msg.health_status,
        image: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Owned(msg.image)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      frame_index: msg.frame_index,
        frame_url: msg.frame_url.as_str().into(),
        video_name: msg.video_name.as_str().into(),
        session: msg.session.as_str().into(),
      ref_x: msg.ref_x,
      ref_y: msg.ref_y,
      ref_z: msg.ref_z,
      ref_valid: msg.ref_valid,
      health_status: msg.health_status,
        image: sensor_msgs::msg::Image::into_rmw_message(std::borrow::Cow::Borrowed(&msg.image)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      frame_index: msg.frame_index,
      frame_url: msg.frame_url.to_string(),
      video_name: msg.video_name.to_string(),
      session: msg.session.to_string(),
      ref_x: msg.ref_x,
      ref_y: msg.ref_y,
      ref_z: msg.ref_z,
      ref_valid: msg.ref_valid,
      health_status: msg.health_status,
      image: sensor_msgs::msg::Image::from_rmw_message(msg.image),
    }
  }
}


// Corresponds to t3_interfaces__msg__PoseEstimate
/// Estimated aircraft displacement for one frame (what gets POSTed to the server)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PoseEstimate {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_index: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_url: std::string::String,

    /// metres, relative to first frame of the session
    pub x: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub z: f64,

}



impl Default for PoseEstimate {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PoseEstimate::default())
  }
}

impl rosidl_runtime_rs::Message for PoseEstimate {
  type RmwMsg = super::msg::rmw::PoseEstimate;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        frame_index: msg.frame_index,
        frame_url: msg.frame_url.as_str().into(),
        x: msg.x,
        y: msg.y,
        z: msg.z,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      frame_index: msg.frame_index,
        frame_url: msg.frame_url.as_str().into(),
      x: msg.x,
      y: msg.y,
      z: msg.z,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      frame_index: msg.frame_index,
      frame_url: msg.frame_url.to_string(),
      x: msg.x,
      y: msg.y,
      z: msg.z,
    }
  }
}


