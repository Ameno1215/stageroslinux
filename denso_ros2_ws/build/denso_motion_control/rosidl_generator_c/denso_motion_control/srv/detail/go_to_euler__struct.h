// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/GoToEuler.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'frame_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GoToEuler in the package denso_motion_control.
typedef struct denso_motion_control__srv__GoToEuler_Request
{
  /// The reference frame (e.g., "world" or "base_link")
  rosidl_runtime_c__String frame_id;
  /// X Position (meters)
  double x;
  /// Y Position (meters)
  double y;
  /// Z Position (meters)
  double z;
  /// Rotation around X (radians) - Roll
  double rx;
  /// Rotation around Y (radians) - Pitch
  double ry;
  /// Rotation around Z (radians) - Yaw
  double rz;
  /// True = Move the robot, False = Plan only
  bool execute;
} denso_motion_control__srv__GoToEuler_Request;

// Struct for a sequence of denso_motion_control__srv__GoToEuler_Request.
typedef struct denso_motion_control__srv__GoToEuler_Request__Sequence
{
  denso_motion_control__srv__GoToEuler_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__GoToEuler_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GoToEuler in the package denso_motion_control.
typedef struct denso_motion_control__srv__GoToEuler_Response
{
  /// True if the operation was successful
  bool success;
  /// Success or error message
  rosidl_runtime_c__String message;
} denso_motion_control__srv__GoToEuler_Response;

// Struct for a sequence of denso_motion_control__srv__GoToEuler_Response.
typedef struct denso_motion_control__srv__GoToEuler_Response__Sequence
{
  denso_motion_control__srv__GoToEuler_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__GoToEuler_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__STRUCT_H_
