// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__TRAITS_HPP_
#define T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "t3_interfaces/msg/detail/pose_estimate__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace t3_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PoseEstimate & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: frame_index
  {
    out << "frame_index: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_index, out);
    out << ", ";
  }

  // member: frame_url
  {
    out << "frame_url: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_url, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PoseEstimate & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: frame_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_index: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_index, out);
    out << "\n";
  }

  // member: frame_url
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_url: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_url, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PoseEstimate & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace t3_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use t3_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const t3_interfaces::msg::PoseEstimate & msg,
  std::ostream & out, size_t indentation = 0)
{
  t3_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use t3_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const t3_interfaces::msg::PoseEstimate & msg)
{
  return t3_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<t3_interfaces::msg::PoseEstimate>()
{
  return "t3_interfaces::msg::PoseEstimate";
}

template<>
inline const char * name<t3_interfaces::msg::PoseEstimate>()
{
  return "t3_interfaces/msg/PoseEstimate";
}

template<>
struct has_fixed_size<t3_interfaces::msg::PoseEstimate>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<t3_interfaces::msg::PoseEstimate>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<t3_interfaces::msg::PoseEstimate>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__TRAITS_HPP_
