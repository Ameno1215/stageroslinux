// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from denso_robot_core_interfaces:msg/UserIO.idl
// generated code does not contain a copyright notice

#ifndef DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__STRUCT_HPP_
#define DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__denso_robot_core_interfaces__msg__UserIO __attribute__((deprecated))
#else
# define DEPRECATED__denso_robot_core_interfaces__msg__UserIO __declspec(deprecated)
#endif

namespace denso_robot_core_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct UserIO_
{
  using Type = UserIO_<ContainerAllocator>;

  explicit UserIO_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->offset = 0l;
      this->size = 0l;
    }
  }

  explicit UserIO_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->offset = 0l;
      this->size = 0l;
    }
  }

  // field types and members
  using _offset_type =
    int32_t;
  _offset_type offset;
  using _size_type =
    int32_t;
  _size_type size;
  using _value_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _value_type value;

  // setters for named parameter idiom
  Type & set__offset(
    const int32_t & _arg)
  {
    this->offset = _arg;
    return *this;
  }
  Type & set__size(
    const int32_t & _arg)
  {
    this->size = _arg;
    return *this;
  }
  Type & set__value(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int32_t MIN_USERIO_OFFSET =
    128;
  static constexpr int32_t USERIO_ALIGNMENT =
    8;

  // pointer types
  using RawPtr =
    denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator> *;
  using ConstRawPtr =
    const denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__denso_robot_core_interfaces__msg__UserIO
    std::shared_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__denso_robot_core_interfaces__msg__UserIO
    std::shared_ptr<denso_robot_core_interfaces::msg::UserIO_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const UserIO_ & other) const
  {
    if (this->offset != other.offset) {
      return false;
    }
    if (this->size != other.size) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const UserIO_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct UserIO_

// alias to use template instance with default allocator
using UserIO =
  denso_robot_core_interfaces::msg::UserIO_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t UserIO_<ContainerAllocator>::MIN_USERIO_OFFSET;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t UserIO_<ContainerAllocator>::USERIO_ALIGNMENT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace denso_robot_core_interfaces

#endif  // DENSO_ROBOT_CORE_INTERFACES__MSG__DETAIL__USER_IO__STRUCT_HPP_
