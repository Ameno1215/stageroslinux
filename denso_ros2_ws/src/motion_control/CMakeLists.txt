cmake_minimum_required(VERSION 3.8)
project(motion_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

# ---- Interfaces (srv) ----
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/InitRobot.srv"
  "srv/SetScaling.srv"
  "srv/GetCurrentPose.srv"
  "srv/GetJointState.srv"
  "srv/MoveToPose.srv"
  "srv/MoveJoints.srv"
  "srv/MoveWaypoints.srv"
  "srv/SetVirtualCage.srv"
  "srv/ManageBox.srv"
  DEPENDENCIES geometry_msgs
)

ament_export_dependencies(rosidl_default_runtime)

include_directories(include)

add_library(motion_server_lib
  src/motion_server.cpp
)
ament_target_dependencies(motion_server_lib
  rclcpp geometry_msgs moveit_ros_planning_interface moveit_msgs
)

# Make sure the generated interfaces are available to this target
# rosidl_target_interfaces(motion_server_lib
#   ${PROJECT_NAME} "rosidl_typesupport_cpp"
# )
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)
target_link_libraries(motion_server_lib "${cpp_typesupport_target}")


add_executable(denso_motion_server
  src/motion_server_node.cpp
)
target_link_libraries(denso_motion_server motion_server_lib)
ament_target_dependencies(denso_motion_server
  rclcpp
)

install(TARGETS
  motion_server_lib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(TARGETS
  denso_motion_server
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
)




ament_package()