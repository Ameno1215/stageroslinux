// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "bcap_service_interfaces/srv/detail/bcap__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace bcap_service_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void Bcap_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) bcap_service_interfaces::srv::Bcap_Request(_init);
}

void Bcap_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<bcap_service_interfaces::srv::Bcap_Request *>(message_memory);
  typed_message->~Bcap_Request();
}

size_t size_function__Bcap_Request__vnt_args(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<bcap_service_interfaces::msg::Variant> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Bcap_Request__vnt_args(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<bcap_service_interfaces::msg::Variant> *>(untyped_member);
  return &member[index];
}

void * get_function__Bcap_Request__vnt_args(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<bcap_service_interfaces::msg::Variant> *>(untyped_member);
  return &member[index];
}

void fetch_function__Bcap_Request__vnt_args(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const bcap_service_interfaces::msg::Variant *>(
    get_const_function__Bcap_Request__vnt_args(untyped_member, index));
  auto & value = *reinterpret_cast<bcap_service_interfaces::msg::Variant *>(untyped_value);
  value = item;
}

void assign_function__Bcap_Request__vnt_args(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<bcap_service_interfaces::msg::Variant *>(
    get_function__Bcap_Request__vnt_args(untyped_member, index));
  const auto & value = *reinterpret_cast<const bcap_service_interfaces::msg::Variant *>(untyped_value);
  item = value;
}

void resize_function__Bcap_Request__vnt_args(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<bcap_service_interfaces::msg::Variant> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Bcap_Request_message_member_array[2] = {
  {
    "func_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces::srv::Bcap_Request, func_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "vnt_args",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<bcap_service_interfaces::msg::Variant>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces::srv::Bcap_Request, vnt_args),  // bytes offset in struct
    nullptr,  // default value
    size_function__Bcap_Request__vnt_args,  // size() function pointer
    get_const_function__Bcap_Request__vnt_args,  // get_const(index) function pointer
    get_function__Bcap_Request__vnt_args,  // get(index) function pointer
    fetch_function__Bcap_Request__vnt_args,  // fetch(index, &value) function pointer
    assign_function__Bcap_Request__vnt_args,  // assign(index, value) function pointer
    resize_function__Bcap_Request__vnt_args  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Bcap_Request_message_members = {
  "bcap_service_interfaces::srv",  // message namespace
  "Bcap_Request",  // message name
  2,  // number of fields
  sizeof(bcap_service_interfaces::srv::Bcap_Request),
  Bcap_Request_message_member_array,  // message members
  Bcap_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  Bcap_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Bcap_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Bcap_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace bcap_service_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<bcap_service_interfaces::srv::Bcap_Request>()
{
  return &::bcap_service_interfaces::srv::rosidl_typesupport_introspection_cpp::Bcap_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, bcap_service_interfaces, srv, Bcap_Request)() {
  return &::bcap_service_interfaces::srv::rosidl_typesupport_introspection_cpp::Bcap_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace bcap_service_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void Bcap_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) bcap_service_interfaces::srv::Bcap_Response(_init);
}

void Bcap_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<bcap_service_interfaces::srv::Bcap_Response *>(message_memory);
  typed_message->~Bcap_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Bcap_Response_message_member_array[2] = {
  {
    "hresult",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces::srv::Bcap_Response, hresult),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "vnt_ret",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<bcap_service_interfaces::msg::Variant>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(bcap_service_interfaces::srv::Bcap_Response, vnt_ret),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Bcap_Response_message_members = {
  "bcap_service_interfaces::srv",  // message namespace
  "Bcap_Response",  // message name
  2,  // number of fields
  sizeof(bcap_service_interfaces::srv::Bcap_Response),
  Bcap_Response_message_member_array,  // message members
  Bcap_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  Bcap_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Bcap_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Bcap_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace bcap_service_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<bcap_service_interfaces::srv::Bcap_Response>()
{
  return &::bcap_service_interfaces::srv::rosidl_typesupport_introspection_cpp::Bcap_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, bcap_service_interfaces, srv, Bcap_Response)() {
  return &::bcap_service_interfaces::srv::rosidl_typesupport_introspection_cpp::Bcap_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "bcap_service_interfaces/srv/detail/bcap__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace bcap_service_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers Bcap_service_members = {
  "bcap_service_interfaces::srv",  // service namespace
  "Bcap",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<bcap_service_interfaces::srv::Bcap>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t Bcap_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Bcap_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace bcap_service_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<bcap_service_interfaces::srv::Bcap>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::bcap_service_interfaces::srv::rosidl_typesupport_introspection_cpp::Bcap_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::bcap_service_interfaces::srv::Bcap_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::bcap_service_interfaces::srv::Bcap_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, bcap_service_interfaces, srv, Bcap)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<bcap_service_interfaces::srv::Bcap>();
}

#ifdef __cplusplus
}
#endif
