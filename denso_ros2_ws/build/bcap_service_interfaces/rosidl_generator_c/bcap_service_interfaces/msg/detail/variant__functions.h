// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__FUNCTIONS_H_
#define BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "bcap_service_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "bcap_service_interfaces/msg/detail/variant__struct.h"

/// Initialize msg/Variant message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * bcap_service_interfaces__msg__Variant
 * )) before or use
 * bcap_service_interfaces__msg__Variant__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bool
bcap_service_interfaces__msg__Variant__init(bcap_service_interfaces__msg__Variant * msg);

/// Finalize msg/Variant message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
void
bcap_service_interfaces__msg__Variant__fini(bcap_service_interfaces__msg__Variant * msg);

/// Create msg/Variant message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * bcap_service_interfaces__msg__Variant__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bcap_service_interfaces__msg__Variant *
bcap_service_interfaces__msg__Variant__create();

/// Destroy msg/Variant message.
/**
 * It calls
 * bcap_service_interfaces__msg__Variant__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
void
bcap_service_interfaces__msg__Variant__destroy(bcap_service_interfaces__msg__Variant * msg);

/// Check for msg/Variant message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bool
bcap_service_interfaces__msg__Variant__are_equal(const bcap_service_interfaces__msg__Variant * lhs, const bcap_service_interfaces__msg__Variant * rhs);

/// Copy a msg/Variant message.
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
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bool
bcap_service_interfaces__msg__Variant__copy(
  const bcap_service_interfaces__msg__Variant * input,
  bcap_service_interfaces__msg__Variant * output);

/// Initialize array of msg/Variant messages.
/**
 * It allocates the memory for the number of elements and calls
 * bcap_service_interfaces__msg__Variant__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bool
bcap_service_interfaces__msg__Variant__Sequence__init(bcap_service_interfaces__msg__Variant__Sequence * array, size_t size);

/// Finalize array of msg/Variant messages.
/**
 * It calls
 * bcap_service_interfaces__msg__Variant__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
void
bcap_service_interfaces__msg__Variant__Sequence__fini(bcap_service_interfaces__msg__Variant__Sequence * array);

/// Create array of msg/Variant messages.
/**
 * It allocates the memory for the array and calls
 * bcap_service_interfaces__msg__Variant__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bcap_service_interfaces__msg__Variant__Sequence *
bcap_service_interfaces__msg__Variant__Sequence__create(size_t size);

/// Destroy array of msg/Variant messages.
/**
 * It calls
 * bcap_service_interfaces__msg__Variant__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
void
bcap_service_interfaces__msg__Variant__Sequence__destroy(bcap_service_interfaces__msg__Variant__Sequence * array);

/// Check for msg/Variant message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bool
bcap_service_interfaces__msg__Variant__Sequence__are_equal(const bcap_service_interfaces__msg__Variant__Sequence * lhs, const bcap_service_interfaces__msg__Variant__Sequence * rhs);

/// Copy an array of msg/Variant messages.
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
ROSIDL_GENERATOR_C_PUBLIC_bcap_service_interfaces
bool
bcap_service_interfaces__msg__Variant__Sequence__copy(
  const bcap_service_interfaces__msg__Variant__Sequence * input,
  bcap_service_interfaces__msg__Variant__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__FUNCTIONS_H_
