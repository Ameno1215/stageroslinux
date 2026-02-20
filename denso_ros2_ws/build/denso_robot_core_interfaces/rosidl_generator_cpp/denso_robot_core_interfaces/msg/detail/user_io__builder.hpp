// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:msg/UserIO.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/msg/detail/user_io__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace msg
{

namespace builder
{

class Init_UserIO_value
{
public:
  explicit Init_UserIO_value(::denso_robot_core_interfaces::msg::UserIO & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::msg::UserIO value(::denso_robot_core_interfaces::msg::UserIO::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::UserIO msg_;
};

class Init_UserIO_size
{
public:
  explicit Init_UserIO_size(::denso_robot_core_interfaces::msg::UserIO & msg)
  : msg_(msg)
  {}
  Init_UserIO_value size(::denso_robot_core_interfaces::msg::UserIO::_size_type arg)
  {
    msg_.size = std::move(arg);
    return Init_UserIO_value(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::UserIO msg_;
};

class Init_UserIO_offset
{
public:
  Init_UserIO_offset()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_UserIO_size offset(::denso_robot_core_interfaces::msg::UserIO::_offset_type arg)
  {
    msg_.offset = std::move(arg);
    return Init_UserIO_size(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::UserIO msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::msg::UserIO>()
{
  return denso_robot_core_interfaces::msg::builder::Init_UserIO_offset();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__BUILDER_HPP_
