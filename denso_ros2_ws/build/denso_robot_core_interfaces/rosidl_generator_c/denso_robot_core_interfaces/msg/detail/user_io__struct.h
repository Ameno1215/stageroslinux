// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_robot_core_interfaces:msg/UserIO.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__STRUCT_H_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'MIN_USERIO_OFFSET'.
enum
{
  denso_robot_core_interfaces__msg__UserIO__MIN_USERIO_OFFSET = 128l
};

/// Constant 'USERIO_ALIGNMENT'.
enum
{
  denso_robot_core_interfaces__msg__UserIO__USERIO_ALIGNMENT = 8l
};

// Include directives for member types
// Member 'value'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/UserIO in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__msg__UserIO
{
  int32_t offset;
  int32_t size;
  rosidl_runtime_c__uint8__Sequence value;
} denso_robot_core_interfaces__msg__UserIO;

// Struct for a sequence of denso_robot_core_interfaces__msg__UserIO.
typedef struct denso_robot_core_interfaces__msg__UserIO__Sequence
{
  denso_robot_core_interfaces__msg__UserIO * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__msg__UserIO__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__STRUCT_H_
