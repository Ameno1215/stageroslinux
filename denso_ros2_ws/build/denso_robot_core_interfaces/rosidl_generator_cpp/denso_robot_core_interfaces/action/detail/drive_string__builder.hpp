// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:action/DriveString.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__DRIVE_STRING__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__DRIVE_STRING__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/action/detail/drive_string__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_Goal_option
{
public:
  explicit Init_DriveString_Goal_option(::denso_robot_core_interfaces::action::DriveString_Goal & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveString_Goal option(::denso_robot_core_interfaces::action::DriveString_Goal::_option_type arg)
  {
    msg_.option = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_Goal msg_;
};

class Init_DriveString_Goal_pose
{
public:
  Init_DriveString_Goal_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveString_Goal_option pose(::denso_robot_core_interfaces::action::DriveString_Goal::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_DriveString_Goal_option(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_Goal>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_Goal_pose();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_Result_hresult
{
public:
  Init_DriveString_Result_hresult()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::action::DriveString_Result hresult(::denso_robot_core_interfaces::action::DriveString_Result::_hresult_type arg)
  {
    msg_.hresult = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_Result>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_Result_hresult();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_Feedback_pose
{
public:
  Init_DriveString_Feedback_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::action::DriveString_Feedback pose(::denso_robot_core_interfaces::action::DriveString_Feedback::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_Feedback>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_Feedback_pose();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_SendGoal_Request_goal
{
public:
  explicit Init_DriveString_SendGoal_Request_goal(::denso_robot_core_interfaces::action::DriveString_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveString_SendGoal_Request goal(::denso_robot_core_interfaces::action::DriveString_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_SendGoal_Request msg_;
};

class Init_DriveString_SendGoal_Request_goal_id
{
public:
  Init_DriveString_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveString_SendGoal_Request_goal goal_id(::denso_robot_core_interfaces::action::DriveString_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_DriveString_SendGoal_Request_goal(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_SendGoal_Request>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_SendGoal_Request_goal_id();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_SendGoal_Response_stamp
{
public:
  explicit Init_DriveString_SendGoal_Response_stamp(::denso_robot_core_interfaces::action::DriveString_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveString_SendGoal_Response stamp(::denso_robot_core_interfaces::action::DriveString_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_SendGoal_Response msg_;
};

class Init_DriveString_SendGoal_Response_accepted
{
public:
  Init_DriveString_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveString_SendGoal_Response_stamp accepted(::denso_robot_core_interfaces::action::DriveString_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_DriveString_SendGoal_Response_stamp(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_SendGoal_Response>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_SendGoal_Response_accepted();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_GetResult_Request_goal_id
{
public:
  Init_DriveString_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::action::DriveString_GetResult_Request goal_id(::denso_robot_core_interfaces::action::DriveString_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_GetResult_Request>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_GetResult_Request_goal_id();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_GetResult_Response_result
{
public:
  explicit Init_DriveString_GetResult_Response_result(::denso_robot_core_interfaces::action::DriveString_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveString_GetResult_Response result(::denso_robot_core_interfaces::action::DriveString_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_GetResult_Response msg_;
};

class Init_DriveString_GetResult_Response_status
{
public:
  Init_DriveString_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveString_GetResult_Response_result status(::denso_robot_core_interfaces::action::DriveString_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_DriveString_GetResult_Response_result(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_GetResult_Response>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_GetResult_Response_status();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveString_FeedbackMessage_feedback
{
public:
  explicit Init_DriveString_FeedbackMessage_feedback(::denso_robot_core_interfaces::action::DriveString_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveString_FeedbackMessage feedback(::denso_robot_core_interfaces::action::DriveString_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_FeedbackMessage msg_;
};

class Init_DriveString_FeedbackMessage_goal_id
{
public:
  Init_DriveString_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveString_FeedbackMessage_feedback goal_id(::denso_robot_core_interfaces::action::DriveString_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_DriveString_FeedbackMessage_feedback(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveString_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveString_FeedbackMessage>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveString_FeedbackMessage_goal_id();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__DRIVE_STRING__BUILDER_HPP_
