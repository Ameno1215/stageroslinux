// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_motion_control:srv/MoveWaypoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__TRAITS_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_motion_control/srv/detail/move_waypoints__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'waypoints'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveWaypoints_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: waypoints
  {
    if (msg.waypoints.size() == 0) {
      out << "waypoints: []";
    } else {
      out << "waypoints: [";
      size_t pending_items = msg.waypoints.size();
      for (auto item : msg.waypoints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
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
  const MoveWaypoints_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoints.size() == 0) {
      out << "waypoints: []\n";
    } else {
      out << "waypoints:\n";
      for (auto item : msg.waypoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
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

inline std::string to_yaml(const MoveWaypoints_Request & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::MoveWaypoints_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::MoveWaypoints_Request & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::MoveWaypoints_Request>()
{
  return "denso_motion_control::srv::MoveWaypoints_Request";
}

template<>
inline const char * name<denso_motion_control::srv::MoveWaypoints_Request>()
{
  return "denso_motion_control/srv/MoveWaypoints_Request";
}

template<>
struct has_fixed_size<denso_motion_control::srv::MoveWaypoints_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::MoveWaypoints_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::MoveWaypoints_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const MoveWaypoints_Response & msg,
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
  const MoveWaypoints_Response & msg,
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

inline std::string to_yaml(const MoveWaypoints_Response & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::MoveWaypoints_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::MoveWaypoints_Response & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::MoveWaypoints_Response>()
{
  return "denso_motion_control::srv::MoveWaypoints_Response";
}

template<>
inline const char * name<denso_motion_control::srv::MoveWaypoints_Response>()
{
  return "denso_motion_control/srv/MoveWaypoints_Response";
}

template<>
struct has_fixed_size<denso_motion_control::srv::MoveWaypoints_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::MoveWaypoints_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::MoveWaypoints_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_motion_control::srv::MoveWaypoints>()
{
  return "denso_motion_control::srv::MoveWaypoints";
}

template<>
inline const char * name<denso_motion_control::srv::MoveWaypoints>()
{
  return "denso_motion_control/srv/MoveWaypoints";
}

template<>
struct has_fixed_size<denso_motion_control::srv::MoveWaypoints>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_motion_control::srv::MoveWaypoints_Request>::value &&
    has_fixed_size<denso_motion_control::srv::MoveWaypoints_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_motion_control::srv::MoveWaypoints>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_motion_control::srv::MoveWaypoints_Request>::value &&
    has_bounded_size<denso_motion_control::srv::MoveWaypoints_Response>::value
  >
{
};

template<>
struct is_service<denso_motion_control::srv::MoveWaypoints>
  : std::true_type
{
};

template<>
struct is_service_request<denso_motion_control::srv::MoveWaypoints_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_motion_control::srv::MoveWaypoints_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__TRAITS_HPP_
