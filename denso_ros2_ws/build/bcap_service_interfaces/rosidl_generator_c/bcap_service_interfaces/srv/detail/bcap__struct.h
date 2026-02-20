// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__STRUCT_H_
#define BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'vnt_args'
#include "bcap_service_interfaces/msg/detail/variant__struct.h"

/// Struct defined in srv/Bcap in the package bcap_service_interfaces.
typedef struct bcap_service_interfaces__srv__Bcap_Request
{
  int32_t func_id;
  bcap_service_interfaces__msg__Variant__Sequence vnt_args;
} bcap_service_interfaces__srv__Bcap_Request;

// Struct for a sequence of bcap_service_interfaces__srv__Bcap_Request.
typedef struct bcap_service_interfaces__srv__Bcap_Request__Sequence
{
  bcap_service_interfaces__srv__Bcap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bcap_service_interfaces__srv__Bcap_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'vnt_ret'
// already included above
// #include "bcap_service_interfaces/msg/detail/variant__struct.h"

/// Struct defined in srv/Bcap in the package bcap_service_interfaces.
typedef struct bcap_service_interfaces__srv__Bcap_Response
{
  int32_t hresult;
  bcap_service_interfaces__msg__Variant vnt_ret;
} bcap_service_interfaces__srv__Bcap_Response;

// Struct for a sequence of bcap_service_interfaces__srv__Bcap_Response.
typedef struct bcap_service_interfaces__srv__Bcap_Response__Sequence
{
  bcap_service_interfaces__srv__Bcap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bcap_service_interfaces__srv__Bcap_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__STRUCT_H_
