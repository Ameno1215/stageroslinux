// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_robot_core_interfaces:msg/PoseData.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__TRAITS_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_robot_core_interfaces/msg/detail/pose_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'exjoints'
#include "denso_robot_core_interfaces/msg/detail/ex_joints__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const PoseData & msg,
  std::ostream & out)
{
  out << "{";
  // member: value
  {
    if (msg.value.size() == 0) {
      out << "value: []";
    } else {
      out << "value: [";
      size_t pending_items = msg.value.size();
      for (auto item : msg.value) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: passflag
  {
    out << "passflag: ";
    rosidl_generator_traits::value_to_yaml(msg.passflag, out);
    out << ", ";
  }

  // member: exjoints
  {
    out << "exjoints: ";
    to_flow_style_yaml(msg.exjoints, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PoseData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.value.size() == 0) {
      out << "value: []\n";
    } else {
      out << "value:\n";
      for (auto item : msg.value) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: passflag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "passflag: ";
    rosidl_generator_traits::value_to_yaml(msg.passflag, out);
    out << "\n";
  }

  // member: exjoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "exjoints:\n";
    to_block_style_yaml(msg.exjoints, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PoseData & msg, bool use_flow_style = false)
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
  const denso_robot_core_interfaces::msg::PoseData & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::msg::PoseData & msg)
{
  return denso_robot_core_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::msg::PoseData>()
{
  return "denso_robot_core_interfaces::msg::PoseData";
}

template<>
inline const char * name<denso_robot_core_interfaces::msg::PoseData>()
{
  return "denso_robot_core_interfaces/msg/PoseData";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::msg::PoseData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::msg::PoseData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_robot_core_interfaces::msg::PoseData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__TRAITS_HPP_
