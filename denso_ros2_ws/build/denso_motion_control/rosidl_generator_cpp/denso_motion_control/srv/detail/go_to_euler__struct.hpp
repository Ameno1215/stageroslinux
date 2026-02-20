// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_motion_control:srv/GoToEuler.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__STRUCT_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__GoToEuler_Request __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__GoToEuler_Request __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GoToEuler_Request_
{
  using Type = GoToEuler_Request_<ContainerAllocator>;

  explicit GoToEuler_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_id = "";
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->rx = 0.0;
      this->ry = 0.0;
      this->rz = 0.0;
      this->execute = false;
    }
  }

  explicit GoToEuler_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : frame_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->frame_id = "";
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->rx = 0.0;
      this->ry = 0.0;
      this->rz = 0.0;
      this->execute = false;
    }
  }

  // field types and members
  using _frame_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _frame_id_type frame_id;
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;
  using _z_type =
    double;
  _z_type z;
  using _rx_type =
    double;
  _rx_type rx;
  using _ry_type =
    double;
  _ry_type ry;
  using _rz_type =
    double;
  _rz_type rz;
  using _execute_type =
    bool;
  _execute_type execute;

  // setters for named parameter idiom
  Type & set__frame_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->frame_id = _arg;
    return *this;
  }
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const double & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const double & _arg)
  {
    this->z = _arg;
    return *this;
  }
  Type & set__rx(
    const double & _arg)
  {
    this->rx = _arg;
    return *this;
  }
  Type & set__ry(
    const double & _arg)
  {
    this->ry = _arg;
    return *this;
  }
  Type & set__rz(
    const double & _arg)
  {
    this->rz = _arg;
    return *this;
  }
  Type & set__execute(
    const bool & _arg)
  {
    this->execute = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__GoToEuler_Request
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__GoToEuler_Request
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToEuler_Request_ & other) const
  {
    if (this->frame_id != other.frame_id) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->rx != other.rx) {
      return false;
    }
    if (this->ry != other.ry) {
      return false;
    }
    if (this->rz != other.rz) {
      return false;
    }
    if (this->execute != other.execute) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToEuler_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToEuler_Request_

// alias to use template instance with default allocator
using GoToEuler_Request =
  denso_motion_control::srv::GoToEuler_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__GoToEuler_Response __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__GoToEuler_Response __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GoToEuler_Response_
{
  using Type = GoToEuler_Response_<ContainerAllocator>;

  explicit GoToEuler_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit GoToEuler_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__GoToEuler_Response
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__GoToEuler_Response
    std::shared_ptr<denso_motion_control::srv::GoToEuler_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToEuler_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToEuler_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToEuler_Response_

// alias to use template instance with default allocator
using GoToEuler_Response =
  denso_motion_control::srv::GoToEuler_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control

namespace denso_motion_control
{

namespace srv
{

struct GoToEuler
{
  using Request = denso_motion_control::srv::GoToEuler_Request;
  using Response = denso_motion_control::srv::GoToEuler_Response;
};

}  // namespace srv

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__GO_TO_EULER__STRUCT_HPP_
