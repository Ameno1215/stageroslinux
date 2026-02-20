// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__STRUCT_HPP_
#define BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__bcap_service_interfaces__msg__Variant __attribute__((deprecated))
#else
# define DEPRECATED__bcap_service_interfaces__msg__Variant __declspec(deprecated)
#endif

namespace bcap_service_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Variant_
{
  using Type = Variant_<ContainerAllocator>;

  explicit Variant_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->vt = 0;
      this->value = "";
    }
  }

  explicit Variant_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : value(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->vt = 0;
      this->value = "";
    }
  }

  // field types and members
  using _vt_type =
    int16_t;
  _vt_type vt;
  using _value_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _value_type value;

  // setters for named parameter idiom
  Type & set__vt(
    const int16_t & _arg)
  {
    this->vt = _arg;
    return *this;
  }
  Type & set__value(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    bcap_service_interfaces::msg::Variant_<ContainerAllocator> *;
  using ConstRawPtr =
    const bcap_service_interfaces::msg::Variant_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bcap_service_interfaces::msg::Variant_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bcap_service_interfaces::msg::Variant_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bcap_service_interfaces__msg__Variant
    std::shared_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bcap_service_interfaces__msg__Variant
    std::shared_ptr<bcap_service_interfaces::msg::Variant_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Variant_ & other) const
  {
    if (this->vt != other.vt) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const Variant_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Variant_

// alias to use template instance with default allocator
using Variant =
  bcap_service_interfaces::msg::Variant_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace bcap_service_interfaces

#endif  // BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__STRUCT_HPP_
