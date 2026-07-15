#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "t3_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__t3_interfaces__msg__FrameInfo() -> *const std::ffi::c_void;
}

#[link(name = "t3_interfaces__rosidl_generator_c")]
extern "C" {
    fn t3_interfaces__msg__FrameInfo__init(msg: *mut FrameInfo) -> bool;
    fn t3_interfaces__msg__FrameInfo__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<FrameInfo>, size: usize) -> bool;
    fn t3_interfaces__msg__FrameInfo__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<FrameInfo>);
    fn t3_interfaces__msg__FrameInfo__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<FrameInfo>, out_seq: *mut rosidl_runtime_rs::Sequence<FrameInfo>) -> bool;
}

// Corresponds to t3_interfaces__msg__FrameInfo
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// One competition frame as received from the server (Figure 16 of the guidebook)

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct FrameInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,

    /// 0-based index in the session
    pub frame_index: i64,

    /// unique url of the frame ("url" field)
    pub frame_url: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub video_name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub session: rosidl_runtime_rs::String,

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
    pub image: sensor_msgs::msg::rmw::Image,

}



impl Default for FrameInfo {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !t3_interfaces__msg__FrameInfo__init(&mut msg as *mut _) {
        panic!("Call to t3_interfaces__msg__FrameInfo__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for FrameInfo {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { t3_interfaces__msg__FrameInfo__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { t3_interfaces__msg__FrameInfo__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { t3_interfaces__msg__FrameInfo__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for FrameInfo {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for FrameInfo where Self: Sized {
  const TYPE_NAME: &'static str = "t3_interfaces/msg/FrameInfo";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__t3_interfaces__msg__FrameInfo() }
  }
}


#[link(name = "t3_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__t3_interfaces__msg__PoseEstimate() -> *const std::ffi::c_void;
}

#[link(name = "t3_interfaces__rosidl_generator_c")]
extern "C" {
    fn t3_interfaces__msg__PoseEstimate__init(msg: *mut PoseEstimate) -> bool;
    fn t3_interfaces__msg__PoseEstimate__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PoseEstimate>, size: usize) -> bool;
    fn t3_interfaces__msg__PoseEstimate__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PoseEstimate>);
    fn t3_interfaces__msg__PoseEstimate__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PoseEstimate>, out_seq: *mut rosidl_runtime_rs::Sequence<PoseEstimate>) -> bool;
}

// Corresponds to t3_interfaces__msg__PoseEstimate
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Estimated aircraft displacement for one frame (what gets POSTed to the server)

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PoseEstimate {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_index: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub frame_url: rosidl_runtime_rs::String,

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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !t3_interfaces__msg__PoseEstimate__init(&mut msg as *mut _) {
        panic!("Call to t3_interfaces__msg__PoseEstimate__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PoseEstimate {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { t3_interfaces__msg__PoseEstimate__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { t3_interfaces__msg__PoseEstimate__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { t3_interfaces__msg__PoseEstimate__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PoseEstimate {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PoseEstimate where Self: Sized {
  const TYPE_NAME: &'static str = "t3_interfaces/msg/PoseEstimate";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__t3_interfaces__msg__PoseEstimate() }
  }
}


