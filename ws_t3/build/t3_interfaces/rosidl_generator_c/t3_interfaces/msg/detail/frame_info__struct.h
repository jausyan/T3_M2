// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from t3_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_H_
#define T3_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_H_

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
// Member 'video_name'
// Member 'session'
#include "rosidl_runtime_c/string.h"
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in msg/FrameInfo in the package t3_interfaces.
/**
  * One competition frame as received from the server (Figure 16 of the guidebook)
 */
typedef struct t3_interfaces__msg__FrameInfo
{
  std_msgs__msg__Header header;
  /// 0-based index in the session
  int64_t frame_index;
  /// unique url of the frame ("url" field)
  rosidl_runtime_c__String frame_url;
  rosidl_runtime_c__String video_name;
  rosidl_runtime_c__String session;
  /// translation_x from server (0.0 when invalid)
  double ref_x;
  /// translation_y from server
  double ref_y;
  /// translation_z from server
  double ref_z;
  /// false when server sent "NaN" / health_status == 0
  bool ref_valid;
  /// 1 = position system healthy, 0 = unhealthy
  int8_t health_status;
  /// the decoded camera frame
  sensor_msgs__msg__Image image;
} t3_interfaces__msg__FrameInfo;

// Struct for a sequence of t3_interfaces__msg__FrameInfo.
typedef struct t3_interfaces__msg__FrameInfo__Sequence
{
  t3_interfaces__msg__FrameInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} t3_interfaces__msg__FrameInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // T3_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_H_
