// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_motion_control:srv/GetCurrentPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__STRUCT_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__GetCurrentPose_Request __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__GetCurrentPose_Request __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCurrentPose_Request_
{
  using Type = GetCurrentPose_Request_<ContainerAllocator>;

  explicit GetCurrentPose_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_id = "";
      this->child_frame_id = "";
    }
  }

  explicit GetCurrentPose_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : frame_id(_alloc),
    child_frame_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_id = "";
      this->child_frame_id = "";
    }
  }

  // field types and members
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _child_frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _child_frame_id_type child_frame_id;

  // setters for named parameter idiom
  Type & set__frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__child_frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->child_frame_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__GetCurrentPose_Request
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__GetCurrentPose_Request
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCurrentPose_Request_ & other) const
  {
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->child_frame_id != other.child_frame_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCurrentPose_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCurrentPose_Request_

// alias to use template instance with default allocator
using GetCurrentPose_Request =
  denso_motion_control::srv::GetCurrentPose_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__GetCurrentPose_Response __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__GetCurrentPose_Response __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetCurrentPose_Response_
{
  using Type = GetCurrentPose_Response_<ContainerAllocator>;

  explicit GetCurrentPose_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit GetCurrentPose_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc),
    pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _pose_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _pose_type pose;
  using _euler_rpy_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _euler_rpy_type euler_rpy;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__euler_rpy(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->euler_rpy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__GetCurrentPose_Response
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__GetCurrentPose_Response
    std::shared_ptr<denso_motion_control::srv::GetCurrentPose_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetCurrentPose_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->euler_rpy != other.euler_rpy) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetCurrentPose_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetCurrentPose_Response_

// alias to use template instance with default allocator
using GetCurrentPose_Response =
  denso_motion_control::srv::GetCurrentPose_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control

namespace denso_motion_control
{

namespace srv
{

struct GetCurrentPose
{
  using Request = denso_motion_control::srv::GetCurrentPose_Request;
  using Response = denso_motion_control::srv::GetCurrentPose_Response;
};

}  // namespace srv

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GET_CURRENT_POSE__STRUCT_HPP_
