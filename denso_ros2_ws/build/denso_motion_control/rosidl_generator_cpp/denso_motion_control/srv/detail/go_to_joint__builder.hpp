// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/GoToJoint.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_JOINT__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_JOINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/go_to_joint__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GoToJoint_Request_execute
{
public:
  explicit Init_GoToJoint_Request_execute(::denso_motion_control::srv::GoToJoint_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GoToJoint_Request execute(::denso_motion_control::srv::GoToJoint_Request::_execute_type arg)
  {
    msg_.execute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GoToJoint_Request msg_;
};

class Init_GoToJoint_Request_joints
{
public:
  Init_GoToJoint_Request_joints()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToJoint_Request_execute joints(::denso_motion_control::srv::GoToJoint_Request::_joints_type arg)
  {
    msg_.joints = std::move(arg);
    return Init_GoToJoint_Request_execute(msg_);
  }

private:
  ::denso_motion_control::srv::GoToJoint_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GoToJoint_Request>()
{
  return denso_motion_control::srv::builder::Init_GoToJoint_Request_joints();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GoToJoint_Response_message
{
public:
  explicit Init_GoToJoint_Response_message(::denso_motion_control::srv::GoToJoint_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GoToJoint_Response message(::denso_motion_control::srv::GoToJoint_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GoToJoint_Response msg_;
};

class Init_GoToJoint_Response_success
{
public:
  Init_GoToJoint_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToJoint_Response_message success(::denso_motion_control::srv::GoToJoint_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GoToJoint_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::GoToJoint_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GoToJoint_Response>()
{
  return denso_motion_control::srv::builder::Init_GoToJoint_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_JOINT__BUILDER_HPP_
