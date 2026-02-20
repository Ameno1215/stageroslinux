// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/InitRobot.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/init_robot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_InitRobot_Request_accel_scale
{
public:
  explicit Init_InitRobot_Request_accel_scale(::denso_motion_control::srv::InitRobot_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::InitRobot_Request accel_scale(::denso_motion_control::srv::InitRobot_Request::_accel_scale_type arg)
  {
    msg_.accel_scale = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::InitRobot_Request msg_;
};

class Init_InitRobot_Request_velocity_scale
{
public:
  explicit Init_InitRobot_Request_velocity_scale(::denso_motion_control::srv::InitRobot_Request & msg)
  : msg_(msg)
  {}
  Init_InitRobot_Request_accel_scale velocity_scale(::denso_motion_control::srv::InitRobot_Request::_velocity_scale_type arg)
  {
    msg_.velocity_scale = std::move(arg);
    return Init_InitRobot_Request_accel_scale(msg_);
  }

private:
  ::denso_motion_control::srv::InitRobot_Request msg_;
};

class Init_InitRobot_Request_planning_group
{
public:
  explicit Init_InitRobot_Request_planning_group(::denso_motion_control::srv::InitRobot_Request & msg)
  : msg_(msg)
  {}
  Init_InitRobot_Request_velocity_scale planning_group(::denso_motion_control::srv::InitRobot_Request::_planning_group_type arg)
  {
    msg_.planning_group = std::move(arg);
    return Init_InitRobot_Request_velocity_scale(msg_);
  }

private:
  ::denso_motion_control::srv::InitRobot_Request msg_;
};

class Init_InitRobot_Request_model
{
public:
  Init_InitRobot_Request_model()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitRobot_Request_planning_group model(::denso_motion_control::srv::InitRobot_Request::_model_type arg)
  {
    msg_.model = std::move(arg);
    return Init_InitRobot_Request_planning_group(msg_);
  }

private:
  ::denso_motion_control::srv::InitRobot_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::InitRobot_Request>()
{
  return denso_motion_control::srv::builder::Init_InitRobot_Request_model();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_InitRobot_Response_message
{
public:
  explicit Init_InitRobot_Response_message(::denso_motion_control::srv::InitRobot_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::InitRobot_Response message(::denso_motion_control::srv::InitRobot_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::InitRobot_Response msg_;
};

class Init_InitRobot_Response_success
{
public:
  Init_InitRobot_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_InitRobot_Response_message success(::denso_motion_control::srv::InitRobot_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_InitRobot_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::InitRobot_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::InitRobot_Response>()
{
  return denso_motion_control::srv::builder::Init_InitRobot_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__INIT_ROBOT__BUILDER_HPP_
