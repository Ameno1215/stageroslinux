// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_robot_core_interfaces:msg/ExJoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__STRUCT_H_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'joints'
#include "denso_robot_core_interfaces/msg/detail/joints__struct.h"

/// Struct defined in msg/ExJoints in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__msg__ExJoints
{
  int32_t mode;
  denso_robot_core_interfaces__msg__Joints__Sequence joints;
} denso_robot_core_interfaces__msg__ExJoints;

// Struct for a sequence of denso_robot_core_interfaces__msg__ExJoints.
typedef struct denso_robot_core_interfaces__msg__ExJoints__Sequence
{
  denso_robot_core_interfaces__msg__ExJoints * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__msg__ExJoints__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__STRUCT_H_
