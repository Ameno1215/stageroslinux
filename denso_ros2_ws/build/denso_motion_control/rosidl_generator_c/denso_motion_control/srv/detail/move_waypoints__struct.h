// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/MoveWaypoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'waypoints'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'reference_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MoveWaypoints in the package denso_motion_control.
typedef struct denso_motion_control__srv__MoveWaypoints_Request
{
  geometry_msgs__msg__Pose__Sequence waypoints;
  /// Configuration globale pour toute la trajectoire
  /// "WORLD" ou "TOOL"
  rosidl_runtime_c__String reference_frame;
  /// True = chaque point est relatif au précédent
  bool is_relative;
  /// True = relie les points en lignes droites, False = courbe fluide
  bool cartesian_path;
  /// True = planifie et bouge, False = planifie seulement
  bool execute;
} denso_motion_control__srv__MoveWaypoints_Request;

// Struct for a sequence of denso_motion_control__srv__MoveWaypoints_Request.
typedef struct denso_motion_control__srv__MoveWaypoints_Request__Sequence
{
  denso_motion_control__srv__MoveWaypoints_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__MoveWaypoints_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/MoveWaypoints in the package denso_motion_control.
typedef struct denso_motion_control__srv__MoveWaypoints_Response
{
  bool success;
  rosidl_runtime_c__String message;
} denso_motion_control__srv__MoveWaypoints_Response;

// Struct for a sequence of denso_motion_control__srv__MoveWaypoints_Response.
typedef struct denso_motion_control__srv__MoveWaypoints_Response__Sequence
{
  denso_motion_control__srv__MoveWaypoints_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__MoveWaypoints_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__STRUCT_H_
