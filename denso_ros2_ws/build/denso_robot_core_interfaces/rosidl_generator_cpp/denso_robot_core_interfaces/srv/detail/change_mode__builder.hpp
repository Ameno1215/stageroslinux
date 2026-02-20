// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:srv/ChangeMode.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/srv/detail/change_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace srv
{

namespace builder
{

class Init_ChangeMode_Request_mode
{
public:
  Init_ChangeMode_Request_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::srv::ChangeMode_Request mode(::denso_robot_core_interfaces::srv::ChangeMode_Request::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::srv::ChangeMode_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::srv::ChangeMode_Request>()
{
  return denso_robot_core_interfaces::srv::builder::Init_ChangeMode_Request_mode();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace srv
{

namespace builder
{

class Init_ChangeMode_Response_hresult
{
public:
  Init_ChangeMode_Response_hresult()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::srv::ChangeMode_Response hresult(::denso_robot_core_interfaces::srv::ChangeMode_Response::_hresult_type arg)
  {
    msg_.hresult = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::srv::ChangeMode_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::srv::ChangeMode_Response>()
{
  return denso_robot_core_interfaces::srv::builder::Init_ChangeMode_Response_hresult();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__SRV__DETAIL__CHANGE_MODE__BUILDER_HPP_
