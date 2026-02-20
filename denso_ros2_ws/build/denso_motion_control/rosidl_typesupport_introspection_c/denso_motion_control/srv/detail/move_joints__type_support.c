// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from denso_motion_control:srv/MoveJoints.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "denso_motion_control/srv/detail/move_joints__rosidl_typesupport_introspection_c.h"
#include "denso_motion_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "denso_motion_control/srv/detail/move_joints__functions.h"
#include "denso_motion_control/srv/detail/move_joints__struct.h"


// Include directives for member types
// Member `joints`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_motion_control__srv__MoveJoints_Request__init(message_memory);
}

void denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_fini_function(void * message_memory)
{
  denso_motion_control__srv__MoveJoints_Request__fini(message_memory);
}

size_t denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__size_function__MoveJoints_Request__joints(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__get_const_function__MoveJoints_Request__joints(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__get_function__MoveJoints_Request__joints(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__fetch_function__MoveJoints_Request__joints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__get_const_function__MoveJoints_Request__joints(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__assign_function__MoveJoints_Request__joints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__get_function__MoveJoints_Request__joints(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__resize_function__MoveJoints_Request__joints(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_member_array[3] = {
  {
    "joints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_motion_control__srv__MoveJoints_Request, joints),  // bytes offset in struct
    NULL,  // default value
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__size_function__MoveJoints_Request__joints,  // size() function pointer
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__get_const_function__MoveJoints_Request__joints,  // get_const(index) function pointer
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__get_function__MoveJoints_Request__joints,  // get(index) function pointer
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__fetch_function__MoveJoints_Request__joints,  // fetch(index, &value) function pointer
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__assign_function__MoveJoints_Request__joints,  // assign(index, value) function pointer
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__resize_function__MoveJoints_Request__joints  // resize(index) function pointer
  },
  {
    "is_relative",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_motion_control__srv__MoveJoints_Request, is_relative),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "execute",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_motion_control__srv__MoveJoints_Request, execute),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_members = {
  "denso_motion_control__srv",  // message namespace
  "MoveJoints_Request",  // message name
  3,  // number of fields
  sizeof(denso_motion_control__srv__MoveJoints_Request),
  denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_member_array,  // message members
  denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_type_support_handle = {
  0,
  &denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_motion_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints_Request)() {
  if (!denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_type_support_handle.typesupport_identifier) {
    denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_motion_control__srv__MoveJoints_Request__rosidl_typesupport_introspection_c__MoveJoints_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_motion_control/srv/detail/move_joints__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_motion_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_motion_control/srv/detail/move_joints__functions.h"
// already included above
// #include "denso_motion_control/srv/detail/move_joints__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_motion_control__srv__MoveJoints_Response__init(message_memory);
}

void denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_fini_function(void * message_memory)
{
  denso_motion_control__srv__MoveJoints_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_motion_control__srv__MoveJoints_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_motion_control__srv__MoveJoints_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_members = {
  "denso_motion_control__srv",  // message namespace
  "MoveJoints_Response",  // message name
  2,  // number of fields
  sizeof(denso_motion_control__srv__MoveJoints_Response),
  denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_member_array,  // message members
  denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_type_support_handle = {
  0,
  &denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_motion_control
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints_Response)() {
  if (!denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_type_support_handle.typesupport_identifier) {
    denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_motion_control__srv__MoveJoints_Response__rosidl_typesupport_introspection_c__MoveJoints_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "denso_motion_control/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "denso_motion_control/srv/detail/move_joints__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_members = {
  "denso_motion_control__srv",  // service namespace
  "MoveJoints",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_Request_message_type_support_handle,
  NULL  // response message
  // denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_Response_message_type_support_handle
};

static rosidl_service_type_support_t denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_type_support_handle = {
  0,
  &denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_motion_control
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints)() {
  if (!denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_type_support_handle.typesupport_identifier) {
    denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_motion_control, srv, MoveJoints_Response)()->data;
  }

  return &denso_motion_control__srv__detail__move_joints__rosidl_typesupport_introspection_c__MoveJoints_service_type_support_handle;
}
