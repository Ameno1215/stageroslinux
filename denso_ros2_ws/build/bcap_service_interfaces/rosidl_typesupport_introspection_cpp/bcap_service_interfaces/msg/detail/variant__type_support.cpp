// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "bcap_service_interfaces/msg/detail/variant__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace bcap_service_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Variant_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) bcap_service_interfaces::msg::Variant(_init);
}

void Variant_fini_function(void * message_memory)
{
  auto typed_message = static_cast<bcap_service_interfaces::msg::Variant *>(message_memory);
  typed_message->~Variant();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Variant_message_member_array[2] = {
  {
    "vt",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces::msg::Variant, vt),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "value",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces::msg::Variant, value),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Variant_message_members = {
  "bcap_service_interfaces::msg",  // message namespace
  "Variant",  // message name
  2,  // number of fields
  sizeof(bcap_service_interfaces::msg::Variant),
  Variant_message_member_array,  // message members
  Variant_init_function,  // function to initialize message memory (memory has to be allocated)
  Variant_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Variant_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Variant_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace bcap_service_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<bcap_service_interfaces::msg::Variant>()
{
  return &::bcap_service_interfaces::msg::rosidl_typesupport_introspection_cpp::Variant_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, bcap_service_interfaces, msg, Variant)() {
  return &::bcap_service_interfaces::msg::rosidl_typesupport_introspection_cpp::Variant_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
