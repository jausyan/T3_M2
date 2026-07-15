// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "t3_interfaces/msg/detail/pose_estimate__rosidl_typesupport_introspection_c.h"
#include "t3_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "t3_interfaces/msg/detail/pose_estimate__functions.h"
#include "t3_interfaces/msg/detail/pose_estimate__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `frame_url`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  t3_interfaces__msg__PoseEstimate__init(message_memory);
}

void t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_fini_function(void * message_memory)
{
  t3_interfaces__msg__PoseEstimate__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_member_array[6] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(t3_interfaces__msg__PoseEstimate, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "frame_index",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(t3_interfaces__msg__PoseEstimate, frame_index),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "frame_url",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(t3_interfaces__msg__PoseEstimate, frame_url),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(t3_interfaces__msg__PoseEstimate, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(t3_interfaces__msg__PoseEstimate, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(t3_interfaces__msg__PoseEstimate, z),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_members = {
  "t3_interfaces__msg",  // message namespace
  "PoseEstimate",  // message name
  6,  // number of fields
  sizeof(t3_interfaces__msg__PoseEstimate),
  t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_member_array,  // message members
  t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_init_function,  // function to initialize message memory (memory has to be allocated)
  t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_type_support_handle = {
  0,
  &t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_t3_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, t3_interfaces, msg, PoseEstimate)() {
  t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_type_support_handle.typesupport_identifier) {
    t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &t3_interfaces__msg__PoseEstimate__rosidl_typesupport_introspection_c__PoseEstimate_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
