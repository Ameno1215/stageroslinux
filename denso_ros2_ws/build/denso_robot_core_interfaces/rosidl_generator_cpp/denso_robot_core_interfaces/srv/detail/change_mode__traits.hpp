// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_robot_core_interfaces:srv/ChangeMode.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__TRAITS_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_robot_core_interfaces/srv/detail/change_mode__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_robot_core_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ChangeMode_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChangeMode_Request & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChangeMode_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::srv::ChangeMode_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::srv::ChangeMode_Request & msg)
{
  return denso_robot_core_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::srv::ChangeMode_Request>()
{
  return "denso_robot_core_interfaces::srv::ChangeMode_Request";
}

template<>
inline const char * name<denso_robot_core_interfaces::srv::ChangeMode_Request>()
{
  return "denso_robot_core_interfaces/srv/ChangeMode_Request";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::srv::ChangeMode_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::srv::ChangeMode_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<denso_robot_core_interfaces::srv::ChangeMode_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_robot_core_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ChangeMode_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: hresult
  {
    out << "hresult: ";
    rosidl_generator_traits::value_to_yaml(msg.hresult, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ChangeMode_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: hresult
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hresult: ";
    rosidl_generator_traits::value_to_yaml(msg.hresult, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ChangeMode_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::srv::ChangeMode_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::srv::ChangeMode_Response & msg)
{
  return denso_robot_core_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::srv::ChangeMode_Response>()
{
  return "denso_robot_core_interfaces::srv::ChangeMode_Response";
}

template<>
inline const char * name<denso_robot_core_interfaces::srv::ChangeMode_Response>()
{
  return "denso_robot_core_interfaces/srv/ChangeMode_Response";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::srv::ChangeMode_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::srv::ChangeMode_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<denso_robot_core_interfaces::srv::ChangeMode_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_robot_core_interfaces::srv::ChangeMode>()
{
  return "denso_robot_core_interfaces::srv::ChangeMode";
}

template<>
inline const char * name<denso_robot_core_interfaces::srv::ChangeMode>()
{
  return "denso_robot_core_interfaces/srv/ChangeMode";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::srv::ChangeMode>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_robot_core_interfaces::srv::ChangeMode_Request>::value &&
    has_fixed_size<denso_robot_core_interfaces::srv::ChangeMode_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_robot_core_interfaces::srv::ChangeMode>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_robot_core_interfaces::srv::ChangeMode_Request>::value &&
    has_bounded_size<denso_robot_core_interfaces::srv::ChangeMode_Response>::value
  >
{
};

template<>
struct is_service<denso_robot_core_interfaces::srv::ChangeMode>
  : std::true_type
{
};

template<>
struct is_service_request<denso_robot_core_interfaces::srv::ChangeMode_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_robot_core_interfaces::srv::ChangeMode_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__TRAITS_HPP_
