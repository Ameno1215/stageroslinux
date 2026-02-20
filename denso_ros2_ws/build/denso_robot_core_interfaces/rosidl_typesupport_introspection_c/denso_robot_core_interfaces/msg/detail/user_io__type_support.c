// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from denso_robot_core_interfaces:msg/UserIO.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "denso_robot_core_interfaces/msg/detail/user_io__rosidl_typesupport_introspection_c.h"
#include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "denso_robot_core_interfaces/msg/detail/user_io__functions.h"
#include "denso_robot_core_interfaces/msg/detail/user_io__struct.h"


// Include directives for member types
// Member `value`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__msg__UserIO__init(message_memory);
}

void denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__msg__UserIO__fini(message_memory);
}

size_t denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__size_function__UserIO__value(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__get_const_function__UserIO__value(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__get_function__UserIO__value(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__fetch_function__UserIO__value(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__get_const_function__UserIO__value(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__assign_function__UserIO__value(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__get_function__UserIO__value(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__resize_function__UserIO__value(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_member_array[3] = {
  {
    "offset",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__msg__UserIO, offset),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "size",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__msg__UserIO, size),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "value",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__msg__UserIO, value),  // bytes offset in struct
    NULL,  // default value
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__size_function__UserIO__value,  // size() function pointer
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__get_const_function__UserIO__value,  // get_const(index) function pointer
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__get_function__UserIO__value,  // get(index) function pointer
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__fetch_function__UserIO__value,  // fetch(index, &value) function pointer
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__assign_function__UserIO__value,  // assign(index, value) function pointer
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__resize_function__UserIO__value  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_members = {
  "denso_robot_core_interfaces__msg",  // message namespace
  "UserIO",  // message name
  3,  // number of fields
  sizeof(denso_robot_core_interfaces__msg__UserIO),
  denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_member_array,  // message members
  denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, msg, UserIO)() {
  if (!denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__msg__UserIO__rosidl_typesupport_introspection_c__UserIO_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
