// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from denso_robot_core_interfaces:srv/ChangeMode.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "denso_robot_core_interfaces/srv/detail/change_mode__rosidl_typesupport_introspection_c.h"
#include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "denso_robot_core_interfaces/srv/detail/change_mode__functions.h"
#include "denso_robot_core_interfaces/srv/detail/change_mode__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__srv__ChangeMode_Request__init(message_memory);
}

void denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__srv__ChangeMode_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_member_array[1] = {
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__srv__ChangeMode_Request, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_members = {
  "denso_robot_core_interfaces__srv",  // message namespace
  "ChangeMode_Request",  // message name
  1,  // number of fields
  sizeof(denso_robot_core_interfaces__srv__ChangeMode_Request),
  denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_member_array,  // message members
  denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode_Request)() {
  if (!denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__srv__ChangeMode_Request__rosidl_typesupport_introspection_c__ChangeMode_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/srv/detail/change_mode__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/srv/detail/change_mode__functions.h"
// already included above
// #include "denso_robot_core_interfaces/srv/detail/change_mode__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__srv__ChangeMode_Response__init(message_memory);
}

void denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__srv__ChangeMode_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_member_array[1] = {
  {
    "hresult",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__srv__ChangeMode_Response, hresult),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_members = {
  "denso_robot_core_interfaces__srv",  // message namespace
  "ChangeMode_Response",  // message name
  1,  // number of fields
  sizeof(denso_robot_core_interfaces__srv__ChangeMode_Response),
  denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_member_array,  // message members
  denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode_Response)() {
  if (!denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__srv__ChangeMode_Response__rosidl_typesupport_introspection_c__ChangeMode_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "denso_robot_core_interfaces/srv/detail/change_mode__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_members = {
  "denso_robot_core_interfaces__srv",  // service namespace
  "ChangeMode",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_Request_message_type_support_handle,
  NULL  // response message
  // denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_Response_message_type_support_handle
};

static rosidl_service_type_support_t denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_type_support_handle = {
  0,
  &denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode)() {
  if (!denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, srv, ChangeMode_Response)()->data;
  }

  return &denso_robot_core_interfaces__srv__detail__change_mode__rosidl_typesupport_introspection_c__ChangeMode_service_type_support_handle;
}
