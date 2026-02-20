// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_motion_control:srv/SetScaling.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__SET_SCALING__STRUCT_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__SET_SCALING__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__SetScaling_Request __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__SetScaling_Request __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetScaling_Request_
{
  using Type = SetScaling_Request_<ContainerAllocator>;

  explicit SetScaling_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity_scale = 0.0;
      this->accel_scale = 0.0;
    }
  }

  explicit SetScaling_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity_scale = 0.0;
      this->accel_scale = 0.0;
    }
  }

  // field types and members
  using _velocity_scale_type =
    double;
  _velocity_scale_type velocity_scale;
  using _accel_scale_type =
    double;
  _accel_scale_type accel_scale;

  // setters for named parameter idiom
  Type & set__velocity_scale(
    const double & _arg)
  {
    this->velocity_scale = _arg;
    return *this;
  }
  Type & set__accel_scale(
    const double & _arg)
  {
    this->accel_scale = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_motion_control::srv::SetScaling_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::SetScaling_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::SetScaling_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::SetScaling_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__SetScaling_Request
    std::shared_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__SetScaling_Request
    std::shared_ptr<denso_motion_control::srv::SetScaling_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetScaling_Request_ & other) const
  {
    if (this->velocity_scale != other.velocity_scale) {
      return false;
    }
    if (this->accel_scale != other.accel_scale) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetScaling_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetScaling_Request_

// alias to use template instance with default allocator
using SetScaling_Request =
  denso_motion_control::srv::SetScaling_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__SetScaling_Response __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__SetScaling_Response __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetScaling_Response_
{
  using Type = SetScaling_Response_<ContainerAllocator>;

  explicit SetScaling_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetScaling_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
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

  // constant declarations

  // pointer types
  using RawPtr =
    denso_motion_control::srv::SetScaling_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::SetScaling_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::SetScaling_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::SetScaling_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__SetScaling_Response
    std::shared_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__SetScaling_Response
    std::shared_ptr<denso_motion_control::srv::SetScaling_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetScaling_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetScaling_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetScaling_Response_

// alias to use template instance with default allocator
using SetScaling_Response =
  denso_motion_control::srv::SetScaling_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control

namespace denso_motion_control
{

namespace srv
{

struct SetScaling
{
  using Request = denso_motion_control::srv::SetScaling_Request;
  using Response = denso_motion_control::srv::SetScaling_Response;
};

}  // namespace srv

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__SET_SCALING__STRUCT_HPP_
