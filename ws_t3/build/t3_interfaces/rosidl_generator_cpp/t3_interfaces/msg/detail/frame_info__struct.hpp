// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from t3_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_HPP_
#define T3_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__t3_interfaces__msg__FrameInfo __attribute__((deprecated))
#else
# define DEPRECATED__t3_interfaces__msg__FrameInfo __declspec(deprecated)
#endif

namespace t3_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FrameInfo_
{
  using Type = FrameInfo_<ContainerAllocator>;

  explicit FrameInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    image(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_index = 0ll;
      this->frame_url = "";
      this->video_name = "";
      this->session = "";
      this->ref_x = 0.0;
      this->ref_y = 0.0;
      this->ref_z = 0.0;
      this->ref_valid = false;
      this->health_status = 0;
    }
  }

  explicit FrameInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    frame_url(_alloc),
    video_name(_alloc),
    session(_alloc),
    image(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_index = 0ll;
      this->frame_url = "";
      this->video_name = "";
      this->session = "";
      this->ref_x = 0.0;
      this->ref_y = 0.0;
      this->ref_z = 0.0;
      this->ref_valid = false;
      this->health_status = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _frame_index_type =
    int64_t;
  _frame_index_type frame_index;
  using _frame_url_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_url_type frame_url;
  using _video_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _video_name_type video_name;
  using _session_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _session_type session;
  using _ref_x_type =
    double;
  _ref_x_type ref_x;
  using _ref_y_type =
    double;
  _ref_y_type ref_y;
  using _ref_z_type =
    double;
  _ref_z_type ref_z;
  using _ref_valid_type =
    bool;
  _ref_valid_type ref_valid;
  using _health_status_type =
    int8_t;
  _health_status_type health_status;
  using _image_type =
    sensor_msgs::msg::Image_<ContainerAllocator>;
  _image_type image;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__frame_index(
    const int64_t & _arg)
  {
    this->frame_index = _arg;
    return *this;
  }
  Type & set__frame_url(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_url = _arg;
    return *this;
  }
  Type & set__video_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->video_name = _arg;
    return *this;
  }
  Type & set__session(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->session = _arg;
    return *this;
  }
  Type & set__ref_x(
    const double & _arg)
  {
    this->ref_x = _arg;
    return *this;
  }
  Type & set__ref_y(
    const double & _arg)
  {
    this->ref_y = _arg;
    return *this;
  }
  Type & set__ref_z(
    const double & _arg)
  {
    this->ref_z = _arg;
    return *this;
  }
  Type & set__ref_valid(
    const bool & _arg)
  {
    this->ref_valid = _arg;
    return *this;
  }
  Type & set__health_status(
    const int8_t & _arg)
  {
    this->health_status = _arg;
    return *this;
  }
  Type & set__image(
    const sensor_msgs::msg::Image_<ContainerAllocator> & _arg)
  {
    this->image = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    t3_interfaces::msg::FrameInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const t3_interfaces::msg::FrameInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      t3_interfaces::msg::FrameInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      t3_interfaces::msg::FrameInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__t3_interfaces__msg__FrameInfo
    std::shared_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__t3_interfaces__msg__FrameInfo
    std::shared_ptr<t3_interfaces::msg::FrameInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FrameInfo_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->frame_index != other.frame_index) {
      return false;
    }
    if (this->frame_url != other.frame_url) {
      return false;
    }
    if (this->video_name != other.video_name) {
      return false;
    }
    if (this->session != other.session) {
      return false;
    }
    if (this->ref_x != other.ref_x) {
      return false;
    }
    if (this->ref_y != other.ref_y) {
      return false;
    }
    if (this->ref_z != other.ref_z) {
      return false;
    }
    if (this->ref_valid != other.ref_valid) {
      return false;
    }
    if (this->health_status != other.health_status) {
      return false;
    }
    if (this->image != other.image) {
      return false;
    }
    return true;
  }
  bool operator!=(const FrameInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FrameInfo_

// alias to use template instance with default allocator
using FrameInfo =
  t3_interfaces::msg::FrameInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace t3_interfaces

#endif  // T3_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_HPP_
