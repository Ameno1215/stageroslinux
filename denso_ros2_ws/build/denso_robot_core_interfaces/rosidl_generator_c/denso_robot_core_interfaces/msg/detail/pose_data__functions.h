// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from denso_robot_core_interfaces:msg/PoseData.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__FUNCTIONS_H_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "denso_robot_core_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "denso_robot_core_interfaces/msg/detail/pose_data__struct.h"

/// Initialize msg/PoseData message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__msg__PoseData
 * )) before or use
 * denso_robot_core_interfaces__msg__PoseData__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__PoseData__init(denso_robot_core_interfaces__msg__PoseData * msg);

/// Finalize msg/PoseData message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__PoseData__fini(denso_robot_core_interfaces__msg__PoseData * msg);

/// Create msg/PoseData message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__msg__PoseData__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__msg__PoseData *
denso_robot_core_interfaces__msg__PoseData__create();

/// Destroy msg/PoseData message.
/**
 * It calls
 * denso_robot_core_interfaces__msg__PoseData__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__PoseData__destroy(denso_robot_core_interfaces__msg__PoseData * msg);

/// Check for msg/PoseData message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__PoseData__are_equal(const denso_robot_core_interfaces__msg__PoseData * lhs, const denso_robot_core_interfaces__msg__PoseData * rhs);

/// Copy a msg/PoseData message.
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
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__PoseData__copy(
  const denso_robot_core_interfaces__msg__PoseData * input,
  denso_robot_core_interfaces__msg__PoseData * output);

/// Initialize array of msg/PoseData messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__msg__PoseData__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__PoseData__Sequence__init(denso_robot_core_interfaces__msg__PoseData__Sequence * array, size_t size);

/// Finalize array of msg/PoseData messages.
/**
 * It calls
 * denso_robot_core_interfaces__msg__PoseData__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__PoseData__Sequence__fini(denso_robot_core_interfaces__msg__PoseData__Sequence * array);

/// Create array of msg/PoseData messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__msg__PoseData__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__msg__PoseData__Sequence *
denso_robot_core_interfaces__msg__PoseData__Sequence__create(size_t size);

/// Destroy array of msg/PoseData messages.
/**
 * It calls
 * denso_robot_core_interfaces__msg__PoseData__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__PoseData__Sequence__destroy(denso_robot_core_interfaces__msg__PoseData__Sequence * array);

/// Check for msg/PoseData message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__PoseData__Sequence__are_equal(const denso_robot_core_interfaces__msg__PoseData__Sequence * lhs, const denso_robot_core_interfaces__msg__PoseData__Sequence * rhs);

/// Copy an array of msg/PoseData messages.
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
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__PoseData__Sequence__copy(
  const denso_robot_core_interfaces__msg__PoseData__Sequence * input,
  denso_robot_core_interfaces__msg__PoseData__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__FUNCTIONS_H_
