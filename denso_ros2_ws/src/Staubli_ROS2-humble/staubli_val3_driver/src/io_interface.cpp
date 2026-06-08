
/*
 * Copyright 2021 Institute for Factory Automation and Production Systems (FAPS)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "staubli_val3_driver/io_interface.hpp"
#include "staubli_val3_driver/write_single_io_message.hpp"

#include "rclcpp/rclcpp.hpp"
#include "simple_message/simple_message.hpp"
#include "simple_message/socket/tcp_client.hpp"
#include "industrial_msgs/msg/service_return_code.hpp"

#include <arpa/inet.h>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std::placeholders;

// Initialize module names map
const std::map<int, std::string> IOInterface::MODULE_NAMES = {
  { staubli_msgs::msg::IOModule::USER_IN, "UserIn" },
  { staubli_msgs::msg::IOModule::BASIC_IN, "BasicIn" },
  { staubli_msgs::msg::IOModule::BASIC_OUT, "BasicOut" },
  { staubli_msgs::msg::IOModule::VALVE_OUT, "ValveOut" },
  { staubli_msgs::msg::IOModule::BASIC_IN_2, "BasicIn-2" },
  { staubli_msgs::msg::IOModule::BASIC_OUT_2, "BasicOut-2" }
};

IOInterface::IOInterface()
  : Node("io_interface")
  , connection_(nullptr)
  , publish_io_states_(true)
  , vacuum_module_id_(staubli_msgs::msg::IOModule::BASIC_IN)
  , vacuum_pin_(0)
  , port_(0)
{
}

IOInterface::~IOInterface()
{
}

bool IOInterface::init(const std::string& default_ip, int default_port)
{
  std::string ip;
  int port;

  // override IP/port with ROS params, if available
  this->declare_parameter<std::string>("robot_ip_address", default_ip);
  this->declare_parameter<int>("~port", default_port);
  this->get_parameter("robot_ip_address", ip);
  this->get_parameter("~port", port);

  // check for valid parameter values
  if (ip.empty())
  {
    RCLCPP_ERROR(this->get_logger(), "No valid robot IP address found. Please set the 'robot_ip_address' parameter");
    return false;
  }
  if (port <= 0 || port > 65535)
  {
    RCLCPP_ERROR(this->get_logger(), "No valid robot IP port found. Please set the '~port' parameter");
    return false;
  }

  ip_ = ip;
  port_ = port;
  RCLCPP_INFO(this->get_logger(), "io_interface: Using short IO connections (%s:%i)", ip_.c_str(), port_);
  return true;
}

void IOInterface::run()
{
  service = this->create_service<staubli_msgs::srv::WriteSingleIO>("io_interface/write_single_io", std::bind(&IOInterface::writeSingleIOCb, this, _1, _2));
  RCLCPP_INFO_STREAM(this->get_logger(), "Service " << service->get_service_name() << " is ready and running");

  this->declare_parameter<bool>("publish_io_states", true);
  this->declare_parameter<double>("io_state_poll_period_sec", 0.5);
  this->declare_parameter<int>("vacuum_module_id", staubli_msgs::msg::IOModule::BASIC_IN);
  this->declare_parameter<int>("vacuum_pin", 0);

  double poll_period_sec;
  this->get_parameter("publish_io_states", publish_io_states_);
  this->get_parameter("io_state_poll_period_sec", poll_period_sec);
  this->get_parameter("vacuum_module_id", vacuum_module_id_);
  this->get_parameter("vacuum_pin", vacuum_pin_);

  if (publish_io_states_)
  {
    const auto poll_ms = std::chrono::milliseconds(std::max(1, static_cast<int>(poll_period_sec * 1000.0)));
    io_states_pub_ = this->create_publisher<staubli_msgs::msg::IOStates>("io_states", 10);
    io_states_timer_ = this->create_wall_timer(poll_ms, std::bind(&IOInterface::publishIOStates, this));
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing IO states on " << io_states_pub_->get_topic_name());
  }
}

void IOInterface::writeSingleIOCb(const std::shared_ptr<staubli_msgs::srv::WriteSingleIO::Request> req, 
                                std::shared_ptr<staubli_msgs::srv::WriteSingleIO::Response> res)
{
  std::string module_name;

  // lookup module name for requested module id
  if (MODULE_NAMES.find(req->module.id) != MODULE_NAMES.end())
  {
    module_name = MODULE_NAMES.at(req->module.id);
  }
  else
  {
    RCLCPP_WARN(this->get_logger(), "Unknown module id given in WriteSingleIO service request!");
  }

  if (req->state)
  {
    RCLCPP_INFO(this->get_logger(), "Trying to set pin %d of module '%s'", req->pin, module_name.c_str());
  }
  else
  {
    RCLCPP_INFO(this->get_logger(), "Trying to clear pin %d of module '%s'", req->pin, module_name.c_str());
  }

  if (writeSingleIO(IOModule(req->module.id), req->pin, req->state))
  {
    res->code.val = industrial_msgs::msg::ServiceReturnCode::SUCCESS;
  }
  else
  {
    res->code.val = industrial_msgs::msg::ServiceReturnCode::FAILURE;
  }
}

bool IOInterface::writeSingleIO(IOModule moduleId, int pin, bool state)
{
  std::vector<char> body;
  appendInt32(body, static_cast<int>(moduleId));
  appendInt32(body, pin);
  body.push_back(state ? 1 : 0);

  int reply_code = industrial::simple_message::ReplyTypes::FAILURE;
  std::vector<char> reply_body;
  std::lock_guard<std::mutex> lock(connection_mutex_);
  if (!sendSimpleRequest(1621, body, reply_code, reply_body))
  {
    return false;
  }

  return (reply_code == industrial::simple_message::ReplyTypes::SUCCESS);
}

bool IOInterface::readVacuum(bool& state)
{
  int reply_code = industrial::simple_message::ReplyTypes::FAILURE;
  std::vector<char> reply_body;
  {
    std::lock_guard<std::mutex> lock(connection_mutex_);
    if (!sendSimpleRequest(1622, {}, reply_code, reply_body))
    {
      return false;
    }
  }

  if (reply_code != industrial::simple_message::ReplyTypes::SUCCESS || reply_body.empty())
  {
    return false;
  }

  state = reply_body[0] != 0;
  return true;
}

bool IOInterface::sendSimpleRequest(int msg_type, const std::vector<char>& body, int& reply_code, std::vector<char>& reply_body)
{
  reply_code = industrial::simple_message::ReplyTypes::FAILURE;
  reply_body.clear();

  int socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0)
  {
    RCLCPP_WARN(this->get_logger(), "Could not create IO socket: %s", std::strerror(errno));
    return false;
  }

  sockaddr_in address {};
  address.sin_family = AF_INET;
  address.sin_port = htons(port_);
  if (::inet_pton(AF_INET, ip_.c_str(), &address.sin_addr) <= 0)
  {
    RCLCPP_WARN(this->get_logger(), "Invalid robot IO IP address: %s", ip_.c_str());
    ::close(socket_fd);
    return false;
  }

  if (::connect(socket_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0)
  {
    RCLCPP_WARN(this->get_logger(), "Could not connect IO socket: %s", std::strerror(errno));
    ::close(socket_fd);
    return false;
  }

  std::vector<char> packet;
  appendInt32(packet, static_cast<int>(12 + body.size()));
  appendInt32(packet, msg_type);
  appendInt32(packet, industrial::simple_message::CommTypes::SERVICE_REQUEST);
  appendInt32(packet, industrial::simple_message::ReplyTypes::INVALID);
  packet.insert(packet.end(), body.begin(), body.end());

  if (::send(socket_fd, packet.data(), packet.size(), 0) != static_cast<ssize_t>(packet.size()))
  {
    RCLCPP_WARN(this->get_logger(), "Could not send IO request: %s", std::strerror(errno));
    ::close(socket_fd);
    return false;
  }

  int length = 0;
  if (!receiveExact(socket_fd, &length, sizeof(length)) || length < 12)
  {
    ::close(socket_fd);
    return false;
  }

  std::vector<char> payload(length);
  if (!receiveExact(socket_fd, payload.data(), payload.size()))
  {
    ::close(socket_fd);
    return false;
  }

  int reply_msg_type = 0;
  int comm_type = 0;
  std::memcpy(&reply_msg_type, payload.data(), sizeof(reply_msg_type));
  std::memcpy(&comm_type, payload.data() + 4, sizeof(comm_type));
  std::memcpy(&reply_code, payload.data() + 8, sizeof(reply_code));
  reply_body.assign(payload.begin() + 12, payload.end());

  ::close(socket_fd);
  return reply_msg_type == msg_type && comm_type == industrial::simple_message::CommTypes::SERVICE_REPLY;
}

bool IOInterface::receiveExact(int socket_fd, void* data, size_t size)
{
  auto* cursor = static_cast<char*>(data);
  size_t remaining = size;
  while (remaining > 0)
  {
    ssize_t received = ::recv(socket_fd, cursor, remaining, 0);
    if (received <= 0)
    {
      RCLCPP_WARN(this->get_logger(), "Could not receive IO reply: %s", received < 0 ? std::strerror(errno) : "socket closed");
      return false;
    }
    cursor += received;
    remaining -= static_cast<size_t>(received);
  }
  return true;
}

void IOInterface::appendInt32(std::vector<char>& data, int value)
{
  const auto* bytes = reinterpret_cast<const char*>(&value);
  data.insert(data.end(), bytes, bytes + sizeof(value));
}

void IOInterface::publishIOStates()
{
  bool vacuum_state = false;
  if (!readVacuum(vacuum_state))
  {
    RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 5000, "Could not read vacuum state from robot IO");
    return;
  }

  auto unknown = makeTriState(staubli_msgs::msg::TriState::UNKNOWN);
  staubli_msgs::msg::IOStates msg;
  msg.user_in.assign(2, unknown);
  msg.valve_out.assign(2, unknown);
  msg.basic_io_in.assign(16, unknown);
  msg.basic_io_out.assign(16, unknown);
  msg.basic_io_in_2.assign(16, unknown);
  msg.basic_io_out_2.assign(16, unknown);

  auto state = makeTriState(vacuum_state ? staubli_msgs::msg::TriState::TRUE : staubli_msgs::msg::TriState::FALSE);
  switch (vacuum_module_id_)
  {
    case staubli_msgs::msg::IOModule::USER_IN:
      if (vacuum_pin_ >= 0 && vacuum_pin_ < static_cast<int>(msg.user_in.size()))
        msg.user_in[vacuum_pin_] = state;
      break;
    case staubli_msgs::msg::IOModule::VALVE_OUT:
      if (vacuum_pin_ >= 0 && vacuum_pin_ < static_cast<int>(msg.valve_out.size()))
        msg.valve_out[vacuum_pin_] = state;
      break;
    case staubli_msgs::msg::IOModule::BASIC_IN:
      if (vacuum_pin_ >= 0 && vacuum_pin_ < static_cast<int>(msg.basic_io_in.size()))
        msg.basic_io_in[vacuum_pin_] = state;
      break;
    case staubli_msgs::msg::IOModule::BASIC_OUT:
      if (vacuum_pin_ >= 0 && vacuum_pin_ < static_cast<int>(msg.basic_io_out.size()))
        msg.basic_io_out[vacuum_pin_] = state;
      break;
    case staubli_msgs::msg::IOModule::BASIC_IN_2:
      if (vacuum_pin_ >= 0 && vacuum_pin_ < static_cast<int>(msg.basic_io_in_2.size()))
        msg.basic_io_in_2[vacuum_pin_] = state;
      break;
    case staubli_msgs::msg::IOModule::BASIC_OUT_2:
      if (vacuum_pin_ >= 0 && vacuum_pin_ < static_cast<int>(msg.basic_io_out_2.size()))
        msg.basic_io_out_2[vacuum_pin_] = state;
      break;
    default:
      break;
  }

  io_states_pub_->publish(msg);
}

staubli_msgs::msg::TriState IOInterface::makeTriState(int8_t value)
{
  staubli_msgs::msg::TriState state;
  state.val = value;
  return state;
}
