// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from bcap_service_interfaces:srv/Bcap.idl
// generated code does not contain a copyright notice

#ifndef BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__BUILDER_HPP_
#define BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "bcap_service_interfaces/srv/detail/bcap__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace bcap_service_interfaces
{

namespace srv
{

namespace builder
{

class Init_Bcap_Request_vnt_args
{
public:
  explicit Init_Bcap_Request_vnt_args(::bcap_service_interfaces::srv::Bcap_Request & msg)
  : msg_(msg)
  {}
  ::bcap_service_interfaces::srv::Bcap_Request vnt_args(::bcap_service_interfaces::srv::Bcap_Request::_vnt_args_type arg)
  {
    msg_.vnt_args = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bcap_service_interfaces::srv::Bcap_Request msg_;
};

class Init_Bcap_Request_func_id
{
public:
  Init_Bcap_Request_func_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bcap_Request_vnt_args func_id(::bcap_service_interfaces::srv::Bcap_Request::_func_id_type arg)
  {
    msg_.func_id = std::move(arg);
    return Init_Bcap_Request_vnt_args(msg_);
  }

private:
  ::bcap_service_interfaces::srv::Bcap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::bcap_service_interfaces::srv::Bcap_Request>()
{
  return bcap_service_interfaces::srv::builder::Init_Bcap_Request_func_id();
}

}  // namespace bcap_service_interfaces


namespace bcap_service_interfaces
{

namespace srv
{

namespace builder
{

class Init_Bcap_Response_vnt_ret
{
public:
  explicit Init_Bcap_Response_vnt_ret(::bcap_service_interfaces::srv::Bcap_Response & msg)
  : msg_(msg)
  {}
  ::bcap_service_interfaces::srv::Bcap_Response vnt_ret(::bcap_service_interfaces::srv::Bcap_Response::_vnt_ret_type arg)
  {
    msg_.vnt_ret = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bcap_service_interfaces::srv::Bcap_Response msg_;
};

class Init_Bcap_Response_hresult
{
public:
  Init_Bcap_Response_hresult()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bcap_Response_vnt_ret hresult(::bcap_service_interfaces::srv::Bcap_Response::_hresult_type arg)
  {
    msg_.hresult = std::move(arg);
    return Init_Bcap_Response_vnt_ret(msg_);
  }

private:
  ::bcap_service_interfaces::srv::Bcap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::bcap_service_interfaces::srv::Bcap_Response>()
{
  return bcap_service_interfaces::srv::builder::Init_Bcap_Response_hresult();
}

}  // namespace bcap_service_interfaces

#endif  // BCAP_SERVICE_INTERFACES__SRV__DETAIL__BCAP__BUILDER_HPP_
