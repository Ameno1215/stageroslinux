#include "motion_control/robot_health_monitor.hpp"

#include <sstream>
#include <vector>

#include "industrial_msgs/msg/tri_state.hpp"

namespace motion_control
{

RobotHealthMonitor::RobotHealthMonitor(
  rclcpp::Node* node,
  const std::string& model,
  const std::string& joint_state_topic,
  bool require_drives_powered,
  const std::string& robot_status_topic)
: node_(node),
  is_staubli_(model.rfind("staubli_", 0) == 0),
  require_drives_powered_(require_drives_powered),
  robot_status_topic_(robot_status_topic)
{
  last_joint_state_time_ = node_->now();
  last_robot_status_time_ = node_->now();
  health_callback_group_ = node_->create_callback_group(rclcpp::CallbackGroupType::Reentrant);

  rclcpp::SubscriptionOptions sub_options;
  sub_options.callback_group = health_callback_group_;

// --- 1. RobotError: primary signal — non-zero on ANY RC8 error ---
    const std::string error_topic      = "/" + model + "/RobotError";
    const std::string error_desc_topic = "/" + model + "/RobotErrorDescription";

  robot_error_sub_ = node_->create_subscription<std_msgs::msg::Int32>(
    error_topic,
    rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Int32::SharedPtr msg) {
        if (!active_.load()) return;

        int32_t error_code = msg->data;

        if (error_code != 0 && !has_error_.load()) {
            std::ostringstream oss;
            oss << "RC8 error: 0x" << std::hex << std::uppercase << error_code;
            triggerError(oss.str());
        }
        else if (error_code == 0 && has_error_.load()) {
            RCLCPP_INFO(node_->get_logger(),
                "[HealthMonitor] RC8 error cleared");
            clearError();
        }
    },
    sub_options);

  robot_error_desc_sub_ = node_->create_subscription<std_msgs::msg::String>(
    error_desc_topic,
    rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::String::SharedPtr msg) {
        if (!active_.load()) return;
        if (!msg->data.empty()) {
            // Enrichir le message d'erreur existant avec la description complète
            std::lock_guard<std::mutex> lk(error_msg_mtx_);
            error_msg_ += " | " + msg->data;
            RCLCPP_ERROR(node_->get_logger(),
                "[HealthMonitor] RC8 error details: %s", msg->data.c_str());
        }
    },
    sub_options);

  if (is_staubli_) {
    robot_status_sub_ = node_->create_subscription<industrial_msgs::msg::RobotStatus>(
      robot_status_topic_,
      rclcpp::SystemDefaultsQoS(),
      std::bind(&RobotHealthMonitor::onRobotStatus, this, std::placeholders::_1),
      sub_options);
  }

  // --- 2. Joint states watchdog: catches E-Stop / comms freeze ---
  joint_sub_ = node_->create_subscription<sensor_msgs::msg::JointState>(
    joint_state_topic,
    rclcpp::SensorDataQoS(),
    std::bind(&RobotHealthMonitor::onJointStates, this, std::placeholders::_1),
    sub_options);

  // --- 3. /rosout: captures RCLCPP_FATAL from the driver with RC8 error description ---
  rclcpp::QoS rosout_qos(1000);
  rosout_qos.keep_last(1000);
  rosout_qos.reliable();

  rosout_sub_ = node_->create_subscription<rcl_interfaces::msg::Log>(
    "/rosout",
    rosout_qos,
    std::bind(&RobotHealthMonitor::onRosout, this, std::placeholders::_1),
    sub_options);

  // --- 4. Watchdog timer: 500ms tick ---
  watchdog_timer_ = node_->create_wall_timer(
    std::chrono::milliseconds(500),
    std::bind(&RobotHealthMonitor::watchdogTick, this),
    health_callback_group_);

  RCLCPP_INFO(node_->get_logger(),
      "[HealthMonitor] Initialized for model='%s'. Watching: %s, %s%s",
      model.c_str(), error_topic.c_str(), joint_state_topic.c_str(),
      is_staubli_ ? (", " + robot_status_topic_).c_str() : "");
}

// ─── Joint states watchdog ──────────────────────────────────────────────────

void RobotHealthMonitor::onJointStates(const sensor_msgs::msg::JointState::SharedPtr)
{
  last_joint_state_time_ = node_->now();
}

