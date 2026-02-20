// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "bcap_service_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "bcap_service_interfaces/msg/detail/variant__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace bcap_service_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
cdr_serialize(
  const bcap_service_interfaces::msg::Variant & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  bcap_service_interfaces::msg::Variant & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
get_serialized_size(
  const bcap_service_interfaces::msg::Variant & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
max_serialized_size_Variant(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace bcap_service_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_bcap_service_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, bcap_service_interfaces, msg, Variant)();

#ifdef __cplusplus
}
#endif

#endif  // BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
