// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/MoveJoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_JOINTS__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_JOINTS__STRUCT_H_

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
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/MoveJoints in the package denso_motion_control.
typedef struct denso_motion_control__srv__MoveJoints_Request
{
  /// Tableau des valeurs cibles (en radians)
  rosidl_runtime_c__double__Sequence joints;
  /// True = ajoute ces angles aux angles actuels, False = va à ces angles absolus
  bool is_relative;
  /// True = planifie et bouge, False = planifie seulement
  bool execute;
} denso_motion_control__srv__MoveJoints_Request;

// Struct for a sequence of denso_motion_control__srv__MoveJoints_Request.
typedef struct denso_motion_control__srv__MoveJoints_Request__Sequence
{
  denso_motion_control__srv__MoveJoints_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__MoveJoints_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MoveJoints in the package denso_motion_control.
typedef struct denso_motion_control__srv__MoveJoints_Response
{
  bool success;
  rosidl_runtime_c__String message;
} denso_motion_control__srv__MoveJoints_Response;

// Struct for a sequence of denso_motion_control__srv__MoveJoints_Response.
typedef struct denso_motion_control__srv__MoveJoints_Response__Sequence
{
  denso_motion_control__srv__MoveJoints_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__MoveJoints_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_JOINTS__STRUCT_H_