void RobotHealthMonitor::onRobotStatus(const industrial_msgs::msg::RobotStatus::SharedPtr msg)
{
  if (!active_.load()) return;

  robot_status_received_.store(true);
  last_robot_status_time_ = node_->now();

  const auto true_state = industrial_msgs::msg::TriState::TRUE;
  const auto false_state = industrial_msgs::msg::TriState::FALSE;
  std::vector<std::string> faults;

  if (msg->e_stopped.val == true_state) {
    faults.emplace_back("E-stop active");
  }
  if (msg->in_error.val == true_state) {
    faults.emplace_back("robot reports in_error");
  }
  if (msg->error_code != 0) {
    std::ostringstream oss;
    oss << "robot error_code=0x" << std::hex << std::uppercase << msg->error_code;
    faults.push_back(oss.str());
  }
  if (require_drives_powered_ && msg->drives_powered.val == false_state) {
    faults.emplace_back("drives are OFF");
  }
  if (require_drives_powered_ && msg->motion_possible.val == false_state) {
    faults.emplace_back("motion_possible is FALSE");
  }

  if (!faults.empty()) {
    std::ostringstream oss;
    oss << "Staubli status fault: ";
    for (size_t i = 0; i < faults.size(); ++i) {
      if (i > 0) oss << " | ";
      oss << faults[i];
    }

    setErrorMessage(oss.str());
    if (!has_error_.exchange(true)) {
      RCLCPP_ERROR(node_->get_logger(), "[HealthMonitor] HARDWARE FAULT: %s", oss.str().c_str());
      if (on_error_) on_error_(oss.str());
    }
    return;
  }

  if (has_error_.load()) {
    RCLCPP_INFO(node_->get_logger(), "[HealthMonitor] Staubli status fault cleared");
    clearError();
  }
}

void RobotHealthMonitor::watchdogTick()
{
  if (!active_.load() || has_error_.load()) return;

  if (is_staubli_) {
    if (!robot_status_received_.load()) {
      triggerError("Staubli " + robot_status_topic_ + " not received");
      return;
    }
    if (isStale(last_robot_status_time_, ROBOT_STATUS_TIMEOUT_S)) {
      triggerError("Staubli " + robot_status_topic_ + " timeout");
      return;
    }
  }

  double age = (node_->now() - last_joint_state_time_).seconds();
  if (age > JS_TIMEOUT_S) {
    triggerError(
      "Joint states frozen for " + std::to_string(age) + "s"
      " — E-Stop pressed or b-CAP comms loss");
  }
}

// ─── /rosout relay ──────────────────────────────────────────────────────────

void RobotHealthMonitor::onRosout(const rcl_interfaces::msg::Log::SharedPtr msg)
{
  // Level 50 = FATAL in ROS2
  // We only relay FATAL messages from the DENSO driver — they contain
  // the actual RC8 error code and description from ExecGetCurErrorInfo()
  if (msg->level < 50) return;

  const bool from_driver =
    msg->name.find("DensoRobotHW")    != std::string::npos ||
    msg->name.find("denso_robot")     != std::string::npos ||
    msg->name.find("denso_robot_control") != std::string::npos;

  if (!from_driver) return;

  // Log in our node so it appears in motion_server logs too
  RCLCPP_ERROR(node_->get_logger(),
    "[HealthMonitor] RC8 driver FATAL: [%s] %s",
    msg->name.c_str(), msg->msg.c_str());

  // Enrich the error message if we already have one
  // (CurMode=0 triggers first, this adds the RC8 description)
  if (has_error_.load()) {
    std::lock_guard<std::mutex> lk(error_msg_mtx_);
    error_msg_ += " | RC8: " + msg->msg;
  }
}

// ─── Helpers ────────────────────────────────────────────────────────────────

void RobotHealthMonitor::triggerError(const std::string& reason)
{
  if (has_error_.exchange(true)) return; // already in error state

  setErrorMessage(reason);

  RCLCPP_ERROR(node_->get_logger(), "[HealthMonitor] HARDWARE FAULT: %s", reason.c_str());

  if (on_error_) on_error_(reason);
}

void RobotHealthMonitor::setErrorMessage(const std::string& reason)
{
  std::lock_guard<std::mutex> lk(error_msg_mtx_);
  error_msg_ = reason;
}

bool RobotHealthMonitor::isStale(const rclcpp::Time& stamp, double timeout_s) const
{
  return (node_->now() - stamp).seconds() > timeout_s;
}

void RobotHealthMonitor::clearError()
{
  has_error_.store(false);
  {
    std::lock_guard<std::mutex> lk(error_msg_mtx_);
    error_msg_.clear();
  }
  if (on_cleared_) on_cleared_();
}

std::string RobotHealthMonitor::getErrorMessage() const
{
  std::lock_guard<std::mutex> lk(error_msg_mtx_);
  return error_msg_;
}

} // namespace motion_control
