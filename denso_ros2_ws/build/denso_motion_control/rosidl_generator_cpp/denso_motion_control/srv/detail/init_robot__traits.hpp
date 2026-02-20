// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_motion_control:srv/InitRobot.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__TRAITS_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_motion_control/srv/detail/init_robot__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const InitRobot_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: model
  {
    out << "model: ";
    rosidl_generator_traits::value_to_yaml(msg.model, out);
    out << ", ";
  }

  // member: planning_group
  {
    out << "planning_group: ";
    rosidl_generator_traits::value_to_yaml(msg.planning_group, out);
    out << ", ";
  }

  // member: velocity_scale
  {
    out << "velocity_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_scale, out);
    out << ", ";
  }

  // member: accel_scale
  {
    out << "accel_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_scale, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitRobot_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: model
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model: ";
    rosidl_generator_traits::value_to_yaml(msg.model, out);
    out << "\n";
  }

  // member: planning_group
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "planning_group: ";
    rosidl_generator_traits::value_to_yaml(msg.planning_group, out);
    out << "\n";
  }

  // member: velocity_scale
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity_scale, out);
    out << "\n";
  }

  // member: accel_scale
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accel_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.accel_scale, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitRobot_Request & msg, bool use_flow_style = false)
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

}  // namespace denso_motion_control

namespace rosidl_generator_traits
{

[[deprecated("use denso_motion_control::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_motion_control::srv::InitRobot_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::InitRobot_Request & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::InitRobot_Request>()
{
  return "denso_motion_control::srv::InitRobot_Request";
}

template<>
inline const char * name<denso_motion_control::srv::InitRobot_Request>()
{
  return "denso_motion_control/srv/InitRobot_Request";
}

template<>
struct has_fixed_size<denso_motion_control::srv::InitRobot_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::InitRobot_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::InitRobot_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const InitRobot_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const InitRobot_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const InitRobot_Response & msg, bool use_flow_style = false)
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

}  // namespace denso_motion_control

namespace rosidl_generator_traits
{

[[deprecated("use denso_motion_control::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_motion_control::srv::InitRobot_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::InitRobot_Response & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::InitRobot_Response>()
{
  return "denso_motion_control::srv::InitRobot_Response";
}

template<>
inline const char * name<denso_motion_control::srv::InitRobot_Response>()
{
  return "denso_motion_control/srv/InitRobot_Response";
}

template<>
struct has_fixed_size<denso_motion_control::srv::InitRobot_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::InitRobot_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::InitRobot_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_motion_control::srv::InitRobot>()
{
  return "denso_motion_control::srv::InitRobot";
}

template<>
inline const char * name<denso_motion_control::srv::InitRobot>()
{
  return "denso_motion_control/srv/InitRobot";
}

template<>
struct has_fixed_size<denso_motion_control::srv::InitRobot>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_motion_control::srv::InitRobot_Request>::value &&
    has_fixed_size<denso_motion_control::srv::InitRobot_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_motion_control::srv::InitRobot>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_motion_control::srv::InitRobot_Request>::value &&
    has_bounded_size<denso_motion_control::srv::InitRobot_Response>::value
  >
{
};

template<>
struct is_service<denso_motion_control::srv::InitRobot>
  : std::true_type
{
};

template<>
struct is_service_request<denso_motion_control::srv::InitRobot_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_motion_control::srv::InitRobot_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__TRAITS_HPP_
