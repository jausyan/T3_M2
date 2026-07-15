// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from t3_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__FRAME_INFO__BUILDER_HPP_
#define T3_INTERFACES__MSG__DETAIL__FRAME_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "t3_interfaces/msg/detail/frame_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace t3_interfaces
{

namespace msg
{

namespace builder
{

class Init_FrameInfo_image
{
public:
  explicit Init_FrameInfo_image(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  ::t3_interfaces::msg::FrameInfo image(::t3_interfaces::msg::FrameInfo::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_health_status
{
public:
  explicit Init_FrameInfo_health_status(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_image health_status(::t3_interfaces::msg::FrameInfo::_health_status_type arg)
  {
    msg_.health_status = std::move(arg);
    return Init_FrameInfo_image(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_ref_valid
{
public:
  explicit Init_FrameInfo_ref_valid(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_health_status ref_valid(::t3_interfaces::msg::FrameInfo::_ref_valid_type arg)
  {
    msg_.ref_valid = std::move(arg);
    return Init_FrameInfo_health_status(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_ref_z
{
public:
  explicit Init_FrameInfo_ref_z(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_ref_valid ref_z(::t3_interfaces::msg::FrameInfo::_ref_z_type arg)
  {
    msg_.ref_z = std::move(arg);
    return Init_FrameInfo_ref_valid(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_ref_y
{
public:
  explicit Init_FrameInfo_ref_y(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_ref_z ref_y(::t3_interfaces::msg::FrameInfo::_ref_y_type arg)
  {
    msg_.ref_y = std::move(arg);
    return Init_FrameInfo_ref_z(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_ref_x
{
public:
  explicit Init_FrameInfo_ref_x(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_ref_y ref_x(::t3_interfaces::msg::FrameInfo::_ref_x_type arg)
  {
    msg_.ref_x = std::move(arg);
    return Init_FrameInfo_ref_y(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_session
{
public:
  explicit Init_FrameInfo_session(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_ref_x session(::t3_interfaces::msg::FrameInfo::_session_type arg)
  {
    msg_.session = std::move(arg);
    return Init_FrameInfo_ref_x(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_video_name
{
public:
  explicit Init_FrameInfo_video_name(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_session video_name(::t3_interfaces::msg::FrameInfo::_video_name_type arg)
  {
    msg_.video_name = std::move(arg);
    return Init_FrameInfo_session(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_frame_url
{
public:
  explicit Init_FrameInfo_frame_url(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_video_name frame_url(::t3_interfaces::msg::FrameInfo::_frame_url_type arg)
  {
    msg_.frame_url = std::move(arg);
    return Init_FrameInfo_video_name(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_frame_index
{
public:
  explicit Init_FrameInfo_frame_index(::t3_interfaces::msg::FrameInfo & msg)
  : msg_(msg)
  {}
  Init_FrameInfo_frame_url frame_index(::t3_interfaces::msg::FrameInfo::_frame_index_type arg)
  {
    msg_.frame_index = std::move(arg);
    return Init_FrameInfo_frame_url(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

class Init_FrameInfo_header
{
public:
  Init_FrameInfo_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FrameInfo_frame_index header(::t3_interfaces::msg::FrameInfo::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_FrameInfo_frame_index(msg_);
  }

private:
  ::t3_interfaces::msg::FrameInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::t3_interfaces::msg::FrameInfo>()
{
  return t3_interfaces::msg::builder::Init_FrameInfo_header();
}

}  // namespace t3_interfaces

#endif  // T3_INTERFACES__MSG__DETAIL__FRAME_INFO__BUILDER_HPP_
