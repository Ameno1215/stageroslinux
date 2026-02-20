// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/GetCurrentPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__STRUCT_H_

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
// Member 'child_frame_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetCurrentPose in the package denso_motion_control.
typedef struct denso_motion_control__srv__GetCurrentPose_Request
{
  /// Reference frame (e.g., "world"). Default if empty: "world"
  rosidl_runtime_c__String frame_id;
  /// Target frame (e.g., "tool_link"). Default if empty: End-Effector
  rosidl_runtime_c__String child_frame_id;
} denso_motion_control__srv__GetCurrentPose_Request;

// Struct for a sequence of denso_motion_control__srv__GetCurrentPose_Request.
typedef struct denso_motion_control__srv__GetCurrentPose_Request__Sequence
{
  denso_motion_control__srv__GetCurrentPose_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__GetCurrentPose_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"
// Member 'euler_rpy'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/GetCurrentPose in the package denso_motion_control.
typedef struct denso_motion_control__srv__GetCurrentPose_Response
{
  bool success;
  rosidl_runtime_c__String message;
  /// Standard Pose (Position + Quaternion)
  geometry_msgs__msg__PoseStamped pose;
  /// Euler Angles [roll, pitch, yaw] in radians (Fixed XYZ)
  rosidl_runtime_c__double__Sequence euler_rpy;
} denso_motion_control__srv__GetCurrentPose_Response;

// Struct for a sequence of denso_motion_control__srv__GetCurrentPose_Response.
typedef struct denso_motion_control__srv__GetCurrentPose_Response__Sequence
{
  denso_motion_control__srv__GetCurrentPose_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__GetCurrentPose_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__STRUCT_H_
