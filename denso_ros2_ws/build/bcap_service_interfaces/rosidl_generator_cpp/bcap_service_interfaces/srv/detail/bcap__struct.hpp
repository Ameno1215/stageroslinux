// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__STRUCT_HPP_
#define BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'vnt_args'
#include "bcap_service_interfaces/msg/detail/variant__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__bcap_service_interfaces__srv__Bcap_Request __attribute__((deprecated))
#else
# define DEPRECATED__bcap_service_interfaces__srv__Bcap_Request __declspec(deprecated)
#endif

namespace bcap_service_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Bcap_Request_
{
  using Type = Bcap_Request_<ContainerAllocator>;

  explicit Bcap_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->func_id = 0l;
    }
  }

  explicit Bcap_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->func_id = 0l;
    }
  }

  // field types and members
  using _func_id_type =
    int32_t;
  _func_id_type func_id;
  using _vnt_args_type =
    std::vector<bcap_service_interfaces::msg::Variant_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bcap_service_interfaces::msg::Variant_<ContainerAllocator>>>;
  _vnt_args_type vnt_args;

  // setters for named parameter idiom
  Type & set__func_id(
    const int32_t & _arg)
  {
    this->func_id = _arg;
    return *this;
  }
  Type & set__vnt_args(
    const std::vector<bcap_service_interfaces::msg::Variant_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bcap_service_interfaces::msg::Variant_<ContainerAllocator>>> & _arg)
  {
    this->vnt_args = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bcap_service_interfaces__srv__Bcap_Request
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bcap_service_interfaces__srv__Bcap_Request
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Bcap_Request_ & other) const
  {
    if (this->func_id != other.func_id) {
      return false;
    }
    if (this->vnt_args != other.vnt_args) {
      return false;
    }
    return true;
  }
  bool operator!=(const Bcap_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Bcap_Request_

// alias to use template instance with default allocator
using Bcap_Request =
  bcap_service_interfaces::srv::Bcap_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace bcap_service_interfaces


// Include directives for member types
// Member 'vnt_ret'
// already included above
// #include "bcap_service_interfaces/msg/detail/variant__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__bcap_service_interfaces__srv__Bcap_Response __attribute__((deprecated))
#else
# define DEPRECATED__bcap_service_interfaces__srv__Bcap_Response __declspec(deprecated)
#endif

namespace bcap_service_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Bcap_Response_
{
  using Type = Bcap_Response_<ContainerAllocator>;

  explicit Bcap_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : vnt_ret(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->hresult = 0l;
    }
  }

  explicit Bcap_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : vnt_ret(_alloc, _init)
  {
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
  using _vnt_ret_type =
    bcap_service_interfaces::msg::Variant_<ContainerAllocator>;
  _vnt_ret_type vnt_ret;

  // setters for named parameter idiom
  Type & set__hresult(
    const int32_t & _arg)
  {
    this->hresult = _arg;
    return *this;
  }
  Type & set__vnt_ret(
    const bcap_service_interfaces::msg::Variant_<ContainerAllocator> & _arg)
  {
    this->vnt_ret = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bcap_service_interfaces__srv__Bcap_Response
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bcap_service_interfaces__srv__Bcap_Response
    std::shared_ptr<bcap_service_interfaces::srv::Bcap_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Bcap_Response_ & other) const
  {
    if (this->hresult != other.hresult) {
      return false;
    }
    if (this->vnt_ret != other.vnt_ret) {
      return false;
    }
    return true;
  }
  bool operator!=(const Bcap_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Bcap_Response_

// alias to use template instance with default allocator
using Bcap_Response =
  bcap_service_interfaces::srv::Bcap_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace bcap_service_interfaces

namespace bcap_service_interfaces
{

namespace srv
{

struct Bcap
{
  using Request = bcap_service_interfaces::srv::Bcap_Request;
  using Response = bcap_service_interfaces::srv::Bcap_Response;
};

}  // namespace srv

}  // namespace bcap_service_interfaces

#endif  // BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__STRUCT_HPP_
