// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_robot_core_interfaces:msg/PoseData.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__STRUCT_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'exjoints'
#include "denso_robot_core_interfaces/msg/detail/ex_joints__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__msg__PoseData __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__msg__PoseData __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PoseData_
{
  using Type = PoseData_<ContainerAllocator>;

  explicit PoseData_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : exjoints(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0l;
      this->passflag = 0l;
    }
  }

  explicit PoseData_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : exjoints(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0l;
      this->passflag = 0l;
    }
  }

  // field types and members
  using _value_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _value_type value;
  using _type_type =
    int32_t;
  _type_type type;
  using _passflag_type =
    int32_t;
  _passflag_type passflag;
  using _exjoints_type =
    denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator>;
  _exjoints_type exjoints;

  // setters for named parameter idiom
  Type & set__value(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->value = _arg;
    return *this;
  }
  Type & set__type(
    const int32_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__passflag(
    const int32_t & _arg)
  {
    this->passflag = _arg;
    return *this;
  }
  Type & set__exjoints(
    const denso_robot_core_interfaces::msg::ExJoints_<ContainerAllocator> & _arg)
  {
    this->exjoints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__msg__PoseData
    std::shared_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__msg__PoseData
    std::shared_ptr<denso_robot_core_interfaces::msg::PoseData_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PoseData_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    if (this->passflag != other.passflag) {
      return false;
    }
    if (this->exjoints != other.exjoints) {
      return false;
    }
    return true;
  }
  bool operator!=(const PoseData_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PoseData_

// alias to use template instance with default allocator
using PoseData =
  denso_robot_core_interfaces::msg::PoseData_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__POSE_DATA__STRUCT_HPP_
