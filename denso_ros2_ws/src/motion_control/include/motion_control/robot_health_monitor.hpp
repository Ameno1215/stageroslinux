#pragma once

#include <atomic>
#include <string>
#include <functional>
#include <mutex>

#include "industrial_msgs/msg/robot_status.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "rcl_interfaces/msg/log.hpp"
#include "std_msgs/msg/string.hpp"

namespace motion_control
{

class RobotHealthMonitor
{
public:
  // Callback type: called when an error is detected or cleared
  using ErrorCallback   = std::function<void(const std::string& reason)>;
  using ClearedCallback = std::function<void()>;

  RobotHealthMonitor(
    rclcpp::Node* node,
    const std::string& model,                    // e.g. "vs060", "vp5243"
    const std::string& joint_state_topic = "/joint_states",
    bool require_drives_powered = false,
    const std::string& robot_status_topic = "/robot_status"
  );

  // Register callbacks
  void onError(ErrorCallback cb)   { on_error_   = cb; }
  void onCleared(ClearedCallback cb) { on_cleared_ = cb; }

  // Call this once the robot is initialized and in slave mode
  void setActive(bool active) { active_ = active; }

  // Query current status
  bool hasError() const { return has_error_.load(); }
  std::string getErrorMessage() const;

  // Manually clear (e.g. after operator reset on TP + re-init)
  void clearError();

private:
  void onJointStates(const sensor_msgs::msg::JointState::SharedPtr msg);
  void onRobotStatus(const industrial_msgs::msg::RobotStatus::SharedPtr msg);
  void onRosout(const rcl_interfaces::msg::Log::SharedPtr msg);
  void watchdogTick();
  void triggerError(const std::string& reason);
  void setErrorMessage(const std::string& reason);
  bool isStale(const rclcpp::Time& stamp, double timeout_s) const;

  rclcpp::Node* node_;

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr robot_error_sub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr robot_error_desc_sub_;
  rclcpp::Subscription<industrial_msgs::msg::RobotStatus>::SharedPtr robot_status_sub_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr  joint_sub_;
  rclcpp::Subscription<rcl_interfaces::msg::Log>::SharedPtr      rosout_sub_;
  rclcpp::TimerBase::SharedPtr                                   watchdog_timer_;
  rclcpp::CallbackGroup::SharedPtr                               health_callback_group_;

  std::atomic<bool>    has_error_{false};
  std::atomic<bool>    active_{false};
  bool                 is_staubli_{false};
  bool                 require_drives_powered_{false};
  std::string          robot_status_topic_;
  std::atomic<bool>    robot_status_received_{false};

  mutable std::mutex   error_msg_mtx_;
  std::string          error_msg_;

  rclcpp::Time         last_joint_state_time_;
  rclcpp::Time         last_robot_status_time_;

  ErrorCallback   on_error_;
  ClearedCallback on_cleared_;

  static constexpr double JS_TIMEOUT_S = 1.0;
  static constexpr double ROBOT_STATUS_TIMEOUT_S = 1.0;
};

} // namespace motion_control
