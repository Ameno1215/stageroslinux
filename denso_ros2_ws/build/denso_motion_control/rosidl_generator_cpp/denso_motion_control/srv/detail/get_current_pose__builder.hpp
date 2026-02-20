// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/GetCurrentPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/get_current_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GetCurrentPose_Request_child_frame_id
{
public:
  explicit Init_GetCurrentPose_Request_child_frame_id(::denso_motion_control::srv::GetCurrentPose_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GetCurrentPose_Request child_frame_id(::denso_motion_control::srv::GetCurrentPose_Request::_child_frame_id_type arg)
  {
    msg_.child_frame_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GetCurrentPose_Request msg_;
};

class Init_GetCurrentPose_Request_frame_id
{
public:
  Init_GetCurrentPose_Request_frame_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetCurrentPose_Request_child_frame_id frame_id(::denso_motion_control::srv::GetCurrentPose_Request::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_GetCurrentPose_Request_child_frame_id(msg_);
  }

private:
  ::denso_motion_control::srv::GetCurrentPose_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GetCurrentPose_Request>()
{
  return denso_motion_control::srv::builder::Init_GetCurrentPose_Request_frame_id();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GetCurrentPose_Response_euler_rpy
{
public:
  explicit Init_GetCurrentPose_Response_euler_rpy(::denso_motion_control::srv::GetCurrentPose_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GetCurrentPose_Response euler_rpy(::denso_motion_control::srv::GetCurrentPose_Response::_euler_rpy_type arg)
  {
    msg_.euler_rpy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GetCurrentPose_Response msg_;
};

class Init_GetCurrentPose_Response_pose
{
public:
  explicit Init_GetCurrentPose_Response_pose(::denso_motion_control::srv::GetCurrentPose_Response & msg)
  : msg_(msg)
  {}
  Init_GetCurrentPose_Response_euler_rpy pose(::denso_motion_control::srv::GetCurrentPose_Response::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_GetCurrentPose_Response_euler_rpy(msg_);
  }

private:
  ::denso_motion_control::srv::GetCurrentPose_Response msg_;
};

class Init_GetCurrentPose_Response_message
{
public:
  explicit Init_GetCurrentPose_Response_message(::denso_motion_control::srv::GetCurrentPose_Response & msg)
  : msg_(msg)
  {}
  Init_GetCurrentPose_Response_pose message(::denso_motion_control::srv::GetCurrentPose_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_GetCurrentPose_Response_pose(msg_);
  }

private:
  ::denso_motion_control::srv::GetCurrentPose_Response msg_;
};

class Init_GetCurrentPose_Response_success
{
public:
  Init_GetCurrentPose_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetCurrentPose_Response_message success(::denso_motion_control::srv::GetCurrentPose_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetCurrentPose_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::GetCurrentPose_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GetCurrentPose_Response>()
{
  return denso_motion_control::srv::builder::Init_GetCurrentPose_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__BUILDER_HPP_
