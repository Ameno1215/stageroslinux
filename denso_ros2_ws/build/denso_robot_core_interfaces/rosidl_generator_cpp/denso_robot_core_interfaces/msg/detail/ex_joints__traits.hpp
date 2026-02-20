// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_robot_core_interfaces:msg/ExJoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__TRAITS_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_robot_core_interfaces/msg/detail/ex_joints__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'joints'
#include "denso_robot_core_interfaces/msg/detail/joints__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ExJoints & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: joints
  {
    if (msg.joints.size() == 0) {
      out << "joints: []";
    } else {
      out << "joints: [";
      size_t pending_items = msg.joints.size();
      for (auto item : msg.joints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ExJoints & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: joints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joints.size() == 0) {
      out << "joints: []\n";
    } else {
      out << "joints:\n";
      for (auto item : msg.joints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ExJoints & msg, bool use_flow_style = false)
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
  const denso_robot_core_interfaces::msg::ExJoints & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::msg::ExJoints & msg)
{
  return denso_robot_core_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::msg::ExJoints>()
{
  return "denso_robot_core_interfaces::msg::ExJoints";
}

template<>
inline const char * name<denso_robot_core_interfaces::msg::ExJoints>()
{
  return "denso_robot_core_interfaces/msg/ExJoints";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::msg::ExJoints>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::msg::ExJoints>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_robot_core_interfaces::msg::ExJoints>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__TRAITS_HPP_
