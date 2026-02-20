// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:msg/Joints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/msg/detail/joints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace msg
{

namespace builder
{

class Init_Joints_value
{
public:
  explicit Init_Joints_value(::denso_robot_core_interfaces::msg::Joints & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::msg::Joints value(::denso_robot_core_interfaces::msg::Joints::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::Joints msg_;
};

class Init_Joints_joint
{
public:
  Init_Joints_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Joints_value joint(::denso_robot_core_interfaces::msg::Joints::_joint_type arg)
  {
    msg_.joint = std::move(arg);
    return Init_Joints_value(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::Joints msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::msg::Joints>()
{
  return denso_robot_core_interfaces::msg::builder::Init_Joints_joint();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__BUILDER_HPP_
