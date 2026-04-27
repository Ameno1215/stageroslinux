cmake_minimum_required(VERSION 3.8)
project(tool)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY effecteur_v1 effecteur_v2 effecteur_test
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
