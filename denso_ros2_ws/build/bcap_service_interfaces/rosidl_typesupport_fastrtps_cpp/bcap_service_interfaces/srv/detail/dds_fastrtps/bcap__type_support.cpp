// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice
#include "bcap_service_interfaces/srv/detail/bcap__rosidl_typesupport_fastrtps_cpp.hpp"
#include "bcap_service_interfaces/srv/detail/bcap__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace bcap_service_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const bcap_service_interfaces::msg::Variant &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  bcap_service_interfaces::msg::Variant &);
size_t get_serialized_size(
  const bcap_service_interfaces::msg::Variant &,
  size_t current_alignment);
size_t
max_serialized_size_Variant(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace bcap_service_interfaces


namespace bcap_service_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
cdr_serialize(
  const bcap_service_interfaces::srv::Bcap_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: func_id
  cdr << ros_message.func_id;
  // Member: vnt_args
  {
    size_t size = ros_message.vnt_args.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      bcap_service_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.vnt_args[i],
        cdr);
    }
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  bcap_service_interfaces::srv::Bcap_Request & ros_message)
{
  // Member: func_id
  cdr >> ros_message.func_id;

  // Member: vnt_args
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.vnt_args.resize(size);
    for (size_t i = 0; i < size; i++) {
      bcap_service_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.vnt_args[i]);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
get_serialized_size(
  const bcap_service_interfaces::srv::Bcap_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: func_id
  {
    size_t item_size = sizeof(ros_message.func_id);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: vnt_args
  {
    size_t array_size = ros_message.vnt_args.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        bcap_service_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.vnt_args[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
max_serialized_size_Bcap_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: func_id
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: vnt_args
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        bcap_service_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Variant(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = bcap_service_interfaces::srv::Bcap_Request;
    is_plain =
      (
      offsetof(DataType, vnt_args) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _Bcap_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const bcap_service_interfaces::srv::Bcap_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Bcap_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<bcap_service_interfaces::srv::Bcap_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Bcap_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const bcap_service_interfaces::srv::Bcap_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Bcap_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_Bcap_Request(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _Bcap_Request__callbacks = {
  "bcap_service_interfaces::srv",
  "Bcap_Request",
  _Bcap_Request__cdr_serialize,
  _Bcap_Request__cdr_deserialize,
  _Bcap_Request__get_serialized_size,
  _Bcap_Request__max_serialized_size
};

static rosidl_message_type_support_t _Bcap_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Bcap_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace bcap_service_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_bcap_service_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<bcap_service_interfaces::srv::Bcap_Request>()
{
  return &bcap_service_interfaces::srv::typesupport_fastrtps_cpp::_Bcap_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, bcap_service_interfaces, srv, Bcap_Request)() {
  return &bcap_service_interfaces::srv::typesupport_fastrtps_cpp::_Bcap_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
// functions for bcap_service_interfaces::msg::Variant already declared above


namespace bcap_service_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
cdr_serialize(
  const bcap_service_interfaces::srv::Bcap_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: hresult
  cdr << ros_message.hresult;
  // Member: vnt_ret
  bcap_service_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.vnt_ret,
    cdr);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  bcap_service_interfaces::srv::Bcap_Response & ros_message)
{
  // Member: hresult
  cdr >> ros_message.hresult;

  // Member: vnt_ret
  bcap_service_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.vnt_ret);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
get_serialized_size(
  const bcap_service_interfaces::srv::Bcap_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: hresult
  {
    size_t item_size = sizeof(ros_message.hresult);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: vnt_ret

  current_alignment +=
    bcap_service_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.vnt_ret, current_alignment);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
max_serialized_size_Bcap_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: hresult
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: vnt_ret
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        bcap_service_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Variant(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = bcap_service_interfaces::srv::Bcap_Response;
    is_plain =
      (
      offsetof(DataType, vnt_ret) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _Bcap_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const bcap_service_interfaces::srv::Bcap_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Bcap_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<bcap_service_interfaces::srv::Bcap_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Bcap_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const bcap_service_interfaces::srv::Bcap_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Bcap_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_Bcap_Response(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _Bcap_Response__callbacks = {
  "bcap_service_interfaces::srv",
  "Bcap_Response",
  _Bcap_Response__cdr_serialize,
  _Bcap_Response__cdr_deserialize,
  _Bcap_Response__get_serialized_size,
  _Bcap_Response__max_serialized_size
};

static rosidl_message_type_support_t _Bcap_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Bcap_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace bcap_service_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_bcap_service_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<bcap_service_interfaces::srv::Bcap_Response>()
{
  return &bcap_service_interfaces::srv::typesupport_fastrtps_cpp::_Bcap_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, bcap_service_interfaces, srv, Bcap_Response)() {
  return &bcap_service_interfaces::srv::typesupport_fastrtps_cpp::_Bcap_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace bcap_service_interfaces
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _Bcap__callbacks = {
  "bcap_service_interfaces::srv",
  "Bcap",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, bcap_service_interfaces, srv, Bcap_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, bcap_service_interfaces, srv, Bcap_Response)(),
};

static rosidl_service_type_support_t _Bcap__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Bcap__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace bcap_service_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_bcap_service_interfaces
const rosidl_service_type_support_t *
get_service_type_support_handle<bcap_service_interfaces::srv::Bcap>()
{
  return &bcap_service_interfaces::srv::typesupport_fastrtps_cpp::_Bcap__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, bcap_service_interfaces, srv, Bcap)() {
  return &bcap_service_interfaces::srv::typesupport_fastrtps_cpp::_Bcap__handle;
}

#ifdef __cplusplus
}
#endif
