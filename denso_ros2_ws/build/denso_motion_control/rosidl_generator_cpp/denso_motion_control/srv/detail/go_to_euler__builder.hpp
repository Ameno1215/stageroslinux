// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/GoToEuler.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/go_to_euler__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GoToEuler_Request_execute
{
public:
  explicit Init_GoToEuler_Request_execute(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GoToEuler_Request execute(::denso_motion_control::srv::GoToEuler_Request::_execute_type arg)
  {
    msg_.execute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_rz
{
public:
  explicit Init_GoToEuler_Request_rz(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  Init_GoToEuler_Request_execute rz(::denso_motion_control::srv::GoToEuler_Request::_rz_type arg)
  {
    msg_.rz = std::move(arg);
    return Init_GoToEuler_Request_execute(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_ry
{
public:
  explicit Init_GoToEuler_Request_ry(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  Init_GoToEuler_Request_rz ry(::denso_motion_control::srv::GoToEuler_Request::_ry_type arg)
  {
    msg_.ry = std::move(arg);
    return Init_GoToEuler_Request_rz(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_rx
{
public:
  explicit Init_GoToEuler_Request_rx(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  Init_GoToEuler_Request_ry rx(::denso_motion_control::srv::GoToEuler_Request::_rx_type arg)
  {
    msg_.rx = std::move(arg);
    return Init_GoToEuler_Request_ry(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_z
{
public:
  explicit Init_GoToEuler_Request_z(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  Init_GoToEuler_Request_rx z(::denso_motion_control::srv::GoToEuler_Request::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_GoToEuler_Request_rx(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_y
{
public:
  explicit Init_GoToEuler_Request_y(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  Init_GoToEuler_Request_z y(::denso_motion_control::srv::GoToEuler_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_GoToEuler_Request_z(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_x
{
public:
  explicit Init_GoToEuler_Request_x(::denso_motion_control::srv::GoToEuler_Request & msg)
  : msg_(msg)
  {}
  Init_GoToEuler_Request_y x(::denso_motion_control::srv::GoToEuler_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_GoToEuler_Request_y(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

class Init_GoToEuler_Request_frame_id
{
public:
  Init_GoToEuler_Request_frame_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToEuler_Request_x frame_id(::denso_motion_control::srv::GoToEuler_Request::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_GoToEuler_Request_x(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GoToEuler_Request>()
{
  return denso_motion_control::srv::builder::Init_GoToEuler_Request_frame_id();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_GoToEuler_Response_message
{
public:
  explicit Init_GoToEuler_Response_message(::denso_motion_control::srv::GoToEuler_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::GoToEuler_Response message(::denso_motion_control::srv::GoToEuler_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Response msg_;
};

class Init_GoToEuler_Response_success
{
public:
  Init_GoToEuler_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToEuler_Response_message success(::denso_motion_control::srv::GoToEuler_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GoToEuler_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::GoToEuler_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::GoToEuler_Response>()
{
  return denso_motion_control::srv::builder::Init_GoToEuler_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__BUILDER_HPP_
