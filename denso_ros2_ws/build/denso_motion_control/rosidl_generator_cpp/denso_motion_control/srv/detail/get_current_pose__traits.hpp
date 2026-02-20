// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_motion_control:srv/GetCurrentPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__TRAITS_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_motion_control/srv/detail/get_current_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCurrentPose_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: frame_id
  {
    out << "frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_id, out);
    out << ", ";
  }

  // member: child_frame_id
  {
    out << "child_frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.child_frame_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetCurrentPose_Request & msg,
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

  // member: child_frame_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "child_frame_id: ";
    rosidl_generator_traits::value_to_yaml(msg.child_frame_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCurrentPose_Request & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::GetCurrentPose_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::GetCurrentPose_Request & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::GetCurrentPose_Request>()
{
  return "denso_motion_control::srv::GetCurrentPose_Request";
}

template<>
inline const char * name<denso_motion_control::srv::GetCurrentPose_Request>()
{
  return "denso_motion_control/srv/GetCurrentPose_Request";
}

template<>
struct has_fixed_size<denso_motion_control::srv::GetCurrentPose_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::GetCurrentPose_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::GetCurrentPose_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace denso_motion_control
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetCurrentPose_Response & msg,
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
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: euler_rpy
  {
    if (msg.euler_rpy.size() == 0) {
      out << "euler_rpy: []";
    } else {
      out << "euler_rpy: [";
      size_t pending_items = msg.euler_rpy.size();
      for (auto item : msg.euler_rpy) {
        rosidl_generator_traits::value_to_yaml(item, out);
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
  const GetCurrentPose_Response & msg,
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

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: euler_rpy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.euler_rpy.size() == 0) {
      out << "euler_rpy: []\n";
    } else {
      out << "euler_rpy:\n";
      for (auto item : msg.euler_rpy) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetCurrentPose_Response & msg, bool use_flow_style = false)
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
  const denso_motion_control::srv::GetCurrentPose_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_motion_control::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_motion_control::srv::to_yaml() instead")]]
inline std::string to_yaml(const denso_motion_control::srv::GetCurrentPose_Response & msg)
{
  return denso_motion_control::srv::to_yaml(msg);
}

template<>
inline const char * data_type<denso_motion_control::srv::GetCurrentPose_Response>()
{
  return "denso_motion_control::srv::GetCurrentPose_Response";
}

template<>
inline const char * name<denso_motion_control::srv::GetCurrentPose_Response>()
{
  return "denso_motion_control/srv/GetCurrentPose_Response";
}

template<>
struct has_fixed_size<denso_motion_control::srv::GetCurrentPose_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_motion_control::srv::GetCurrentPose_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_motion_control::srv::GetCurrentPose_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_motion_control::srv::GetCurrentPose>()
{
  return "denso_motion_control::srv::GetCurrentPose";
}

template<>
inline const char * name<denso_motion_control::srv::GetCurrentPose>()
{
  return "denso_motion_control/srv/GetCurrentPose";
}

template<>
struct has_fixed_size<denso_motion_control::srv::GetCurrentPose>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_motion_control::srv::GetCurrentPose_Request>::value &&
    has_fixed_size<denso_motion_control::srv::GetCurrentPose_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_motion_control::srv::GetCurrentPose>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_motion_control::srv::GetCurrentPose_Request>::value &&
    has_bounded_size<denso_motion_control::srv::GetCurrentPose_Response>::value
  >
{
};

template<>
struct is_service<denso_motion_control::srv::GetCurrentPose>
  : std::true_type
{
};

template<>
struct is_service_request<denso_motion_control::srv::GetCurrentPose_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_motion_control::srv::GetCurrentPose_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__TRAITS_HPP_
