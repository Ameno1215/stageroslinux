// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from denso_robot_core_interfaces:action/MoveValue.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_VALUE__FUNCTIONS_H_
#define DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_VALUE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "denso_robot_core_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "denso_robot_core_interfaces/action/detail/move_value__struct.h"

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_Goal
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Goal__init(denso_robot_core_interfaces__action__MoveValue_Goal * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Goal__fini(denso_robot_core_interfaces__action__MoveValue_Goal * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_Goal *
denso_robot_core_interfaces__action__MoveValue_Goal__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Goal__destroy(denso_robot_core_interfaces__action__MoveValue_Goal * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Goal__are_equal(const denso_robot_core_interfaces__action__MoveValue_Goal * lhs, const denso_robot_core_interfaces__action__MoveValue_Goal * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_Goal__copy(
  const denso_robot_core_interfaces__action__MoveValue_Goal * input,
  denso_robot_core_interfaces__action__MoveValue_Goal * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__init(denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence *
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_Goal__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_Goal__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_Result
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Result__init(denso_robot_core_interfaces__action__MoveValue_Result * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Result__fini(denso_robot_core_interfaces__action__MoveValue_Result * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_Result *
denso_robot_core_interfaces__action__MoveValue_Result__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Result__destroy(denso_robot_core_interfaces__action__MoveValue_Result * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Result__are_equal(const denso_robot_core_interfaces__action__MoveValue_Result * lhs, const denso_robot_core_interfaces__action__MoveValue_Result * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_Result__copy(
  const denso_robot_core_interfaces__action__MoveValue_Result * input,
  denso_robot_core_interfaces__action__MoveValue_Result * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Result__Sequence__init(denso_robot_core_interfaces__action__MoveValue_Result__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Result__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_Result__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_Result__Sequence *
denso_robot_core_interfaces__action__MoveValue_Result__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Result__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_Result__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Result__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_Result__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_Result__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_Result__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_Result__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_Result__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_Feedback
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Feedback__init(denso_robot_core_interfaces__action__MoveValue_Feedback * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Feedback__fini(denso_robot_core_interfaces__action__MoveValue_Feedback * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_Feedback *
denso_robot_core_interfaces__action__MoveValue_Feedback__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Feedback__destroy(denso_robot_core_interfaces__action__MoveValue_Feedback * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Feedback__are_equal(const denso_robot_core_interfaces__action__MoveValue_Feedback * lhs, const denso_robot_core_interfaces__action__MoveValue_Feedback * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_Feedback__copy(
  const denso_robot_core_interfaces__action__MoveValue_Feedback * input,
  denso_robot_core_interfaces__action__MoveValue_Feedback * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__init(denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence *
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_Feedback__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__init(denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__fini(denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request *
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__destroy(denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__are_equal(const denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * lhs, const denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__copy(
  const denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * input,
  denso_robot_core_interfaces__action__MoveValue_SendGoal_Request * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__init(denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence *
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_SendGoal_Request__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__init(denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__fini(denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response *
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__destroy(denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__are_equal(const denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * lhs, const denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__copy(
  const denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * input,
  denso_robot_core_interfaces__action__MoveValue_SendGoal_Response * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__init(denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence *
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_SendGoal_Response__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__init(denso_robot_core_interfaces__action__MoveValue_GetResult_Request * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__fini(denso_robot_core_interfaces__action__MoveValue_GetResult_Request * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_GetResult_Request *
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__destroy(denso_robot_core_interfaces__action__MoveValue_GetResult_Request * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__are_equal(const denso_robot_core_interfaces__action__MoveValue_GetResult_Request * lhs, const denso_robot_core_interfaces__action__MoveValue_GetResult_Request * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__copy(
  const denso_robot_core_interfaces__action__MoveValue_GetResult_Request * input,
  denso_robot_core_interfaces__action__MoveValue_GetResult_Request * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__init(denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence *
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_GetResult_Request__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__init(denso_robot_core_interfaces__action__MoveValue_GetResult_Response * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__fini(denso_robot_core_interfaces__action__MoveValue_GetResult_Response * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_GetResult_Response *
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__destroy(denso_robot_core_interfaces__action__MoveValue_GetResult_Response * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__are_equal(const denso_robot_core_interfaces__action__MoveValue_GetResult_Response * lhs, const denso_robot_core_interfaces__action__MoveValue_GetResult_Response * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__copy(
  const denso_robot_core_interfaces__action__MoveValue_GetResult_Response * input,
  denso_robot_core_interfaces__action__MoveValue_GetResult_Response * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__init(denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence *
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_GetResult_Response__Sequence * output);

/// Initialize action/MoveValue message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage
 * )) before or use
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__init(denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * msg);

/// Finalize action/MoveValue message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__fini(denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * msg);

/// Create action/MoveValue message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage *
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__create();

/// Destroy action/MoveValue message.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__destroy(denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * msg);

/// Check for action/MoveValue message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__are_equal(const denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * lhs, const denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * rhs);

/// Copy a action/MoveValue message.
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
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__copy(
  const denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * input,
  denso_robot_core_interfaces__action__MoveValue_FeedbackMessage * output);

/// Initialize array of action/MoveValue messages.
/**
 * It allocates the memory for the number of elements and calls
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__init(denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__fini(denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * array);

/// Create array of action/MoveValue messages.
/**
 * It allocates the memory for the array and calls
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence *
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/MoveValue messages.
/**
 * It calls
 * denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
void
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__destroy(denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * array);

/// Check for action/MoveValue message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_denso_robot_core_interfaces
bool
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__are_equal(const denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * lhs, const denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/MoveValue messages.
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
denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence__copy(
  const denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * input,
  denso_robot_core_interfaces__action__MoveValue_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_VALUE__FUNCTIONS_H_
