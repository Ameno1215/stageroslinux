// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_motion_control:srv/MoveToPose.idl
// generated code does not contain a copyright notice

#ifndef DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__STRUCT_HPP_
#define DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__MoveToPose_Request __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__MoveToPose_Request __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveToPose_Request_
{
  using Type = MoveToPose_Request_<ContainerAllocator>;

  explicit MoveToPose_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->r1 = 0.0;
      this->r2 = 0.0;
      this->r3 = 0.0;
      this->r4 = 0.0;
      this->rotation_format = "";
      this->reference_frame = "";
      this->is_relative = false;
      this->cartesian_path = false;
      this->execute = false;
    }
  }

  explicit MoveToPose_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : rotation_format(_alloc),
    reference_frame(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0;
      this->y = 0.0;
      this->z = 0.0;
      this->r1 = 0.0;
      this->r2 = 0.0;
      this->r3 = 0.0;
      this->r4 = 0.0;
      this->rotation_format = "";
      this->reference_frame = "";
      this->is_relative = false;
      this->cartesian_path = false;
      this->execute = false;
    }
  }

  // field types and members
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;
  using _z_type =
    double;
  _z_type z;
  using _r1_type =
    double;
  _r1_type r1;
  using _r2_type =
    double;
  _r2_type r2;
  using _r3_type =
    double;
  _r3_type r3;
  using _r4_type =
    double;
  _r4_type r4;
  using _rotation_format_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _rotation_format_type rotation_format;
  using _reference_frame_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reference_frame_type reference_frame;
  using _is_relative_type =
    bool;
  _is_relative_type is_relative;
  using _cartesian_path_type =
    bool;
  _cartesian_path_type cartesian_path;
  using _execute_type =
    bool;
  _execute_type execute;

  // setters for named parameter idiom
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
  Type & set__r1(
    const double & _arg)
  {
    this->r1 = _arg;
    return *this;
  }
  Type & set__r2(
    const double & _arg)
  {
    this->r2 = _arg;
    return *this;
  }
  Type & set__r3(
    const double & _arg)
  {
    this->r3 = _arg;
    return *this;
  }
  Type & set__r4(
    const double & _arg)
  {
    this->r4 = _arg;
    return *this;
  }
  Type & set__rotation_format(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->rotation_format = _arg;
    return *this;
  }
  Type & set__reference_frame(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reference_frame = _arg;
    return *this;
  }
  Type & set__is_relative(
    const bool & _arg)
  {
    this->is_relative = _arg;
    return *this;
  }
  Type & set__cartesian_path(
    const bool & _arg)
  {
    this->cartesian_path = _arg;
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
    denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__MoveToPose_Request
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__MoveToPose_Request
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveToPose_Request_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->r1 != other.r1) {
      return false;
    }
    if (this->r2 != other.r2) {
      return false;
    }
    if (this->r3 != other.r3) {
      return false;
    }
    if (this->r4 != other.r4) {
      return false;
    }
    if (this->rotation_format != other.rotation_format) {
      return false;
    }
    if (this->reference_frame != other.reference_frame) {
      return false;
    }
    if (this->is_relative != other.is_relative) {
      return false;
    }
    if (this->cartesian_path != other.cartesian_path) {
      return false;
    }
    if (this->execute != other.execute) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveToPose_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveToPose_Request_

// alias to use template instance with default allocator
using MoveToPose_Request =
  denso_motion_control::srv::MoveToPose_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control


#ifndef _WIN32
# define DEPRECATED__denso_motion_control__srv__MoveToPose_Response __attribute__((deprecated))
#else
# define DEPRECATED__denso_motion_control__srv__MoveToPose_Response __declspec(deprecated)
#endif

namespace denso_motion_control
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct MoveToPose_Response_
{
  using Type = MoveToPose_Response_<ContainerAllocator>;

  explicit MoveToPose_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit MoveToPose_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_motion_control__srv__MoveToPose_Response
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_motion_control__srv__MoveToPose_Response
    std::shared_ptr<denso_motion_control::srv::MoveToPose_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveToPose_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveToPose_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveToPose_Response_

// alias to use template instance with default allocator
using MoveToPose_Response =
  denso_motion_control::srv::MoveToPose_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace denso_motion_control

namespace denso_motion_control
{

namespace srv
{

struct MoveToPose
{
  using Request = denso_motion_control::srv::MoveToPose_Request;
  using Response = denso_motion_control::srv::MoveToPose_Response;
};

}  // namespace srv

}  // namespace denso_motion_control

#endif  // DENSO_MOTION_CONTROL__SRV__DETAIL__MOVE_TO_POSE__STRUCT_HPP_
