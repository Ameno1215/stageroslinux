// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from denso_robot_core_interfaces:action/DriveValue.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__DRIVE_VALUE__BUILDER_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__DRIVE_VALUE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "denso_robot_core_interfaces/action/detail/drive_value__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_Goal_option
{
public:
  explicit Init_DriveValue_Goal_option(::denso_robot_core_interfaces::action::DriveValue_Goal & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_Goal option(::denso_robot_core_interfaces::action::DriveValue_Goal::_option_type arg)
  {
    msg_.option = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_Goal msg_;
};

class Init_DriveValue_Goal_passflag
{
public:
  explicit Init_DriveValue_Goal_passflag(::denso_robot_core_interfaces::action::DriveValue_Goal & msg)
  : msg_(msg)
  {}
  Init_DriveValue_Goal_option passflag(::denso_robot_core_interfaces::action::DriveValue_Goal::_passflag_type arg)
  {
    msg_.passflag = std::move(arg);
    return Init_DriveValue_Goal_option(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_Goal msg_;
};

class Init_DriveValue_Goal_pose
{
public:
  Init_DriveValue_Goal_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveValue_Goal_passflag pose(::denso_robot_core_interfaces::action::DriveValue_Goal::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_DriveValue_Goal_passflag(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_Goal>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_Goal_pose();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_Result_hresult
{
public:
  Init_DriveValue_Result_hresult()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_Result hresult(::denso_robot_core_interfaces::action::DriveValue_Result::_hresult_type arg)
  {
    msg_.hresult = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_Result>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_Result_hresult();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_Feedback_pose
{
public:
  Init_DriveValue_Feedback_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_Feedback pose(::denso_robot_core_interfaces::action::DriveValue_Feedback::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_Feedback>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_Feedback_pose();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_SendGoal_Request_goal
{
public:
  explicit Init_DriveValue_SendGoal_Request_goal(::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request goal(::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request msg_;
};

class Init_DriveValue_SendGoal_Request_goal_id
{
public:
  Init_DriveValue_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveValue_SendGoal_Request_goal goal_id(::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_DriveValue_SendGoal_Request_goal(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_SendGoal_Request>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_SendGoal_Request_goal_id();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_SendGoal_Response_stamp
{
public:
  explicit Init_DriveValue_SendGoal_Response_stamp(::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response stamp(::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response msg_;
};

class Init_DriveValue_SendGoal_Response_accepted
{
public:
  Init_DriveValue_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveValue_SendGoal_Response_stamp accepted(::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_DriveValue_SendGoal_Response_stamp(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_SendGoal_Response>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_SendGoal_Response_accepted();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_GetResult_Request_goal_id
{
public:
  Init_DriveValue_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_GetResult_Request goal_id(::denso_robot_core_interfaces::action::DriveValue_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_GetResult_Request>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_GetResult_Request_goal_id();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_GetResult_Response_result
{
public:
  explicit Init_DriveValue_GetResult_Response_result(::denso_robot_core_interfaces::action::DriveValue_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_GetResult_Response result(::denso_robot_core_interfaces::action::DriveValue_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_GetResult_Response msg_;
};

class Init_DriveValue_GetResult_Response_status
{
public:
  Init_DriveValue_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveValue_GetResult_Response_result status(::denso_robot_core_interfaces::action::DriveValue_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_DriveValue_GetResult_Response_result(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_GetResult_Response>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_GetResult_Response_status();
}

}  // namespace denso_robot_core_interfaces


namespace denso_robot_core_interfaces
{

namespace action
{

namespace builder
{

class Init_DriveValue_FeedbackMessage_feedback
{
public:
  explicit Init_DriveValue_FeedbackMessage_feedback(::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage feedback(::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage msg_;
};

class Init_DriveValue_FeedbackMessage_goal_id
{
public:
  Init_DriveValue_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DriveValue_FeedbackMessage_feedback goal_id(::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_DriveValue_FeedbackMessage_feedback(msg_);
  }

private:
  ::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::denso_robot_core_interfaces::action::DriveValue_FeedbackMessage>()
{
  return denso_robot_core_interfaces::action::builder::Init_DriveValue_FeedbackMessage_goal_id();
}

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__DRIVE_VALUE__BUILDER_HPP_
