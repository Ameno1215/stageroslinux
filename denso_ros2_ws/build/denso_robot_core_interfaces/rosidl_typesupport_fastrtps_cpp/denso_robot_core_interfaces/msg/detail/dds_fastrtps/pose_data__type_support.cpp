// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from denso_robot_core_interfaces:msg/PoseData.idl
// generated code does not contain a copyright notice
#include "denso_robot_core_interfaces/msg/detail/pose_data__rosidl_typesupport_fastrtps_cpp.hpp"
#include "denso_robot_core_interfaces/msg/detail/pose_data__struct.hpp"

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
  const denso_robot_core_interfaces::msg::ExJoints &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  denso_robot_core_interfaces::msg::ExJoints &);
size_t get_serialized_size(
  const denso_robot_core_interfaces::msg::ExJoints &,
  size_t current_alignment);
size_t
max_serialized_size_ExJoints(
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
  const denso_robot_core_interfaces::msg::PoseData & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: value
  {
    cdr << ros_message.value;
  }
  // Member: type
  cdr << ros_message.type;
  // Member: passflag
  cdr << ros_message.passflag;
  // Member: exjoints
  denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.exjoints,
    cdr);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  denso_robot_core_interfaces::msg::PoseData & ros_message)
{
  // Member: value
  {
    cdr >> ros_message.value;
  }

  // Member: type
  cdr >> ros_message.type;

  // Member: passflag
  cdr >> ros_message.passflag;

  // Member: exjoints
  denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.exjoints);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
get_serialized_size(
  const denso_robot_core_interfaces::msg::PoseData & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: value
  {
    size_t array_size = ros_message.value.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.value[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: type
  {
    size_t item_size = sizeof(ros_message.type);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: passflag
  {
    size_t item_size = sizeof(ros_message.passflag);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: exjoints

  current_alignment +=
    denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.exjoints, current_alignment);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_denso_robot_core_interfaces
max_serialized_size_PoseData(
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


  // Member: value
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: type
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: passflag
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: exjoints
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_ExJoints(
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
    using DataType = denso_robot_core_interfaces::msg::PoseData;
    is_plain =
      (
      offsetof(DataType, exjoints) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _PoseData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const denso_robot_core_interfaces::msg::PoseData *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _PoseData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<denso_robot_core_interfaces::msg::PoseData *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _PoseData__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const denso_robot_core_interfaces::msg::PoseData *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _PoseData__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_PoseData(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _PoseData__callbacks = {
  "denso_robot_core_interfaces::msg",
  "PoseData",
  _PoseData__cdr_serialize,
  _PoseData__cdr_deserialize,
  _PoseData__get_serialized_size,
  _PoseData__max_serialized_size
};

static rosidl_message_type_support_t _PoseData__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_PoseData__callbacks,
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
get_message_type_support_handle<denso_robot_core_interfaces::msg::PoseData>()
{
  return &denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::_PoseData__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, denso_robot_core_interfaces, msg, PoseData)() {
  return &denso_robot_core_interfaces::msg::typesupport_fastrtps_cpp::_PoseData__handle;
}

#ifdef __cplusplus
}
#endif
