// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/GetJointState.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GET_JOINT_STATE__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GET_JOINT_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/get_joint_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GetJointState_Request>()
{
  return ::denso_motion_control::srv::GetJointState_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GetJointState_Response_joints
{
public:
  explicit Init_GetJointState_Response_joints(::denso_motion_control::srv::GetJointState_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GetJointState_Response joints(::denso_motion_control::srv::GetJointState_Response::_joints_type arg)
  {
    msg_.joints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GetJointState_Response msg_;
};

class Init_GetJointState_Response_message
{
public:
  explicit Init_GetJointState_Response_message(::denso_motion_control::srv::GetJointState_Response & msg)
  : msg_(msg)
  {}
  Init_GetJointState_Response_joints message(::denso_motion_control::srv::GetJointState_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_GetJointState_Response_joints(msg_);
  }

private:
  ::denso_motion_control::srv::GetJointState_Response msg_;
};

class Init_GetJointState_Response_success
{
public:
  Init_GetJointState_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetJointState_Response_message success(::denso_motion_control::srv::GetJointState_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetJointState_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::GetJointState_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GetJointState_Response>()
{
  return denso_motion_control::srv::builder::Init_GetJointState_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GET_JOINT_STATE__BUILDER_HPP_
