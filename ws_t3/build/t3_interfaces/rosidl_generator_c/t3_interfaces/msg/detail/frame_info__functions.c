// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from t3_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice
#include "t3_interfaces/msg/detail/frame_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `frame_url`
// Member `video_name`
// Member `session`
#include "rosidl_runtime_c/string_functions.h"
// Member `image`
#include "sensor_msgs/msg/detail/image__functions.h"

bool
t3_interfaces__msg__FrameInfo__init(t3_interfaces__msg__FrameInfo * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    t3_interfaces__msg__FrameInfo__fini(msg);
    return false;
  }
  // frame_index
  // frame_url
  if (!rosidl_runtime_c__String__init(&msg->frame_url)) {
    t3_interfaces__msg__FrameInfo__fini(msg);
    return false;
  }
  // video_name
  if (!rosidl_runtime_c__String__init(&msg->video_name)) {
    t3_interfaces__msg__FrameInfo__fini(msg);
    return false;
  }
  // session
  if (!rosidl_runtime_c__String__init(&msg->session)) {
    t3_interfaces__msg__FrameInfo__fini(msg);
    return false;
  }
  // ref_x
  // ref_y
  // ref_z
  // ref_valid
  // health_status
  // image
  if (!sensor_msgs__msg__Image__init(&msg->image)) {
    t3_interfaces__msg__FrameInfo__fini(msg);
    return false;
  }
  return true;
}

void
t3_interfaces__msg__FrameInfo__fini(t3_interfaces__msg__FrameInfo * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // frame_index
  // frame_url
  rosidl_runtime_c__String__fini(&msg->frame_url);
  // video_name
  rosidl_runtime_c__String__fini(&msg->video_name);
  // session
  rosidl_runtime_c__String__fini(&msg->session);
  // ref_x
  // ref_y
  // ref_z
  // ref_valid
  // health_status
  // image
  sensor_msgs__msg__Image__fini(&msg->image);
}

bool
t3_interfaces__msg__FrameInfo__are_equal(const t3_interfaces__msg__FrameInfo * lhs, const t3_interfaces__msg__FrameInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // frame_index
  if (lhs->frame_index != rhs->frame_index) {
    return false;
  }
  // frame_url
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->frame_url), &(rhs->frame_url)))
  {
    return false;
  }
  // video_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->video_name), &(rhs->video_name)))
  {
    return false;
  }
  // session
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->session), &(rhs->session)))
  {
    return false;
  }
  // ref_x
  if (lhs->ref_x != rhs->ref_x) {
    return false;
  }
  // ref_y
  if (lhs->ref_y != rhs->ref_y) {
    return false;
  }
  // ref_z
  if (lhs->ref_z != rhs->ref_z) {
    return false;
  }
  // ref_valid
  if (lhs->ref_valid != rhs->ref_valid) {
    return false;
  }
  // health_status
  if (lhs->health_status != rhs->health_status) {
    return false;
  }
  // image
  if (!sensor_msgs__msg__Image__are_equal(
      &(lhs->image), &(rhs->image)))
  {
    return false;
  }
  return true;
}

bool
t3_interfaces__msg__FrameInfo__copy(
  const t3_interfaces__msg__FrameInfo * input,
  t3_interfaces__msg__FrameInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // frame_index
  output->frame_index = input->frame_index;
  // frame_url
  if (!rosidl_runtime_c__String__copy(
      &(input->frame_url), &(output->frame_url)))
  {
    return false;
  }
  // video_name
  if (!rosidl_runtime_c__String__copy(
      &(input->video_name), &(output->video_name)))
  {
    return false;
  }
  // session
  if (!rosidl_runtime_c__String__copy(
      &(input->session), &(output->session)))
  {
    return false;
  }
  // ref_x
  output->ref_x = input->ref_x;
  // ref_y
  output->ref_y = input->ref_y;
  // ref_z
  output->ref_z = input->ref_z;
  // ref_valid
  output->ref_valid = input->ref_valid;
  // health_status
  output->health_status = input->health_status;
  // image
  if (!sensor_msgs__msg__Image__copy(
      &(input->image), &(output->image)))
  {
    return false;
  }
  return true;
}

t3_interfaces__msg__FrameInfo *
t3_interfaces__msg__FrameInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  t3_interfaces__msg__FrameInfo * msg = (t3_interfaces__msg__FrameInfo *)allocator.allocate(sizeof(t3_interfaces__msg__FrameInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(t3_interfaces__msg__FrameInfo));
  bool success = t3_interfaces__msg__FrameInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
t3_interfaces__msg__FrameInfo__destroy(t3_interfaces__msg__FrameInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    t3_interfaces__msg__FrameInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
t3_interfaces__msg__FrameInfo__Sequence__init(t3_interfaces__msg__FrameInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  t3_interfaces__msg__FrameInfo * data = NULL;

  if (size) {
    data = (t3_interfaces__msg__FrameInfo *)allocator.zero_allocate(size, sizeof(t3_interfaces__msg__FrameInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = t3_interfaces__msg__FrameInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        t3_interfaces__msg__FrameInfo__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
t3_interfaces__msg__FrameInfo__Sequence__fini(t3_interfaces__msg__FrameInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      t3_interfaces__msg__FrameInfo__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

t3_interfaces__msg__FrameInfo__Sequence *
t3_interfaces__msg__FrameInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  t3_interfaces__msg__FrameInfo__Sequence * array = (t3_interfaces__msg__FrameInfo__Sequence *)allocator.allocate(sizeof(t3_interfaces__msg__FrameInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = t3_interfaces__msg__FrameInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
t3_interfaces__msg__FrameInfo__Sequence__destroy(t3_interfaces__msg__FrameInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    t3_interfaces__msg__FrameInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
t3_interfaces__msg__FrameInfo__Sequence__are_equal(const t3_interfaces__msg__FrameInfo__Sequence * lhs, const t3_interfaces__msg__FrameInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!t3_interfaces__msg__FrameInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
t3_interfaces__msg__FrameInfo__Sequence__copy(
  const t3_interfaces__msg__FrameInfo__Sequence * input,
  t3_interfaces__msg__FrameInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(t3_interfaces__msg__FrameInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    t3_interfaces__msg__FrameInfo * data =
      (t3_interfaces__msg__FrameInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!t3_interfaces__msg__FrameInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          t3_interfaces__msg__FrameInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!t3_interfaces__msg__FrameInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
