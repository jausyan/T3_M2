// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__BUILDER_HPP_
#define T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "t3_interfaces/msg/detail/pose_estimate__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace t3_interfaces
{

namespace msg
{

namespace builder
{

class Init_PoseEstimate_z
{
public:
  explicit Init_PoseEstimate_z(::t3_interfaces::msg::PoseEstimate & msg)
  : msg_(msg)
  {}
  ::t3_interfaces::msg::PoseEstimate z(::t3_interfaces::msg::PoseEstimate::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::t3_interfaces::msg::PoseEstimate msg_;
};

class Init_PoseEstimate_y
{
public:
  explicit Init_PoseEstimate_y(::t3_interfaces::msg::PoseEstimate & msg)
  : msg_(msg)
  {}
  Init_PoseEstimate_z y(::t3_interfaces::msg::PoseEstimate::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_PoseEstimate_z(msg_);
  }

private:
  ::t3_interfaces::msg::PoseEstimate msg_;
};

class Init_PoseEstimate_x
{
public:
  explicit Init_PoseEstimate_x(::t3_interfaces::msg::PoseEstimate & msg)
  : msg_(msg)
  {}
  Init_PoseEstimate_y x(::t3_interfaces::msg::PoseEstimate::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_PoseEstimate_y(msg_);
  }

private:
  ::t3_interfaces::msg::PoseEstimate msg_;
};

class Init_PoseEstimate_frame_url
{
public:
  explicit Init_PoseEstimate_frame_url(::t3_interfaces::msg::PoseEstimate & msg)
  : msg_(msg)
  {}
  Init_PoseEstimate_x frame_url(::t3_interfaces::msg::PoseEstimate::_frame_url_type arg)
  {
    msg_.frame_url = std::move(arg);
    return Init_PoseEstimate_x(msg_);
  }

private:
  ::t3_interfaces::msg::PoseEstimate msg_;
};

class Init_PoseEstimate_frame_index
{
public:
  explicit Init_PoseEstimate_frame_index(::t3_interfaces::msg::PoseEstimate & msg)
  : msg_(msg)
  {}
  Init_PoseEstimate_frame_url frame_index(::t3_interfaces::msg::PoseEstimate::_frame_index_type arg)
  {
    msg_.frame_index = std::move(arg);
    return Init_PoseEstimate_frame_url(msg_);
  }

private:
  ::t3_interfaces::msg::PoseEstimate msg_;
};

class Init_PoseEstimate_header
{
public:
  Init_PoseEstimate_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PoseEstimate_frame_index header(::t3_interfaces::msg::PoseEstimate::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PoseEstimate_frame_index(msg_);
  }

private:
  ::t3_interfaces::msg::PoseEstimate msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::t3_interfaces::msg::PoseEstimate>()
{
  return t3_interfaces::msg::builder::Init_PoseEstimate_header();
}

}  // namespace t3_interfaces

#endif  // T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__BUILDER_HPP_
