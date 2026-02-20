// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/MoveToPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/move_to_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_MoveToPose_Request_execute
{
public:
  explicit Init_MoveToPose_Request_execute(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::MoveToPose_Request execute(::denso_motion_control::srv::MoveToPose_Request::_execute_type arg)
  {
    msg_.execute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_cartesian_path
{
public:
  explicit Init_MoveToPose_Request_cartesian_path(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_execute cartesian_path(::denso_motion_control::srv::MoveToPose_Request::_cartesian_path_type arg)
  {
    msg_.cartesian_path = std::move(arg);
    return Init_MoveToPose_Request_execute(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_is_relative
{
public:
  explicit Init_MoveToPose_Request_is_relative(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_cartesian_path is_relative(::denso_motion_control::srv::MoveToPose_Request::_is_relative_type arg)
  {
    msg_.is_relative = std::move(arg);
    return Init_MoveToPose_Request_cartesian_path(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_reference_frame
{
public:
  explicit Init_MoveToPose_Request_reference_frame(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_is_relative reference_frame(::denso_motion_control::srv::MoveToPose_Request::_reference_frame_type arg)
  {
    msg_.reference_frame = std::move(arg);
    return Init_MoveToPose_Request_is_relative(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_rotation_format
{
public:
  explicit Init_MoveToPose_Request_rotation_format(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_reference_frame rotation_format(::denso_motion_control::srv::MoveToPose_Request::_rotation_format_type arg)
  {
    msg_.rotation_format = std::move(arg);
    return Init_MoveToPose_Request_reference_frame(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_r4
{
public:
  explicit Init_MoveToPose_Request_r4(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_rotation_format r4(::denso_motion_control::srv::MoveToPose_Request::_r4_type arg)
  {
    msg_.r4 = std::move(arg);
    return Init_MoveToPose_Request_rotation_format(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_r3
{
public:
  explicit Init_MoveToPose_Request_r3(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_r4 r3(::denso_motion_control::srv::MoveToPose_Request::_r3_type arg)
  {
    msg_.r3 = std::move(arg);
    return Init_MoveToPose_Request_r4(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_r2
{
public:
  explicit Init_MoveToPose_Request_r2(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_r3 r2(::denso_motion_control::srv::MoveToPose_Request::_r2_type arg)
  {
    msg_.r2 = std::move(arg);
    return Init_MoveToPose_Request_r3(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_r1
{
public:
  explicit Init_MoveToPose_Request_r1(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_r2 r1(::denso_motion_control::srv::MoveToPose_Request::_r1_type arg)
  {
    msg_.r1 = std::move(arg);
    return Init_MoveToPose_Request_r2(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_z
{
public:
  explicit Init_MoveToPose_Request_z(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_r1 z(::denso_motion_control::srv::MoveToPose_Request::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_MoveToPose_Request_r1(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_y
{
public:
  explicit Init_MoveToPose_Request_y(::denso_motion_control::srv::MoveToPose_Request & msg)
  : msg_(msg)
  {}
  Init_MoveToPose_Request_z y(::denso_motion_control::srv::MoveToPose_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_MoveToPose_Request_z(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

class Init_MoveToPose_Request_x
{
public:
  Init_MoveToPose_Request_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveToPose_Request_y x(::denso_motion_control::srv::MoveToPose_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_MoveToPose_Request_y(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::MoveToPose_Request>()
{
  return denso_motion_control::srv::builder::Init_MoveToPose_Request_x();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_MoveToPose_Response_message
{
public:
  explicit Init_MoveToPose_Response_message(::denso_motion_control::srv::MoveToPose_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::MoveToPose_Response message(::denso_motion_control::srv::MoveToPose_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Response msg_;
};

class Init_MoveToPose_Response_success
{
public:
  Init_MoveToPose_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveToPose_Response_message success(::denso_motion_control::srv::MoveToPose_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveToPose_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::MoveToPose_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::MoveToPose_Response>()
{
  return denso_motion_control::srv::builder::Init_MoveToPose_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__BUILDER_HPP_
