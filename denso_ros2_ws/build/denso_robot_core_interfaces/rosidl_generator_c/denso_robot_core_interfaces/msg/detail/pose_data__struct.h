// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_robot_core_interfaces:msg/PoseData.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__STRUCT_H_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'value'
#include "rosidl_runtime_c/primitives_sequence.h"
// Member 'exjoints'
#include "denso_robot_core_interfaces/msg/detail/ex_joints__struct.h"

/// Struct defined in msg/PoseData in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__msg__PoseData
{
  rosidl_runtime_c__float__Sequence value;
  int32_t type;
  int32_t passflag;
  denso_robot_core_interfaces__msg__ExJoints exjoints;
} denso_robot_core_interfaces__msg__PoseData;

// Struct for a sequence of denso_robot_core_interfaces__msg__PoseData.
typedef struct denso_robot_core_interfaces__msg__PoseData__Sequence
{
  denso_robot_core_interfaces__msg__PoseData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__msg__PoseData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__STRUCT_H_
