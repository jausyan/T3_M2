// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice
#include "t3_interfaces/msg/detail/pose_estimate__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `frame_url`
#include "rosidl_runtime_c/string_functions.h"

bool
t3_interfaces__msg__PoseEstimate__init(t3_interfaces__msg__PoseEstimate * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    t3_interfaces__msg__PoseEstimate__fini(msg);
    return false;
  }
  // frame_index
  // frame_url
  if (!rosidl_runtime_c__String__init(&msg->frame_url)) {
    t3_interfaces__msg__PoseEstimate__fini(msg);
    return false;
  }
  // x
  // y
  // z
  return true;
}

void
t3_interfaces__msg__PoseEstimate__fini(t3_interfaces__msg__PoseEstimate * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // frame_index
  // frame_url
  rosidl_runtime_c__String__fini(&msg->frame_url);
  // x
  // y
  // z
}

bool
t3_interfaces__msg__PoseEstimate__are_equal(const t3_interfaces__msg__PoseEstimate * lhs, const t3_interfaces__msg__PoseEstimate * rhs)
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
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // z
  if (lhs->z != rhs->z) {
    return false;
  }
  return true;
}

bool
t3_interfaces__msg__PoseEstimate__copy(
  const t3_interfaces__msg__PoseEstimate * input,
  t3_interfaces__msg__PoseEstimate * output)
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
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // z
  output->z = input->z;
  return true;
}

t3_interfaces__msg__PoseEstimate *
t3_interfaces__msg__PoseEstimate__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  t3_interfaces__msg__PoseEstimate * msg = (t3_interfaces__msg__PoseEstimate *)allocator.allocate(sizeof(t3_interfaces__msg__PoseEstimate), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(t3_interfaces__msg__PoseEstimate));
  bool success = t3_interfaces__msg__PoseEstimate__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
t3_interfaces__msg__PoseEstimate__destroy(t3_interfaces__msg__PoseEstimate * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    t3_interfaces__msg__PoseEstimate__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
t3_interfaces__msg__PoseEstimate__Sequence__init(t3_interfaces__msg__PoseEstimate__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  t3_interfaces__msg__PoseEstimate * data = NULL;

  if (size) {
    data = (t3_interfaces__msg__PoseEstimate *)allocator.zero_allocate(size, sizeof(t3_interfaces__msg__PoseEstimate), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = t3_interfaces__msg__PoseEstimate__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        t3_interfaces__msg__PoseEstimate__fini(&data[i - 1]);
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
t3_interfaces__msg__PoseEstimate__Sequence__fini(t3_interfaces__msg__PoseEstimate__Sequence * array)
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
      t3_interfaces__msg__PoseEstimate__fini(&array->data[i]);
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

t3_interfaces__msg__PoseEstimate__Sequence *
t3_interfaces__msg__PoseEstimate__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  t3_interfaces__msg__PoseEstimate__Sequence * array = (t3_interfaces__msg__PoseEstimate__Sequence *)allocator.allocate(sizeof(t3_interfaces__msg__PoseEstimate__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = t3_interfaces__msg__PoseEstimate__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
t3_interfaces__msg__PoseEstimate__Sequence__destroy(t3_interfaces__msg__PoseEstimate__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    t3_interfaces__msg__PoseEstimate__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
t3_interfaces__msg__PoseEstimate__Sequence__are_equal(const t3_interfaces__msg__PoseEstimate__Sequence * lhs, const t3_interfaces__msg__PoseEstimate__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!t3_interfaces__msg__PoseEstimate__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
t3_interfaces__msg__PoseEstimate__Sequence__copy(
  const t3_interfaces__msg__PoseEstimate__Sequence * input,
  t3_interfaces__msg__PoseEstimate__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(t3_interfaces__msg__PoseEstimate);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    t3_interfaces__msg__PoseEstimate * data =
      (t3_interfaces__msg__PoseEstimate *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!t3_interfaces__msg__PoseEstimate__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          t3_interfaces__msg__PoseEstimate__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!t3_interfaces__msg__PoseEstimate__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
