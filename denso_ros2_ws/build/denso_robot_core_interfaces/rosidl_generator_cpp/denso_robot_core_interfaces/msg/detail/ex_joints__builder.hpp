// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:msg/ExJoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/msg/detail/ex_joints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace msg
{

namespace builder
{

class Init_ExJoints_joints
{
public:
  explicit Init_ExJoints_joints(::denso_robot_core_interfaces::msg::ExJoints & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::msg::ExJoints joints(::denso_robot_core_interfaces::msg::ExJoints::_joints_type arg)
  {
    msg_.joints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::ExJoints msg_;
};

class Init_ExJoints_mode
{
public:
  Init_ExJoints_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ExJoints_joints mode(::denso_robot_core_interfaces::msg::ExJoints::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_ExJoints_joints(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::ExJoints msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::msg::ExJoints>()
{
  return denso_robot_core_interfaces::msg::builder::Init_ExJoints_mode();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__BUILDER_HPP_
