// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from denso_robot_core_interfaces:action/DriveValue.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
#include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
#include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `pose`
#include "denso_robot_core_interfaces/msg/joints.h"
// Member `pose`
#include "denso_robot_core_interfaces/msg/detail/joints__rosidl_typesupport_introspection_c.h"
// Member `option`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_Goal__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_Goal__fini(message_memory);
}

size_t denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__size_function__DriveValue_Goal__pose(
  const void * untyped_member)
{
  const denso_robot_core_interfaces__msg__Joints__Sequence * member =
    (const denso_robot_core_interfaces__msg__Joints__Sequence *)(untyped_member);
  return member->size;
}

const void * denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__get_const_function__DriveValue_Goal__pose(
  const void * untyped_member, size_t index)
{
  const denso_robot_core_interfaces__msg__Joints__Sequence * member =
    (const denso_robot_core_interfaces__msg__Joints__Sequence *)(untyped_member);
  return &member->data[index];
}

void * denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__get_function__DriveValue_Goal__pose(
  void * untyped_member, size_t index)
{
  denso_robot_core_interfaces__msg__Joints__Sequence * member =
    (denso_robot_core_interfaces__msg__Joints__Sequence *)(untyped_member);
  return &member->data[index];
}

void denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__fetch_function__DriveValue_Goal__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const denso_robot_core_interfaces__msg__Joints * item =
    ((const denso_robot_core_interfaces__msg__Joints *)
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__get_const_function__DriveValue_Goal__pose(untyped_member, index));
  denso_robot_core_interfaces__msg__Joints * value =
    (denso_robot_core_interfaces__msg__Joints *)(untyped_value);
  *value = *item;
}

void denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__assign_function__DriveValue_Goal__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  denso_robot_core_interfaces__msg__Joints * item =
    ((denso_robot_core_interfaces__msg__Joints *)
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__get_function__DriveValue_Goal__pose(untyped_member, index));
  const denso_robot_core_interfaces__msg__Joints * value =
    (const denso_robot_core_interfaces__msg__Joints *)(untyped_value);
  *item = *value;
}

bool denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__resize_function__DriveValue_Goal__pose(
  void * untyped_member, size_t size)
{
  denso_robot_core_interfaces__msg__Joints__Sequence * member =
    (denso_robot_core_interfaces__msg__Joints__Sequence *)(untyped_member);
  denso_robot_core_interfaces__msg__Joints__Sequence__fini(member);
  return denso_robot_core_interfaces__msg__Joints__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_member_array[3] = {
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_Goal, pose),  // bytes offset in struct
    NULL,  // default value
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__size_function__DriveValue_Goal__pose,  // size() function pointer
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__get_const_function__DriveValue_Goal__pose,  // get_const(index) function pointer
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__get_function__DriveValue_Goal__pose,  // get(index) function pointer
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__fetch_function__DriveValue_Goal__pose,  // fetch(index, &value) function pointer
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__assign_function__DriveValue_Goal__pose,  // assign(index, value) function pointer
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__resize_function__DriveValue_Goal__pose  // resize(index) function pointer
  },
  {
    "passflag",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_Goal, passflag),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "option",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_Goal, option),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_Goal",  // message name
  3,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_Goal),
  denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_Goal)() {
  denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, msg, Joints)();
  if (!denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_Goal__rosidl_typesupport_introspection_c__DriveValue_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_Result__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_Result__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_member_array[1] = {
  {
    "hresult",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_Result, hresult),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_Result",  // message name
  1,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_Result),
  denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_Result)() {
  if (!denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_Result__rosidl_typesupport_introspection_c__DriveValue_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `pose`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_Feedback__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_Feedback__fini(message_memory);
}

size_t denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__size_function__DriveValue_Feedback__pose(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__get_const_function__DriveValue_Feedback__pose(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__get_function__DriveValue_Feedback__pose(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__fetch_function__DriveValue_Feedback__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__get_const_function__DriveValue_Feedback__pose(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__assign_function__DriveValue_Feedback__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__get_function__DriveValue_Feedback__pose(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__resize_function__DriveValue_Feedback__pose(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_member_array[1] = {
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_Feedback, pose),  // bytes offset in struct
    NULL,  // default value
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__size_function__DriveValue_Feedback__pose,  // size() function pointer
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__get_const_function__DriveValue_Feedback__pose,  // get_const(index) function pointer
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__get_function__DriveValue_Feedback__pose,  // get(index) function pointer
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__fetch_function__DriveValue_Feedback__pose,  // fetch(index, &value) function pointer
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__assign_function__DriveValue_Feedback__pose,  // assign(index, value) function pointer
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__resize_function__DriveValue_Feedback__pose  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_Feedback",  // message name
  1,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_Feedback),
  denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_Feedback)() {
  if (!denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_Feedback__rosidl_typesupport_introspection_c__DriveValue_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "denso_robot_core_interfaces/action/drive_value.h"
// Member `goal`
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_SendGoal_Request),
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal_Request)() {
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_Goal)();
  if (!denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_SendGoal_Request__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_SendGoal_Response),
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal_Response)() {
  denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_SendGoal_Response__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_members = {
  "denso_robot_core_interfaces__action",  // service namespace
  "DriveValue_SendGoal",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Request_message_type_support_handle,
  NULL  // response message
  // denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_Response_message_type_support_handle
};

static rosidl_service_type_support_t denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal)() {
  if (!denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_SendGoal_Response)()->data;
  }

  return &denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_GetResult_Request__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_GetResult_Request),
  denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult_Request)() {
  denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_GetResult_Request__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "denso_robot_core_interfaces/action/drive_value.h"
// Member `result`
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_GetResult_Response__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_GetResult_Response),
  denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult_Response)() {
  denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_Result)();
  if (!denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_GetResult_Response__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_members = {
  "denso_robot_core_interfaces__action",  // service namespace
  "DriveValue_GetResult",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_Request_message_type_support_handle,
  NULL  // response message
  // denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_Response_message_type_support_handle
};

static rosidl_service_type_support_t denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult)() {
  if (!denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_GetResult_Response)()->data;
  }

  return &denso_robot_core_interfaces__action__detail__drive_value__rosidl_typesupport_introspection_c__DriveValue_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"
// already included above
// #include "denso_robot_core_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__functions.h"
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "denso_robot_core_interfaces/action/drive_value.h"
// Member `feedback`
// already included above
// #include "denso_robot_core_interfaces/action/detail/drive_value__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__init(message_memory);
}

void denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_fini_function(void * message_memory)
{
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(denso_robot_core_interfaces__action__DriveValue_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_members = {
  "denso_robot_core_interfaces__action",  // message namespace
  "DriveValue_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(denso_robot_core_interfaces__action__DriveValue_FeedbackMessage),
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_member_array,  // message members
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_type_support_handle = {
  0,
  &denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_FeedbackMessage)() {
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, denso_robot_core_interfaces, action, DriveValue_Feedback)();
  if (!denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &denso_robot_core_interfaces__action__DriveValue_FeedbackMessage__rosidl_typesupport_introspection_c__DriveValue_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
