// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from bcap_service_interfaces:msg/Variant.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__BUILDER_HPP_
#define BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "bcap_service_interfaces/msg/detail/variant__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace bcap_service_interfaces
{

namespace msg
{

namespace builder
{

class Init_Variant_value
{
public:
  explicit Init_Variant_value(::bcap_service_interfaces::msg::Variant & msg)
  : msg_(msg)
  {}
  ::bcap_service_interfaces::msg::Variant value(::bcap_service_interfaces::msg::Variant::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bcap_service_interfaces::msg::Variant msg_;
};

class Init_Variant_vt
{
public:
  Init_Variant_vt()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Variant_value vt(::bcap_service_interfaces::msg::Variant::_vt_type arg)
  {
    msg_.vt = std::move(arg);
    return Init_Variant_value(msg_);
  }

private:
  ::bcap_service_interfaces::msg::Variant msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::bcap_service_interfaces::msg::Variant>()
{
  return bcap_service_interfaces::msg::builder::Init_Variant_vt();
}

}  // namespace bcap_service_interfaces

#endif  // BCAP_SERVICE_INTERFACES__MSG__DETAIL__VARIANT__BUILDER_HPP_
