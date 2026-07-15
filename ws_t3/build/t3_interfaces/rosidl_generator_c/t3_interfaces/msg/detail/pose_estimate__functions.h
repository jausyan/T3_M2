// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from t3_interfaces:msg/PoseEstimate.idl
// generated code does not contain a copyright notice

#ifndef T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__FUNCTIONS_H_
#define T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "t3_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "t3_interfaces/msg/detail/pose_estimate__struct.h"

/// Initialize msg/PoseEstimate message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * t3_interfaces__msg__PoseEstimate
 * )) before or use
 * t3_interfaces__msg__PoseEstimate__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
bool
t3_interfaces__msg__PoseEstimate__init(t3_interfaces__msg__PoseEstimate * msg);

/// Finalize msg/PoseEstimate message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
void
t3_interfaces__msg__PoseEstimate__fini(t3_interfaces__msg__PoseEstimate * msg);

/// Create msg/PoseEstimate message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * t3_interfaces__msg__PoseEstimate__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
t3_interfaces__msg__PoseEstimate *
t3_interfaces__msg__PoseEstimate__create();

/// Destroy msg/PoseEstimate message.
/**
 * It calls
 * t3_interfaces__msg__PoseEstimate__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
void
t3_interfaces__msg__PoseEstimate__destroy(t3_interfaces__msg__PoseEstimate * msg);

/// Check for msg/PoseEstimate message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
bool
t3_interfaces__msg__PoseEstimate__are_equal(const t3_interfaces__msg__PoseEstimate * lhs, const t3_interfaces__msg__PoseEstimate * rhs);

/// Copy a msg/PoseEstimate message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
bool
t3_interfaces__msg__PoseEstimate__copy(
  const t3_interfaces__msg__PoseEstimate * input,
  t3_interfaces__msg__PoseEstimate * output);

/// Initialize array of msg/PoseEstimate messages.
/**
 * It allocates the memory for the number of elements and calls
 * t3_interfaces__msg__PoseEstimate__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
bool
t3_interfaces__msg__PoseEstimate__Sequence__init(t3_interfaces__msg__PoseEstimate__Sequence * array, size_t size);

/// Finalize array of msg/PoseEstimate messages.
/**
 * It calls
 * t3_interfaces__msg__PoseEstimate__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
void
t3_interfaces__msg__PoseEstimate__Sequence__fini(t3_interfaces__msg__PoseEstimate__Sequence * array);

/// Create array of msg/PoseEstimate messages.
/**
 * It allocates the memory for the array and calls
 * t3_interfaces__msg__PoseEstimate__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
t3_interfaces__msg__PoseEstimate__Sequence *
t3_interfaces__msg__PoseEstimate__Sequence__create(size_t size);

/// Destroy array of msg/PoseEstimate messages.
/**
 * It calls
 * t3_interfaces__msg__PoseEstimate__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
void
t3_interfaces__msg__PoseEstimate__Sequence__destroy(t3_interfaces__msg__PoseEstimate__Sequence * array);

/// Check for msg/PoseEstimate message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
bool
t3_interfaces__msg__PoseEstimate__Sequence__are_equal(const t3_interfaces__msg__PoseEstimate__Sequence * lhs, const t3_interfaces__msg__PoseEstimate__Sequence * rhs);

/// Copy an array of msg/PoseEstimate messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_t3_interfaces
bool
t3_interfaces__msg__PoseEstimate__Sequence__copy(
  const t3_interfaces__msg__PoseEstimate__Sequence * input,
  t3_interfaces__msg__PoseEstimate__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // T3_INTERFACES__MSG__DETAIL__POSE_ESTIMATE__FUNCTIONS_H_
