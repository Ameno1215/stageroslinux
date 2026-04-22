#include "motion_control/robot_health_monitor.hpp"

namespace motion_control
{

RobotHealthMonitor::RobotHealthMonitor(
  rclcpp::Node* node,
  const std::string& model,
  const std::string& joint_state_topic)
: node_(node)
{
  last_joint_state_time_ = node_->now();

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
    });

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
    });

  // --- 2. Joint states watchdog: catches E-Stop / comms freeze ---
  joint_sub_ = node_->create_subscription<sensor_msgs::msg::JointState>(
    joint_state_topic,
    rclcpp::SensorDataQoS(),
    std::bind(&RobotHealthMonitor::onJointStates, this, std::placeholders::_1));

  // --- 3. /rosout: captures RCLCPP_FATAL from the driver with RC8 error description ---
  rclcpp::QoS rosout_qos(1000);
  rosout_qos.keep_last(1000);
  rosout_qos.reliable();

  rosout_sub_ = node_->create_subscription<rcl_interfaces::msg::Log>(
    "/rosout",
    rosout_qos,
    std::bind(&RobotHealthMonitor::onRosout, this, std::placeholders::_1));

  // --- 4. Watchdog timer: 500ms tick ---
  watchdog_timer_ = node_->create_wall_timer(
    std::chrono::milliseconds(500),
    std::bind(&RobotHealthMonitor::watchdogTick, this));

  RCLCPP_INFO(node_->get_logger(),
      "[HealthMonitor] Initialized for model='%s'. Watching: %s, %s",
      model.c_str(), error_topic.c_str(), joint_state_topic.c_str());
}

// ─── Joint states watchdog ──────────────────────────────────────────────────

void RobotHealthMonitor::onJointStates(const sensor_msgs::msg::JointState::SharedPtr)
{
  last_joint_state_time_ = node_->now();
}

void RobotHealthMonitor::watchdogTick()
{
  if (!active_.load() || has_error_.load()) return;

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

  {
    std::lock_guard<std::mutex> lk(error_msg_mtx_);
    error_msg_ = reason;
  }

  RCLCPP_ERROR(node_->get_logger(), "[HealthMonitor] HARDWARE FAULT: %s", reason.c_str());

  if (on_error_) on_error_(reason);
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