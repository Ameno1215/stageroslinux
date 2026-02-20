// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_robot_core_interfaces:msg/ExJoints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__STRUCT_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'joints'
#include "denso_robot_core_interfaces/msg/detail/joints__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__msg__ExJoints __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__msg__ExJoints __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ExJoints_
{
  using Type = ExJoints_<ContainerAllocator>;

  explicit ExJoints_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0l;
    }
  }

  explicit ExJoints_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0l;
    }
  }

  // field types and members
  using _mode_type =
    int32_t;
  _mode_type mode;
  using _joints_type =
    std::vector<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>>;
  _joints_type joints;

  // setters for named parameter idiom
  Type & set__mode(
    const int32_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__joints(
    const std::vector<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>> & _arg)
  {
    this->joints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__msg__ExJoints
    std::shared_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__msg__ExJoints
    std::shared_ptr<denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ExJoints_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->joints != other.joints) {
      return false;
    }
    return true;
  }
  bool operator!=(const ExJoints_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ExJoints_

// alias to use template instance with default allocator
using ExJoints =
  denso_robot_core_interfaces::msg::ExJoints_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__EX_JOINTS__STRUCT_HPP_
