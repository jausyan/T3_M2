// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__STRUCT_HPP_
#define T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__STRUCT_HPP_

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

#ifndef _WIN32
# define DEPRECATED__t3_interfaces__msg__PoseEstimate __attribute__((deprecated))
#else
# define DEPRECATED__t3_interfaces__msg__PoseEstimate __declspec(deprecated)
#endif

namespace t3_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PoseEstimate_
{
  using Type = PoseEstimate_<ContainerAllocator>;

  explicit PoseEstimate_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_index = 0ll;
      this->frame_url = "";
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
    }
  }

  explicit PoseEstimate_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    frame_url(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_index = 0ll;
      this->frame_url = "";
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
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
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;
  using _z_type =
    double;
  _z_type z;

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
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const double & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const double & _arg)
  {
    this->z = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    t3_interfaces::msg::PoseEstimate_<ContainerAllocator> *;
  using ConstRawPtr =
    const t3_interfaces::msg::PoseEstimate_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      t3_interfaces::msg::PoseEstimate_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      t3_interfaces::msg::PoseEstimate_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__t3_interfaces__msg__PoseEstimate
    std::shared_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__t3_interfaces__msg__PoseEstimate
    std::shared_ptr<t3_interfaces::msg::PoseEstimate_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PoseEstimate_ & other) const
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
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    return true;
  }
  bool operator!=(const PoseEstimate_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PoseEstimate_

// alias to use template instance with default allocator
using PoseEstimate =
  t3_interfaces::msg::PoseEstimate_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace t3_interfaces

#endif  // T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__STRUCT_HPP_
