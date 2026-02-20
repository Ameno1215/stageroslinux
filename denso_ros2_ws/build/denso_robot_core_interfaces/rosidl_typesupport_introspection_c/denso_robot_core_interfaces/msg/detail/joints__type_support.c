// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from denso_robot_core_interfaces:msg/Joints.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "denso_robot_core_interfaces/msg/detail/joints__rosidl_typesupport_introspection_c.h"
#include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "denso_robot_core_interfaces/msg/detail/joints__functions.h"
#include "denso_robot_core_interfaces/msg/detail/joints__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__msg__Joints__init(message_memory);
}

void denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__msg__Joints__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_member_array[2] = {
  {
    "joint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__msg__Joints, joint),  // bytes offset in struct
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
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__msg__Joints, value),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_members = {
  "denso_robot_core_interfaces__msg",  // message namespace
  "Joints",  // message name
  2,  // number of fields
  sizeof(denso_robot_core_interfaces__msg__Joints),
  denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_member_array,  // message members
  denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, msg, Joints)() {
  if (!denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__msg__Joints__rosidl_typesupport_introspection_c__Joints_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
