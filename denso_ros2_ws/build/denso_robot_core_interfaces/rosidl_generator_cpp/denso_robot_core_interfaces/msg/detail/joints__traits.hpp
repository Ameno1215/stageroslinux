// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_robot_core_interfaces:msg/Joints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__TRAITS_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_robot_core_interfaces/msg/detail/joints__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_robot_core_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Joints & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint
  {
    out << "joint: ";
    rosidl_generator_traits::value_to_yaml(msg.joint, out);
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
  const Joints & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joint: ";
    rosidl_generator_traits::value_to_yaml(msg.joint, out);
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

inline std::string to_yaml(const Joints & msg, bool use_flow_style = false)
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

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::msg::Joints & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::msg::Joints & msg)
{
  return denso_robot_core_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::msg::Joints>()
{
  return "denso_robot_core_interfaces::msg::Joints";
}

template<>
inline const char * name<denso_robot_core_interfaces::msg::Joints>()
{
  return "denso_robot_core_interfaces/msg/Joints";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::msg::Joints>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::msg::Joints>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<denso_robot_core_interfaces::msg::Joints>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__TRAITS_HPP_
