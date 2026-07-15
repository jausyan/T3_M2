// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from t3_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__FRAME_INFO__TRAITS_HPP_
#define T3_INTERFACES__MSG__DETAIL__FRAME_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "t3_interfaces/msg/detail/frame_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'image'
#include "sensor_msgs/msg/detail/image__traits.hpp"

namespace t3_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const FrameInfo & msg,
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

  // member: video_name
  {
    out << "video_name: ";
    rosidl_generator_traits::value_to_yaml(msg.video_name, out);
    out << ", ";
  }

  // member: session
  {
    out << "session: ";
    rosidl_generator_traits::value_to_yaml(msg.session, out);
    out << ", ";
  }

  // member: ref_x
  {
    out << "ref_x: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_x, out);
    out << ", ";
  }

  // member: ref_y
  {
    out << "ref_y: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_y, out);
    out << ", ";
  }

  // member: ref_z
  {
    out << "ref_z: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_z, out);
    out << ", ";
  }

  // member: ref_valid
  {
    out << "ref_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_valid, out);
    out << ", ";
  }

  // member: health_status
  {
    out << "health_status: ";
    rosidl_generator_traits::value_to_yaml(msg.health_status, out);
    out << ", ";
  }

  // member: image
  {
    out << "image: ";
    to_flow_style_yaml(msg.image, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FrameInfo & msg,
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

  // member: video_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "video_name: ";
    rosidl_generator_traits::value_to_yaml(msg.video_name, out);
    out << "\n";
  }

  // member: session
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "session: ";
    rosidl_generator_traits::value_to_yaml(msg.session, out);
    out << "\n";
  }

  // member: ref_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_x: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_x, out);
    out << "\n";
  }

  // member: ref_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_y: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_y, out);
    out << "\n";
  }

  // member: ref_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_z: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_z, out);
    out << "\n";
  }

  // member: ref_valid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ref_valid: ";
    rosidl_generator_traits::value_to_yaml(msg.ref_valid, out);
    out << "\n";
  }

  // member: health_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "health_status: ";
    rosidl_generator_traits::value_to_yaml(msg.health_status, out);
    out << "\n";
  }

  // member: image
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image:\n";
    to_block_style_yaml(msg.image, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FrameInfo & msg, bool use_flow_style = false)
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
  const t3_interfaces::msg::FrameInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  t3_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use t3_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const t3_interfaces::msg::FrameInfo & msg)
{
  return t3_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<t3_interfaces::msg::FrameInfo>()
{
  return "t3_interfaces::msg::FrameInfo";
}

template<>
inline const char * name<t3_interfaces::msg::FrameInfo>()
{
  return "t3_interfaces/msg/FrameInfo";
}

template<>
struct has_fixed_size<t3_interfaces::msg::FrameInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<t3_interfaces::msg::FrameInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<t3_interfaces::msg::FrameInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // T3_INTERFACES__MSG__DETAIL__FRAME_INFO__TRAITS_HPP_
