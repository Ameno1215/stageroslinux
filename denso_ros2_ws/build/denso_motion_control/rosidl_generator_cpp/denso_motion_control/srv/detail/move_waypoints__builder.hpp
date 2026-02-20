// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_motion_control:srv/MoveWaypoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__BUILDER_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_motion_control/srv/detail/move_waypoints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_MoveWaypoints_Request_execute
{
public:
  explicit Init_MoveWaypoints_Request_execute(::denso_motion_control::srv::MoveWaypoints_Request & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::MoveWaypoints_Request execute(::denso_motion_control::srv::MoveWaypoints_Request::_execute_type arg)
  {
    msg_.execute = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Request msg_;
};

class Init_MoveWaypoints_Request_cartesian_path
{
public:
  explicit Init_MoveWaypoints_Request_cartesian_path(::denso_motion_control::srv::MoveWaypoints_Request & msg)
  : msg_(msg)
  {}
  Init_MoveWaypoints_Request_execute cartesian_path(::denso_motion_control::srv::MoveWaypoints_Request::_cartesian_path_type arg)
  {
    msg_.cartesian_path = std::move(arg);
    return Init_MoveWaypoints_Request_execute(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Request msg_;
};

class Init_MoveWaypoints_Request_is_relative
{
public:
  explicit Init_MoveWaypoints_Request_is_relative(::denso_motion_control::srv::MoveWaypoints_Request & msg)
  : msg_(msg)
  {}
  Init_MoveWaypoints_Request_cartesian_path is_relative(::denso_motion_control::srv::MoveWaypoints_Request::_is_relative_type arg)
  {
    msg_.is_relative = std::move(arg);
    return Init_MoveWaypoints_Request_cartesian_path(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Request msg_;
};

class Init_MoveWaypoints_Request_reference_frame
{
public:
  explicit Init_MoveWaypoints_Request_reference_frame(::denso_motion_control::srv::MoveWaypoints_Request & msg)
  : msg_(msg)
  {}
  Init_MoveWaypoints_Request_is_relative reference_frame(::denso_motion_control::srv::MoveWaypoints_Request::_reference_frame_type arg)
  {
    msg_.reference_frame = std::move(arg);
    return Init_MoveWaypoints_Request_is_relative(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Request msg_;
};

class Init_MoveWaypoints_Request_waypoints
{
public:
  Init_MoveWaypoints_Request_waypoints()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveWaypoints_Request_reference_frame waypoints(::denso_motion_control::srv::MoveWaypoints_Request::_waypoints_type arg)
  {
    msg_.waypoints = std::move(arg);
    return Init_MoveWaypoints_Request_reference_frame(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::MoveWaypoints_Request>()
{
  return denso_motion_control::srv::builder::Init_MoveWaypoints_Request_waypoints();
}

}  // namespace denso_motion_control


namespace denso_motion_control
{

namespace srv
{

namespace builder
{

class Init_MoveWaypoints_Response_message
{
public:
  explicit Init_MoveWaypoints_Response_message(::denso_motion_control::srv::MoveWaypoints_Response & msg)
  : msg_(msg)
  {}
  ::denso_motion_control::srv::MoveWaypoints_Response message(::denso_motion_control::srv::MoveWaypoints_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Response msg_;
};

class Init_MoveWaypoints_Response_success
{
public:
  Init_MoveWaypoints_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveWaypoints_Response_message success(::denso_motion_control::srv::MoveWaypoints_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveWaypoints_Response_message(msg_);
  }

private:
  ::denso_motion_control::srv::MoveWaypoints_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_motion_control::srv::MoveWaypoints_Response>()
{
  return denso_motion_control::srv::builder::Init_MoveWaypoints_Response_success();
}

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_WAYPOINTS__BUILDER_HPP_
