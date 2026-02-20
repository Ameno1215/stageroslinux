// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_motion_control:srv/MoveToPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__TRAITS_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_motion_control/srv/detail/move_to_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveToPose_Request & msg,
  std::ostream & out)
{
  out << "{";
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

  // member: r1
  {
    out << "r1: ";
    rosidl_generator_traits::value_to_yaml(msg.r1, out);
    out << ", ";
  }

  // member: r2
  {
    out << "r2: ";
    rosidl_generator_traits::value_to_yaml(msg.r2, out);
    out << ", ";
  }

  // member: r3
  {
    out << "r3: ";
    rosidl_generator_traits::value_to_yaml(msg.r3, out);
    out << ", ";
  }

  // member: r4
  {
    out << "r4: ";
    rosidl_generator_traits::value_to_yaml(msg.r4, out);
    out << ", ";
  }

  // member: rotation_format
  {
    out << "rotation_format: ";
    rosidl_generator_traits::value_to_yaml(msg.rotation_format, out);
    out << ", ";
  }

  // member: reference_frame
  {
    out << "reference_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_frame, out);
    out << ", ";
  }

  // member: is_relative
  {
    out << "is_relative: ";
    rosidl_generator_traits::value_to_yaml(msg.is_relative, out);
    out << ", ";
  }

  // member: cartesian_path
  {
    out << "cartesian_path: ";
    rosidl_generator_traits::value_to_yaml(msg.cartesian_path, out);
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
  const MoveToPose_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
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

  // member: r1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r1: ";
    rosidl_generator_traits::value_to_yaml(msg.r1, out);
    out << "\n";
  }

  // member: r2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r2: ";
    rosidl_generator_traits::value_to_yaml(msg.r2, out);
    out << "\n";
  }

  // member: r3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r3: ";
    rosidl_generator_traits::value_to_yaml(msg.r3, out);
    out << "\n";
  }

  // member: r4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r4: ";
    rosidl_generator_traits::value_to_yaml(msg.r4, out);
    out << "\n";
  }

  // member: rotation_format
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rotation_format: ";
    rosidl_generator_traits::value_to_yaml(msg.rotation_format, out);
    out << "\n";
  }

  // member: reference_frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reference_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_frame, out);
    out << "\n";
  }

  // member: is_relative
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_relative: ";
    rosidl_generator_traits::value_to_yaml(msg.is_relative, out);
    out << "\n";
  }

  // member: cartesian_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cartesian_path: ";
    rosidl_generator_traits::value_to_yaml(msg.cartesian_path, out);
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

inline std::string to_yaml(const MoveToPose_Request & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::MoveToPose_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::MoveToPose_Request & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::MoveToPose_Request>()
{
  return "denso_motion_control::srv::MoveToPose_Request";
}

template<>
inline const char * name<denso_motion_control::srv::MoveToPose_Request>()
{
  return "denso_motion_control/srv/MoveToPose_Request";
}

template<>
struct has_fixed_size<denso_motion_control::srv::MoveToPose_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::MoveToPose_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::MoveToPose_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveToPose_Response & msg,
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
  const MoveToPose_Response & msg,
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

inline std::string to_yaml(const MoveToPose_Response & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::MoveToPose_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::MoveToPose_Response & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::MoveToPose_Response>()
{
  return "denso_motion_control::srv::MoveToPose_Response";
}

template<>
inline const char * name<denso_motion_control::srv::MoveToPose_Response>()
{
  return "denso_motion_control/srv/MoveToPose_Response";
}

template<>
struct has_fixed_size<denso_motion_control::srv::MoveToPose_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::MoveToPose_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::MoveToPose_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_motion_control::srv::MoveToPose>()
{
  return "denso_motion_control::srv::MoveToPose";
}

template<>
inline const char * name<denso_motion_control::srv::MoveToPose>()
{
  return "denso_motion_control/srv/MoveToPose";
}

template<>
struct has_fixed_size<denso_motion_control::srv::MoveToPose>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_motion_control::srv::MoveToPose_Request>::value &&
    has_fixed_size<denso_motion_control::srv::MoveToPose_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_motion_control::srv::MoveToPose>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_motion_control::srv::MoveToPose_Request>::value &&
    has_bounded_size<denso_motion_control::srv::MoveToPose_Response>::value
  >
{
};

template<>
struct is_service<denso_motion_control::srv::MoveToPose>
  : std::true_type
{
};

template<>
struct is_service_request<denso_motion_control::srv::MoveToPose_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_motion_control::srv::MoveToPose_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__TRAITS_HPP_
