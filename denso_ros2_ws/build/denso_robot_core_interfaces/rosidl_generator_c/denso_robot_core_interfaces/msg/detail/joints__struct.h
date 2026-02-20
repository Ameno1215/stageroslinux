// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_robot_core_interfaces:msg/Joints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__STRUCT_H_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Joints in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__msg__Joints
{
  int32_t joint;
  double value;
} denso_robot_core_interfaces__msg__Joints;

// Struct for a sequence of denso_robot_core_interfaces__msg__Joints.
typedef struct denso_robot_core_interfaces__msg__Joints__Sequence
{
  denso_robot_core_interfaces__msg__Joints * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__msg__Joints__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__STRUCT_H_
