// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "bcap_service_interfaces/srv/detail/bcap__rosidl_typesupport_introspection_c.h"
#include "bcap_service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "bcap_service_interfaces/srv/detail/bcap__functions.h"
#include "bcap_service_interfaces/srv/detail/bcap__struct.h"


// Include directives for member types
// Member `vnt_args`
#include "bcap_service_interfaces/msg/variant.h"
// Member `vnt_args`
#include "bcap_service_interfaces/msg/detail/variant__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  bcap_service_interfaces__srv__Bcap_Request__init(message_memory);
}

void bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_fini_function(void * message_memory)
{
  bcap_service_interfaces__srv__Bcap_Request__fini(message_memory);
}

size_t bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__size_function__Bcap_Request__vnt_args(
  const void * untyped_member)
{
  const bcap_service_interfaces__msg__Variant__Sequence * member =
    (const bcap_service_interfaces__msg__Variant__Sequence *)(untyped_member);
  return member->size;
}

const void * bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__get_const_function__Bcap_Request__vnt_args(
  const void * untyped_member, size_t index)
{
  const bcap_service_interfaces__msg__Variant__Sequence * member =
    (const bcap_service_interfaces__msg__Variant__Sequence *)(untyped_member);
  return &member->data[index];
}

void * bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__get_function__Bcap_Request__vnt_args(
  void * untyped_member, size_t index)
{
  bcap_service_interfaces__msg__Variant__Sequence * member =
    (bcap_service_interfaces__msg__Variant__Sequence *)(untyped_member);
  return &member->data[index];
}

void bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__fetch_function__Bcap_Request__vnt_args(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bcap_service_interfaces__msg__Variant * item =
    ((const bcap_service_interfaces__msg__Variant *)
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__get_const_function__Bcap_Request__vnt_args(untyped_member, index));
  bcap_service_interfaces__msg__Variant * value =
    (bcap_service_interfaces__msg__Variant *)(untyped_value);
  *value = *item;
}

void bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__assign_function__Bcap_Request__vnt_args(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bcap_service_interfaces__msg__Variant * item =
    ((bcap_service_interfaces__msg__Variant *)
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__get_function__Bcap_Request__vnt_args(untyped_member, index));
  const bcap_service_interfaces__msg__Variant * value =
    (const bcap_service_interfaces__msg__Variant *)(untyped_value);
  *item = *value;
}

bool bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__resize_function__Bcap_Request__vnt_args(
  void * untyped_member, size_t size)
{
  bcap_service_interfaces__msg__Variant__Sequence * member =
    (bcap_service_interfaces__msg__Variant__Sequence *)(untyped_member);
  bcap_service_interfaces__msg__Variant__Sequence__fini(member);
  return bcap_service_interfaces__msg__Variant__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_member_array[2] = {
  {
    "func_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces__srv__Bcap_Request, func_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vnt_args",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces__srv__Bcap_Request, vnt_args),  // bytes offset in struct
    NULL,  // default value
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__size_function__Bcap_Request__vnt_args,  // size() function pointer
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__get_const_function__Bcap_Request__vnt_args,  // get_const(index) function pointer
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__get_function__Bcap_Request__vnt_args,  // get(index) function pointer
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__fetch_function__Bcap_Request__vnt_args,  // fetch(index, &value) function pointer
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__assign_function__Bcap_Request__vnt_args,  // assign(index, value) function pointer
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__resize_function__Bcap_Request__vnt_args  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_members = {
  "bcap_service_interfaces__srv",  // message namespace
  "Bcap_Request",  // message name
  2,  // number of fields
  sizeof(bcap_service_interfaces__srv__Bcap_Request),
  bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_member_array,  // message members
  bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_type_support_handle = {
  0,
  &bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_bcap_service_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap_Request)() {
  bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, msg, Variant)();
  if (!bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_type_support_handle.typesupport_identifier) {
    bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &bcap_service_interfaces__srv__Bcap_Request__rosidl_typesupport_introspection_c__Bcap_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__rosidl_typesupport_introspection_c.h"
// already included above
// #include "bcap_service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__functions.h"
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__struct.h"


// Include directives for member types
// Member `vnt_ret`
// already included above
// #include "bcap_service_interfaces/msg/variant.h"
// Member `vnt_ret`
// already included above
// #include "bcap_service_interfaces/msg/detail/variant__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  bcap_service_interfaces__srv__Bcap_Response__init(message_memory);
}

void bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_fini_function(void * message_memory)
{
  bcap_service_interfaces__srv__Bcap_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_member_array[2] = {
  {
    "hresult",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces__srv__Bcap_Response, hresult),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "vnt_ret",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces__srv__Bcap_Response, vnt_ret),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_members = {
  "bcap_service_interfaces__srv",  // message namespace
  "Bcap_Response",  // message name
  2,  // number of fields
  sizeof(bcap_service_interfaces__srv__Bcap_Response),
  bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_member_array,  // message members
  bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_type_support_handle = {
  0,
  &bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_bcap_service_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap_Response)() {
  bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, msg, Variant)();
  if (!bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_type_support_handle.typesupport_identifier) {
    bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &bcap_service_interfaces__srv__Bcap_Response__rosidl_typesupport_introspection_c__Bcap_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "bcap_service_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_members = {
  "bcap_service_interfaces__srv",  // service namespace
  "Bcap",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_Request_message_type_support_handle,
  NULL  // response message
  // bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_Response_message_type_support_handle
};

static rosidl_service_type_support_t bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_type_support_handle = {
  0,
  &bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_bcap_service_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap)() {
  if (!bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_type_support_handle.typesupport_identifier) {
    bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, bcap_service_interfaces, srv, Bcap_Response)()->data;
  }

  return &bcap_service_interfaces__srv__detail__bcap__rosidl_typesupport_introspection_c__Bcap_service_type_support_handle;
}
