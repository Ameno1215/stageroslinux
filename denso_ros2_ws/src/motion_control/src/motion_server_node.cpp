#include <rclcpp/rclcpp.hpp>
#include "motion_control/motion_server.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<motion_control::MotionServer>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
  } catch (const std::exception& e) {
    fprintf(stderr, "[motion_server main] Unhandled std::exception: %s\n", e.what());
  } catch (...) {
    fprintf(stderr, "[motion_server main] Unhandled non-std exception\n");
  }
  rclcpp::shutdown();
  return 1;
}
