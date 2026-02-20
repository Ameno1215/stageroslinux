// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__STRUCT_H_
#define BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Variant in the package bcap_service_interfaces.
typedef struct bcap_service_interfaces__msg__Variant
{
  int16_t vt;
  rosidl_runtime_c__String value;
} bcap_service_interfaces__msg__Variant;

// Struct for a sequence of bcap_service_interfaces__msg__Variant.
typedef struct bcap_service_interfaces__msg__Variant__Sequence
{
  bcap_service_interfaces__msg__Variant * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bcap_service_interfaces__msg__Variant__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__STRUCT_H_
