// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from denso_robot_core_interfaces:srv/ChangeMode.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__STRUCT_H_
#define DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ChangeMode in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__srv__ChangeMode_Request
{
  int32_t mode;
} denso_robot_core_interfaces__srv__ChangeMode_Request;

// Struct for a sequence of denso_robot_core_interfaces__srv__ChangeMode_Request.
typedef struct denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence
{
  denso_robot_core_interfaces__srv__ChangeMode_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__srv__ChangeMode_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/ChangeMode in the package denso_robot_core_interfaces.
typedef struct denso_robot_core_interfaces__srv__ChangeMode_Response
{
  int32_t hresult;
} denso_robot_core_interfaces__srv__ChangeMode_Response;

// Struct for a sequence of denso_robot_core_interfaces__srv__ChangeMode_Response.
typedef struct denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence
{
  denso_robot_core_interfaces__srv__ChangeMode_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} denso_robot_core_interfaces__srv__ChangeMode_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__STRUCT_H_
