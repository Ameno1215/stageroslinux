// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/SetScaling.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__SET_SCALING__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__SET_SCALING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/set_scaling__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_SetScaling_Request_accel_scale
{
public:
  explicit Init_SetScaling_Request_accel_scale(::denso_motion_control::srv::SetScaling_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::SetScaling_Request accel_scale(::denso_motion_control::srv::SetScaling_Request::_accel_scale_type arg)
  {
    msg_.accel_scale = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::SetScaling_Request msg_;
};

class Init_SetScaling_Request_velocity_scale
{
public:
  Init_SetScaling_Request_velocity_scale()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetScaling_Request_accel_scale velocity_scale(::denso_motion_control::srv::SetScaling_Request::_velocity_scale_type arg)
  {
    msg_.velocity_scale = std::move(arg);
    return Init_SetScaling_Request_accel_scale(msg_);
  }

private:
  ::denso_motion_control::srv::SetScaling_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::SetScaling_Request>()
{
  return denso_motion_control::srv::builder::Init_SetScaling_Request_velocity_scale();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_SetScaling_Response_message
{
public:
  explicit Init_SetScaling_Response_message(::denso_motion_control::srv::SetScaling_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::SetScaling_Response message(::denso_motion_control::srv::SetScaling_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::SetScaling_Response msg_;
};

class Init_SetScaling_Response_success
{
public:
  Init_SetScaling_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetScaling_Response_message success(::denso_motion_control::srv::SetScaling_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetScaling_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::SetScaling_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::SetScaling_Response>()
{
  return denso_motion_control::srv::builder::Init_SetScaling_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__SET_SCALING__BUILDER_HPP_
