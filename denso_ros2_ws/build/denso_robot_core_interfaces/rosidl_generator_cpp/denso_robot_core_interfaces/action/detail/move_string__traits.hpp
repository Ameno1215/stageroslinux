// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from denso_robot_core_interfaces:action/MoveString.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_STRING__TRAITS_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_STRING__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "denso_robot_core_interfaces/action/detail/move_string__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: comp
  {
    out << "comp: ";
    rosidl_generator_traits::value_to_yaml(msg.comp, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    rosidl_generator_traits::value_to_yaml(msg.pose, out);
    out << ", ";
  }

  // member: option
  {
    out << "option: ";
    rosidl_generator_traits::value_to_yaml(msg.option, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveString_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: comp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "comp: ";
    rosidl_generator_traits::value_to_yaml(msg.comp, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose: ";
    rosidl_generator_traits::value_to_yaml(msg.pose, out);
    out << "\n";
  }

  // member: option
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "option: ";
    rosidl_generator_traits::value_to_yaml(msg.option, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveString_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_Goal & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_Goal>()
{
  return "denso_robot_core_interfaces::action::MoveString_Goal";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_Goal>()
{
  return "denso_robot_core_interfaces/action/MoveString_Goal";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_Result & msg,
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
  const MoveString_Result & msg,
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

inline std::string to_yaml(const MoveString_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_Result & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_Result>()
{
  return "denso_robot_core_interfaces::action::MoveString_Result";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_Result>()
{
  return "denso_robot_core_interfaces/action/MoveString_Result";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_Result>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_Result>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: pose
  {
    if (msg.pose.size() == 0) {
      out << "pose: []";
    } else {
      out << "pose: [";
      size_t pending_items = msg.pose.size();
      for (auto item : msg.pose) {
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
  const MoveString_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pose.size() == 0) {
      out << "pose: []\n";
    } else {
      out << "pose:\n";
      for (auto item : msg.pose) {
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

inline std::string to_yaml(const MoveString_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_Feedback & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_Feedback>()
{
  return "denso_robot_core_interfaces::action::MoveString_Feedback";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_Feedback>()
{
  return "denso_robot_core_interfaces/action/MoveString_Feedback";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "denso_robot_core_interfaces/action/detail/move_string__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveString_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveString_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_SendGoal_Request & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>()
{
  return "denso_robot_core_interfaces::action::MoveString_SendGoal_Request";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>()
{
  return "denso_robot_core_interfaces/action/MoveString_SendGoal_Request";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<denso_robot_core_interfaces::action::MoveString_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<denso_robot_core_interfaces::action::MoveString_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveString_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveString_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_SendGoal_Response & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>()
{
  return "denso_robot_core_interfaces::action::MoveString_SendGoal_Response";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>()
{
  return "denso_robot_core_interfaces/action/MoveString_SendGoal_Response";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_SendGoal>()
{
  return "denso_robot_core_interfaces::action::MoveString_SendGoal";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_SendGoal>()
{
  return "denso_robot_core_interfaces/action/MoveString_SendGoal";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>::value &&
    has_fixed_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>::value &&
    has_bounded_size<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<denso_robot_core_interfaces::action::MoveString_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<denso_robot_core_interfaces::action::MoveString_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_robot_core_interfaces::action::MoveString_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveString_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveString_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_GetResult_Request & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_GetResult_Request>()
{
  return "denso_robot_core_interfaces::action::MoveString_GetResult_Request";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_GetResult_Request>()
{
  return "denso_robot_core_interfaces/action/MoveString_GetResult_Request";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "denso_robot_core_interfaces/action/detail/move_string__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveString_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveString_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_GetResult_Response & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_GetResult_Response>()
{
  return "denso_robot_core_interfaces::action::MoveString_GetResult_Response";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_GetResult_Response>()
{
  return "denso_robot_core_interfaces/action/MoveString_GetResult_Response";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<denso_robot_core_interfaces::action::MoveString_Result>::value> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<denso_robot_core_interfaces::action::MoveString_Result>::value> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_GetResult>()
{
  return "denso_robot_core_interfaces::action::MoveString_GetResult";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_GetResult>()
{
  return "denso_robot_core_interfaces/action/MoveString_GetResult";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<denso_robot_core_interfaces::action::MoveString_GetResult_Request>::value &&
    has_fixed_size<denso_robot_core_interfaces::action::MoveString_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<denso_robot_core_interfaces::action::MoveString_GetResult_Request>::value &&
    has_bounded_size<denso_robot_core_interfaces::action::MoveString_GetResult_Response>::value
  >
{
};

template<>
struct is_service<denso_robot_core_interfaces::action::MoveString_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<denso_robot_core_interfaces::action::MoveString_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<denso_robot_core_interfaces::action::MoveString_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "denso_robot_core_interfaces/action/detail/move_string__traits.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveString_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveString_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveString_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use denso_robot_core_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const denso_robot_core_interfaces::action::MoveString_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  denso_robot_core_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use denso_robot_core_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const denso_robot_core_interfaces::action::MoveString_FeedbackMessage & msg)
{
  return denso_robot_core_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<denso_robot_core_interfaces::action::MoveString_FeedbackMessage>()
{
  return "denso_robot_core_interfaces::action::MoveString_FeedbackMessage";
}

template<>
inline const char * name<denso_robot_core_interfaces::action::MoveString_FeedbackMessage>()
{
  return "denso_robot_core_interfaces/action/MoveString_FeedbackMessage";
}

template<>
struct has_fixed_size<denso_robot_core_interfaces::action::MoveString_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<denso_robot_core_interfaces::action::MoveString_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<denso_robot_core_interfaces::action::MoveString_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<denso_robot_core_interfaces::action::MoveString_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<denso_robot_core_interfaces::action::MoveString_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<denso_robot_core_interfaces::action::MoveString>
  : std::true_type
{
};

template<>
struct is_action_goal<denso_robot_core_interfaces::action::MoveString_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<denso_robot_core_interfaces::action::MoveString_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<denso_robot_core_interfaces::action::MoveString_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_STRING__TRAITS_HPP_
