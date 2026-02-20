// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__TRAITS_HPP_
#define BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "bcap_service_interfaces/msg/detail/variant__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace bcap_service_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Variant & msg,
  std::ostream & out)
{
  out << "{";
  // member: vt
  {
    out << "vt: ";
    rosidl_generator_traits::value_to_yaml(msg.vt, out);
    out << ", ";
  }

  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Variant & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: vt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vt: ";
    rosidl_generator_traits::value_to_yaml(msg.vt, out);
    out << "\n";
  }

  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Variant & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace bcap_service_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use bcap_service_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bcap_service_interfaces::msg::Variant & msg,
  std::ostream & out, size_t indentation = 0)
{
  bcap_service_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bcap_service_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const bcap_service_interfaces::msg::Variant & msg)
{
  return bcap_service_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<bcap_service_interfaces::msg::Variant>()
{
  return "bcap_service_interfaces::msg::Variant";
}

template<>
inline const char * name<bcap_service_interfaces::msg::Variant>()
{
  return "bcap_service_interfaces/msg/Variant";
}

template<>
struct has_fixed_size<bcap_service_interfaces::msg::Variant>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<bcap_service_interfaces::msg::Variant>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<bcap_service_interfaces::msg::Variant>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__TRAITS_HPP_
