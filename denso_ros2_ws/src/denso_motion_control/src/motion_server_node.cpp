#include <rclcpp/rclcpp.hpp>
#include "denso_motion_control/motion_server.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<denso_motion_control::MotionServer>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
