// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/GoToPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_POSE__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in srv/GoToPose in the package denso_motion_control.
typedef struct denso_motion_control__srv__GoToPose_Request
{
  geometry_msgs__msg__PoseStamped target;
  /// if false: plan only
  bool execute;
} denso_motion_control__srv__GoToPose_Request;

// Struct for a sequence of denso_motion_control__srv__GoToPose_Request.
typedef struct denso_motion_control__srv__GoToPose_Request__Sequence
{
  denso_motion_control__srv__GoToPose_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__GoToPose_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GoToPose in the package denso_motion_control.
typedef struct denso_motion_control__srv__GoToPose_Response
{
  bool success;
  rosidl_runtime_c__String message;
} denso_motion_control__srv__GoToPose_Response;

// Struct for a sequence of denso_motion_control__srv__GoToPose_Response.
typedef struct denso_motion_control__srv__GoToPose_Response__Sequence
{
  denso_motion_control__srv__GoToPose_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__GoToPose_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_POSE__STRUCT_H_
