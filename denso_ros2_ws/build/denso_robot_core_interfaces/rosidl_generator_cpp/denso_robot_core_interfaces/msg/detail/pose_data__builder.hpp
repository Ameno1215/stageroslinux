// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:msg/PoseData.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/msg/detail/pose_data__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace msg
{

namespace builder
{

class Init_PoseData_exjoints
{
public:
  explicit Init_PoseData_exjoints(::denso_robot_core_interfaces::msg::PoseData & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::msg::PoseData exjoints(::denso_robot_core_interfaces::msg::PoseData::_exjoints_type arg)
  {
    msg_.exjoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::PoseData msg_;
};

class Init_PoseData_passflag
{
public:
  explicit Init_PoseData_passflag(::denso_robot_core_interfaces::msg::PoseData & msg)
  : msg_(msg)
  {}
  Init_PoseData_exjoints passflag(::denso_robot_core_interfaces::msg::PoseData::_passflag_type arg)
  {
    msg_.passflag = std::move(arg);
    return Init_PoseData_exjoints(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::PoseData msg_;
};

class Init_PoseData_type
{
public:
  explicit Init_PoseData_type(::denso_robot_core_interfaces::msg::PoseData & msg)
  : msg_(msg)
  {}
  Init_PoseData_passflag type(::denso_robot_core_interfaces::msg::PoseData::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_PoseData_passflag(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::PoseData msg_;
};

class Init_PoseData_value
{
public:
  Init_PoseData_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PoseData_type value(::denso_robot_core_interfaces::msg::PoseData::_value_type arg)
  {
    msg_.value = std::move(arg);
    return Init_PoseData_type(msg_);
  }

private:
  ::denso_robot_core_interfaces::msg::PoseData msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::msg::PoseData>()
{
  return denso_robot_core_interfaces::msg::builder::Init_PoseData_value();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__BUILDER_HPP_
