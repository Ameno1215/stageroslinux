// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/MoveJoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_JOINTS__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_JOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/move_joints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_MoveJoints_Request_execute
{
public:
  explicit Init_MoveJoints_Request_execute(::denso_motion_control::srv::MoveJoints_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::MoveJoints_Request execute(::denso_motion_control::srv::MoveJoints_Request::_execute_type arg)
  {
    msg_.execute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::MoveJoints_Request msg_;
};

class Init_MoveJoints_Request_is_relative
{
public:
  explicit Init_MoveJoints_Request_is_relative(::denso_motion_control::srv::MoveJoints_Request & msg)
  : msg_(msg)
  {}
  Init_MoveJoints_Request_execute is_relative(::denso_motion_control::srv::MoveJoints_Request::_is_relative_type arg)
  {
    msg_.is_relative = std::move(arg);
    return Init_MoveJoints_Request_execute(msg_);
  }

private:
  ::denso_motion_control::srv::MoveJoints_Request msg_;
};

class Init_MoveJoints_Request_joints
{
public:
  Init_MoveJoints_Request_joints()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveJoints_Request_is_relative joints(::denso_motion_control::srv::MoveJoints_Request::_joints_type arg)
  {
    msg_.joints = std::move(arg);
    return Init_MoveJoints_Request_is_relative(msg_);
  }

private:
  ::denso_motion_control::srv::MoveJoints_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::MoveJoints_Request>()
{
  return denso_motion_control::srv::builder::Init_MoveJoints_Request_joints();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_MoveJoints_Response_message
{
public:
  explicit Init_MoveJoints_Response_message(::denso_motion_control::srv::MoveJoints_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::MoveJoints_Response message(::denso_motion_control::srv::MoveJoints_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::MoveJoints_Response msg_;
};

class Init_MoveJoints_Response_success
{
public:
  Init_MoveJoints_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveJoints_Response_message success(::denso_motion_control::srv::MoveJoints_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveJoints_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::MoveJoints_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::MoveJoints_Response>()
{
  return denso_motion_control::srv::builder::Init_MoveJoints_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_JOINTS__BUILDER_HPP_
