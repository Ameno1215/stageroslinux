// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from denso_robot_core_interfaces:msg/UserIO.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__FUNCTIONS_H_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "denso_robot_core_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "denso_robot_core_interfaces/msg/detail/user_io__struct.h"

/// Initialize msg/UserIO message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__msg__UserIO
 * )) before or use
 * denso_robot_core_interfaces__msg__UserIO__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__UserIO__init(denso_robot_core_interfaces__msg__UserIO * msg);

/// Finalize msg/UserIO message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__UserIO__fini(denso_robot_core_interfaces__msg__UserIO * msg);

/// Create msg/UserIO message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__msg__UserIO__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__msg__UserIO *
denso_robot_core_interfaces__msg__UserIO__create();

/// Destroy msg/UserIO message.
/**
 * It calls
 * denso_robot_core_interfaces__msg__UserIO__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__UserIO__destroy(denso_robot_core_interfaces__msg__UserIO * msg);

/// Check for msg/UserIO message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__UserIO__are_equal(const denso_robot_core_interfaces__msg__UserIO * lhs, const denso_robot_core_interfaces__msg__UserIO * rhs);

/// Copy a msg/UserIO message.
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
denso_robot_core_interfaces__msg__UserIO__copy(
  const denso_robot_core_interfaces__msg__UserIO * input,
  denso_robot_core_interfaces__msg__UserIO * output);

/// Initialize array of msg/UserIO messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__msg__UserIO__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__UserIO__Sequence__init(denso_robot_core_interfaces__msg__UserIO__Sequence * array, size_t size);

/// Finalize array of msg/UserIO messages.
/**
 * It calls
 * denso_robot_core_interfaces__msg__UserIO__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__UserIO__Sequence__fini(denso_robot_core_interfaces__msg__UserIO__Sequence * array);

/// Create array of msg/UserIO messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__msg__UserIO__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__msg__UserIO__Sequence *
denso_robot_core_interfaces__msg__UserIO__Sequence__create(size_t size);

/// Destroy array of msg/UserIO messages.
/**
 * It calls
 * denso_robot_core_interfaces__msg__UserIO__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__msg__UserIO__Sequence__destroy(denso_robot_core_interfaces__msg__UserIO__Sequence * array);

/// Check for msg/UserIO message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__msg__UserIO__Sequence__are_equal(const denso_robot_core_interfaces__msg__UserIO__Sequence * lhs, const denso_robot_core_interfaces__msg__UserIO__Sequence * rhs);

/// Copy an array of msg/UserIO messages.
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
denso_robot_core_interfaces__msg__UserIO__Sequence__copy(
  const denso_robot_core_interfaces__msg__UserIO__Sequence * input,
  denso_robot_core_interfaces__msg__UserIO__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__FUNCTIONS_H_
