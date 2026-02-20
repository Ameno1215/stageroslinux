// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_motion_control:srv/InitRobot.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__STRUCT_H_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'model'
// Member 'planning_group'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/InitRobot in the package denso_motion_control.
typedef struct denso_motion_control__srv__InitRobot_Request
{
  /// e.g. "vs060", "cobotta", "hsr065"
  rosidl_runtime_c__String model;
  /// e.g. "arm"
  rosidl_runtime_c__String planning_group;
  /// 0.0..1.0
  double velocity_scale;
  /// 0.0..1.0
  double accel_scale;
} denso_motion_control__srv__InitRobot_Request;

// Struct for a sequence of denso_motion_control__srv__InitRobot_Request.
typedef struct denso_motion_control__srv__InitRobot_Request__Sequence
{
  denso_motion_control__srv__InitRobot_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__InitRobot_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/InitRobot in the package denso_motion_control.
typedef struct denso_motion_control__srv__InitRobot_Response
{
  bool success;
  rosidl_runtime_c__String message;
} denso_motion_control__srv__InitRobot_Response;

// Struct for a sequence of denso_motion_control__srv__InitRobot_Response.
typedef struct denso_motion_control__srv__InitRobot_Response__Sequence
{
  denso_motion_control__srv__InitRobot_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_motion_control__srv__InitRobot_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__STRUCT_H_
