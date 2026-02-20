// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__TRAITS_HPP_
#define BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "bcap_service_interfaces/srv/detail/bcap__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'vnt_args'
#include "bcap_service_interfaces/msg/detail/variant__traits.hpp"

namespace bcap_service_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const Bcap_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: func_id
  {
    out << "func_id: ";
    rosidl_generator_traits::value_to_yaml(msg.func_id, out);
    out << ", ";
  }

  // member: vnt_args
  {
    if (msg.vnt_args.size() == 0) {
      out << "vnt_args: []";
    } else {
      out << "vnt_args: [";
      size_t pending_items = msg.vnt_args.size();
      for (auto item : msg.vnt_args) {
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
  const Bcap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: func_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "func_id: ";
    rosidl_generator_traits::value_to_yaml(msg.func_id, out);
    out << "\n";
  }

  // member: vnt_args
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.vnt_args.size() == 0) {
      out << "vnt_args: []\n";
    } else {
      out << "vnt_args:\n";
      for (auto item : msg.vnt_args) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Bcap_Request & msg, bool use_flow_style = false)
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

}  // namespace bcap_service_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use bcap_service_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bcap_service_interfaces::srv::Bcap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  bcap_service_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bcap_service_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const bcap_service_interfaces::srv::Bcap_Request & msg)
{
  return bcap_service_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<bcap_service_interfaces::srv::Bcap_Request>()
{
  return "bcap_service_interfaces::srv::Bcap_Request";
}

template<>
inline const char * name<bcap_service_interfaces::srv::Bcap_Request>()
{
  return "bcap_service_interfaces/srv/Bcap_Request";
}

template<>
struct has_fixed_size<bcap_service_interfaces::srv::Bcap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<bcap_service_interfaces::srv::Bcap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<bcap_service_interfaces::srv::Bcap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'vnt_ret'
// already included above
// #include "bcap_service_interfaces/msg/detail/variant__traits.hpp"

namespace bcap_service_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const Bcap_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: hresult
  {
    out << "hresult: ";
    rosidl_generator_traits::value_to_yaml(msg.hresult, out);
    out << ", ";
  }

  // member: vnt_ret
  {
    out << "vnt_ret: ";
    to_flow_style_yaml(msg.vnt_ret, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Bcap_Response & msg,
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

  // member: vnt_ret
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "vnt_ret:\n";
    to_block_style_yaml(msg.vnt_ret, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Bcap_Response & msg, bool use_flow_style = false)
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

}  // namespace bcap_service_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use bcap_service_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bcap_service_interfaces::srv::Bcap_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  bcap_service_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bcap_service_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const bcap_service_interfaces::srv::Bcap_Response & msg)
{
  return bcap_service_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<bcap_service_interfaces::srv::Bcap_Response>()
{
  return "bcap_service_interfaces::srv::Bcap_Response";
}

template<>
inline const char * name<bcap_service_interfaces::srv::Bcap_Response>()
{
  return "bcap_service_interfaces/srv/Bcap_Response";
}

template<>
struct has_fixed_size<bcap_service_interfaces::srv::Bcap_Response>
  : std::integral_constant<bool, has_fixed_size<bcap_service_interfaces::msg::Variant>::value> {};

template<>
struct has_bounded_size<bcap_service_interfaces::srv::Bcap_Response>
  : std::integral_constant<bool, has_bounded_size<bcap_service_interfaces::msg::Variant>::value> {};

template<>
struct is_message<bcap_service_interfaces::srv::Bcap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<bcap_service_interfaces::srv::Bcap>()
{
  return "bcap_service_interfaces::srv::Bcap";
}

template<>
inline const char * name<bcap_service_interfaces::srv::Bcap>()
{
  return "bcap_service_interfaces/srv/Bcap";
}

template<>
struct has_fixed_size<bcap_service_interfaces::srv::Bcap>
  : std::integral_constant<
    bool,
    has_fixed_size<bcap_service_interfaces::srv::Bcap_Request>::value &&
    has_fixed_size<bcap_service_interfaces::srv::Bcap_Response>::value
  >
{
};

template<>
struct has_bounded_size<bcap_service_interfaces::srv::Bcap>
  : std::integral_constant<
    bool,
    has_bounded_size<bcap_service_interfaces::srv::Bcap_Request>::value &&
    has_bounded_size<bcap_service_interfaces::srv::Bcap_Response>::value
  >
{
};

template<>
struct is_service<bcap_service_interfaces::srv::Bcap>
  : std::true_type
{
};

template<>
struct is_service_request<bcap_service_interfaces::srv::Bcap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<bcap_service_interfaces::srv::Bcap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__TRAITS_HPP_
