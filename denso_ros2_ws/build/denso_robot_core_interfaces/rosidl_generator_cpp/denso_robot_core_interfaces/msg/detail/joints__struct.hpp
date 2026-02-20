// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_robot_core_interfaces:msg/Joints.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__STRUCT_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__msg__Joints __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__msg__Joints __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Joints_
{
  using Type = Joints_<ContainerAllocator>;

  explicit Joints_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->joint = 0l;
      this->value = 0.0;
    }
  }

  explicit Joints_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->joint = 0l;
      this->value = 0.0;
    }
  }

  // field types and members
  using _joint_type =
    int32_t;
  _joint_type joint;
  using _value_type =
    double;
  _value_type value;

  // setters for named parameter idiom
  Type & set__joint(
    const int32_t & _arg)
  {
    this->joint = _arg;
    return *this;
  }
  Type & set__value(
    const double & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::msg::Joints_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::msg::Joints_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__msg__Joints
    std::shared_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__msg__Joints
    std::shared_ptr<denso_robot_core_interfaces::msg::Joints_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Joints_ & other) const
  {
    if (this->joint != other.joint) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const Joints_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Joints_

// alias to use template instance with default allocator
using Joints =
  denso_robot_core_interfaces::msg::Joints_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__JOINTS__STRUCT_HPP_
