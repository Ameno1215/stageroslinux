// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/MoveToPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'rotation_format'
// Member 'reference_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MoveToPose in the package denso_motion_control.
typedef struct denso_motion_control__srv__MoveToPose_Request
{
  double x;
  double y;
  double z;
  /// Rotation (RPY = r1, r2, r3) ou (Quaternion = r1, r2, r3, r4)
  double r1;
  double r2;
  double r3;
  double r4;
  /// Configuration mathématique
  /// "QUAT" ou "RPY"
  rosidl_runtime_c__String rotation_format;
  /// "WORLD" ou "TOOL"
  rosidl_runtime_c__String reference_frame;
  /// Drapeaux de comportement
  /// True = mouvement relatif, False = cible absolue
  bool is_relative;
  /// True = ligne droite, False = mouvement articulaire fluide
  bool cartesian_path;
  /// True = planifie et bouge, False = planifie seulement
  bool execute;
} denso_motion_control__srv__MoveToPose_Request;

// Struct for a sequence of denso_motion_control__srv__MoveToPose_Request.
typedef struct denso_motion_control__srv__MoveToPose_Request__Sequence
{
  denso_motion_control__srv__MoveToPose_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__MoveToPose_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MoveToPose in the package denso_motion_control.
typedef struct denso_motion_control__srv__MoveToPose_Response
{
  bool success;
  rosidl_runtime_c__String message;
} denso_motion_control__srv__MoveToPose_Response;

// Struct for a sequence of denso_motion_control__srv__MoveToPose_Response.
typedef struct denso_motion_control__srv__MoveToPose_Response__Sequence
{
  denso_motion_control__srv__MoveToPose_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__MoveToPose_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__STRUCT_H_
