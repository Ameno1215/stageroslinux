// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from denso_robot_core_interfaces:msg/ExJoints.idl
// generated code does not contain a copyright notice
#include "denso_robot_core_interfaces/msg/detail/ex_joints__rosidl_typesupport_fastrtps_cpp.hpp"
#include "denso_robot_core_interfaces/msg/detail/ex_joints__struct.hpp"

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
namespace denso_robot_core_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const denso_robot_core_interfaces::msg::Joints &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  denso_robot_core_interfaces::msg::Joints &);
size_t get_serialized_size(
  const denso_robot_core_interfaces::msg::Joints &,
  size_t current_alignment);
size_t
max_serialized_size_Joints(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
cdr_serialize(
  const denso_robot_core_interfaces::msg::ExJoints & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: mode
  cdr << ros_message.mode;
  // Member: joints
  {
    size_t size = ros_message.joints.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.joints[i],
        cdr);
    }
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  denso_robot_core_interfaces::msg::ExJoints & ros_message)
{
  // Member: mode
  cdr >> ros_message.mode;

  // Member: joints
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.joints.resize(size);
    for (size_t i = 0; i < size; i++) {
      denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.joints[i]);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
get_serialized_size(
  const denso_robot_core_interfaces::msg::ExJoints & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: mode
  {
    size_t item_size = sizeof(ros_message.mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: joints
  {
    size_t array_size = ros_message.joints.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.joints[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
max_serialized_size_ExJoints(
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


  // Member: mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: joints
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
        denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Joints(
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
    using DataType = denso_robot_core_interfaces::msg::ExJoints;
    is_plain =
      (
      offsetof(DataType, joints) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ExJoints__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const denso_robot_core_interfaces::msg::ExJoints *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ExJoints__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<denso_robot_core_interfaces::msg::ExJoints *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ExJoints__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const denso_robot_core_interfaces::msg::ExJoints *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ExJoints__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ExJoints(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ExJoints__callbacks = {
  "denso_robot_core_interfaces::msg",
  "ExJoints",
  _ExJoints__cdr_serialize,
  _ExJoints__cdr_deserialize,
  _ExJoints__get_serialized_size,
  _ExJoints__max_serialized_size
};

static rosidl_message_type_support_t _ExJoints__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ExJoints__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace denso_robot_core_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_denso_robot_core_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<denso_robot_core_interfaces::msg::ExJoints>()
{
  return &denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::_ExJoints__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, denso_robot_core_interfaces, msg, ExJoints)() {
  return &denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::_ExJoints__handle;
}

#ifdef __cplusplus
}
#endif
