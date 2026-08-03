
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

#pragma once

#include "write_single_io.hpp"
#include "rclcpp/rclcpp.hpp"
#include "simple_message/smpl_msg_connection.hpp"
#include "simple_message/socket/simple_socket.hpp"
#include "staubli_msgs/msg/io_states.hpp"
#include "staubli_msgs/msg/tri_state.hpp"
#include "staubli_msgs/srv/write_single_io.hpp"
#include "netinet/in.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "stdio.h"


#include <mutex>
#include <string>
#include <vector>

class IOInterface : public rclcpp::Node
{
public:
  static const std::map<int, std::string> MODULE_NAMES;

  IOInterface();

  ~IOInterface();

  bool init(const std::string& default_ip = "", int default_port = industrial::simple_socket::StandardSocketPort::IO);

  void run();

  void writeSingleIOCb(const std::shared_ptr<staubli_msgs::srv::WriteSingleIO::Request> req, 
                     std::shared_ptr<staubli_msgs::srv::WriteSingleIO::Response> res);

  bool writeSingleIO(IOModule moduleId, int pin, bool state);

private:
  bool readVacuum(bool& state);
  void publishIOStates();
  bool sendSimpleRequest(int msg_type, const std::vector<char>& body, int& reply_code, std::vector<char>& reply_body);
  bool receiveExact(int socket_fd, void* data, size_t size);
  static void appendInt32(std::vector<char>& data, int value);
  static staubli_msgs::msg::TriState makeTriState(int8_t value);

  std::shared_ptr<industrial::smpl_msg_connection::SmplMsgConnection> connection_;
  rclcpp::Service<staubli_msgs::srv::WriteSingleIO>::SharedPtr service;
  rclcpp::Publisher<staubli_msgs::msg::IOStates>::SharedPtr io_states_pub_;
  rclcpp::TimerBase::SharedPtr io_states_timer_;
  std::mutex connection_mutex_;
  bool publish_io_states_;
  int vacuum_module_id_;
  int vacuum_pin_;
  std::string ip_;
  int port_;
};
