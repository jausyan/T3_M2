// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__STRUCT_H_
#define T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'frame_url'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PoseEstimate in the package t3_interfaces.
/**
  * Estimated aircraft displacement for one frame (what gets POSTed to the server)
 */
typedef struct t3_interfaces__msg__PoseEstimate
{
  std_msgs__msg__Header header;
  int64_t frame_index;
  rosidl_runtime_c__String frame_url;
  /// metres, relative to first frame of the session
  double x;
  double y;
  double z;
} t3_interfaces__msg__PoseEstimate;

// Struct for a sequence of t3_interfaces__msg__PoseEstimate.
typedef struct t3_interfaces__msg__PoseEstimate__Sequence
{
  t3_interfaces__msg__PoseEstimate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} t3_interfaces__msg__PoseEstimate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__STRUCT_H_
