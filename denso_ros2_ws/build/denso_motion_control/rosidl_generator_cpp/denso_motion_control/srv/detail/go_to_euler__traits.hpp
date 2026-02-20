// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_motion_control:srv/GoToEuler.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__TRAITS_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_motion_control/srv/detail/go_to_euler__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const GoToEuler_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: rx
  {
    out << "rx: ";
    rosidl_generator_traits::value_to_yaml(msg.rx, out);
    out << ", ";
  }

  // member: ry
  {
    out << "ry: ";
    rosidl_generator_traits::value_to_yaml(msg.ry, out);
    out << ", ";
  }

  // member: rz
  {
    out << "rz: ";
    rosidl_generator_traits::value_to_yaml(msg.rz, out);
    out << ", ";
  }

  // member: execute
  {
    out << "execute: ";
    rosidl_generator_traits::value_to_yaml(msg.execute, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToEuler_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: rx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rx: ";
    rosidl_generator_traits::value_to_yaml(msg.rx, out);
    out << "\n";
  }

  // member: ry
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ry: ";
    rosidl_generator_traits::value_to_yaml(msg.ry, out);
    out << "\n";
  }

  // member: rz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rz: ";
    rosidl_generator_traits::value_to_yaml(msg.rz, out);
    out << "\n";
  }

  // member: execute
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "execute: ";
    rosidl_generator_traits::value_to_yaml(msg.execute, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToEuler_Request & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::GoToEuler_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::GoToEuler_Request & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::GoToEuler_Request>()
{
  return "denso_motion_control::srv::GoToEuler_Request";
}

template<>
inline const char * name<denso_motion_control::srv::GoToEuler_Request>()
{
  return "denso_motion_control/srv/GoToEuler_Request";
}

template<>
struct has_fixed_size<denso_motion_control::srv::GoToEuler_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::GoToEuler_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::GoToEuler_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const GoToEuler_Response & msg,
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
  const GoToEuler_Response & msg,
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

inline std::string to_yaml(const GoToEuler_Response & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::GoToEuler_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::GoToEuler_Response & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::GoToEuler_Response>()
{
  return "denso_motion_control::srv::GoToEuler_Response";
}

template<>
inline const char * name<denso_motion_control::srv::GoToEuler_Response>()
{
  return "denso_motion_control/srv/GoToEuler_Response";
}

template<>
struct has_fixed_size<denso_motion_control::srv::GoToEuler_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::GoToEuler_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::GoToEuler_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_motion_control::srv::GoToEuler>()
{
  return "denso_motion_control::srv::GoToEuler";
}

template<>
inline const char * name<denso_motion_control::srv::GoToEuler>()
{
  return "denso_motion_control/srv/GoToEuler";
}

template<>
struct has_fixed_size<denso_motion_control::srv::GoToEuler>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_motion_control::srv::GoToEuler_Request>::value &&
    has_fixed_size<denso_motion_control::srv::GoToEuler_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_motion_control::srv::GoToEuler>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_motion_control::srv::GoToEuler_Request>::value &&
    has_bounded_size<denso_motion_control::srv::GoToEuler_Response>::value
  >
{
};

template<>
struct is_service<denso_motion_control::srv::GoToEuler>
  : std::true_type
{
};

template<>
struct is_service_request<denso_motion_control::srv::GoToEuler_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_motion_control::srv::GoToEuler_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__TRAITS_HPP_
