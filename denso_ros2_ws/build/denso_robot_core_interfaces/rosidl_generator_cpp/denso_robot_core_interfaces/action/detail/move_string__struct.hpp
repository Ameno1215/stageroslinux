// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_robot_core_interfaces:action/MoveString.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_STRING__STRUCT_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_STRING__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_Goal __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_Goal __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_Goal_
{
  using Type = MoveString_Goal_<ContainerAllocator>;

  explicit MoveString_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->comp = 0l;
      this->pose = "";
      this->option = "";
    }
  }

  explicit MoveString_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc),
    option(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->comp = 0l;
      this->pose = "";
      this->option = "";
    }
  }

  // field types and members
  using _comp_type =
    int32_t;
  _comp_type comp;
  using _pose_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pose_type pose;
  using _option_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _option_type option;

  // setters for named parameter idiom
  Type & set__comp(
    const int32_t & _arg)
  {
    this->comp = _arg;
    return *this;
  }
  Type & set__pose(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__option(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->option = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_Goal
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_Goal
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_Goal_ & other) const
  {
    if (this->comp != other.comp) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->option != other.option) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_Goal_

// alias to use template instance with default allocator
using MoveString_Goal =
  denso_robot_core_interfaces::action::MoveString_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces


#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_Result __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_Result __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_Result_
{
  using Type = MoveString_Result_<ContainerAllocator>;

  explicit MoveString_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hresult = 0l;
    }
  }

  explicit MoveString_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hresult = 0l;
    }
  }

  // field types and members
  using _hresult_type =
    int32_t;
  _hresult_type hresult;

  // setters for named parameter idiom
  Type & set__hresult(
    const int32_t & _arg)
  {
    this->hresult = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_Result
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_Result
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_Result_ & other) const
  {
    if (this->hresult != other.hresult) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_Result_

// alias to use template instance with default allocator
using MoveString_Result =
  denso_robot_core_interfaces::action::MoveString_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces


#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_Feedback __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_Feedback_
{
  using Type = MoveString_Feedback_<ContainerAllocator>;

  explicit MoveString_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit MoveString_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _pose_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _pose_type pose;

  // setters for named parameter idiom
  Type & set__pose(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->pose = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_Feedback
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_Feedback
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_Feedback_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_Feedback_

// alias to use template instance with default allocator
using MoveString_Feedback =
  denso_robot_core_interfaces::action::MoveString_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "denso_robot_core_interfaces/action/detail/move_string__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Request __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_SendGoal_Request_
{
  using Type = MoveString_SendGoal_Request_<ContainerAllocator>;

  explicit MoveString_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit MoveString_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const denso_robot_core_interfaces::action::MoveString_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Request
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Request
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_SendGoal_Request_

// alias to use template instance with default allocator
using MoveString_SendGoal_Request =
  denso_robot_core_interfaces::action::MoveString_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Response __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_SendGoal_Response_
{
  using Type = MoveString_SendGoal_Response_<ContainerAllocator>;

  explicit MoveString_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit MoveString_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Response
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_SendGoal_Response
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_SendGoal_Response_

// alias to use template instance with default allocator
using MoveString_SendGoal_Response =
  denso_robot_core_interfaces::action::MoveString_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace denso_robot_core_interfaces
{

namespace action
{

struct MoveString_SendGoal
{
  using Request = denso_robot_core_interfaces::action::MoveString_SendGoal_Request;
  using Response = denso_robot_core_interfaces::action::MoveString_SendGoal_Response;
};

}  // namespace action

}  // namespace denso_robot_core_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Request __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_GetResult_Request_
{
  using Type = MoveString_GetResult_Request_<ContainerAllocator>;

  explicit MoveString_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit MoveString_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Request
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Request
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_GetResult_Request_

// alias to use template instance with default allocator
using MoveString_GetResult_Request =
  denso_robot_core_interfaces::action::MoveString_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "denso_robot_core_interfaces/action/detail/move_string__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Response __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_GetResult_Response_
{
  using Type = MoveString_GetResult_Response_<ContainerAllocator>;

  explicit MoveString_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit MoveString_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const denso_robot_core_interfaces::action::MoveString_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Response
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_GetResult_Response
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_GetResult_Response_

// alias to use template instance with default allocator
using MoveString_GetResult_Response =
  denso_robot_core_interfaces::action::MoveString_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces

namespace denso_robot_core_interfaces
{

namespace action
{

struct MoveString_GetResult
{
  using Request = denso_robot_core_interfaces::action::MoveString_GetResult_Request;
  using Response = denso_robot_core_interfaces::action::MoveString_GetResult_Response;
};

}  // namespace action

}  // namespace denso_robot_core_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "denso_robot_core_interfaces/action/detail/move_string__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__action__MoveString_FeedbackMessage __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveString_FeedbackMessage_
{
  using Type = MoveString_FeedbackMessage_<ContainerAllocator>;

  explicit MoveString_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit MoveString_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const denso_robot_core_interfaces::action::MoveString_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_FeedbackMessage
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__action__MoveString_FeedbackMessage
    std::shared_ptr<denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveString_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveString_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveString_FeedbackMessage_

// alias to use template instance with default allocator
using MoveString_FeedbackMessage =
  denso_robot_core_interfaces::action::MoveString_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace denso_robot_core_interfaces

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace denso_robot_core_interfaces
{

namespace action
{

struct MoveString
{
  /// The goal message defined in the action definition.
  using Goal = denso_robot_core_interfaces::action::MoveString_Goal;
  /// The result message defined in the action definition.
  using Result = denso_robot_core_interfaces::action::MoveString_Result;
  /// The feedback message defined in the action definition.
  using Feedback = denso_robot_core_interfaces::action::MoveString_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = denso_robot_core_interfaces::action::MoveString_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = denso_robot_core_interfaces::action::MoveString_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = denso_robot_core_interfaces::action::MoveString_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct MoveString MoveString;

}  // namespace action

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__ACTION__DETAIL__MOVE_STRING__STRUCT_HPP_
