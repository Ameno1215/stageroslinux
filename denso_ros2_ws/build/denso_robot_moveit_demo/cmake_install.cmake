# Install script for directory: /home/antonin/workspace/denso_ros2_ws/src/denso_robot_drivers_ros2/denso_robot_moveit_demo

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/antonin/workspace/denso_ros2_ws/install/denso_robot_moveit_demo")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/ament_cmake_symlink_install/ament_cmake_symlink_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo" TYPE EXECUTABLE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/denso_robot_moveit_demo")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo"
         OLD_RPATH "/opt/ros/humble/lib:/opt/ros/humble/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_demo")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo" TYPE EXECUTABLE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/denso_robot_moveit_pickandplace")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace"
         OLD_RPATH "/opt/ros/humble/lib:/opt/ros/humble/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo" TYPE EXECUTABLE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara"
         OLD_RPATH "/opt/ros/humble/lib:/opt/ros/humble/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/denso_robot_moveit_demo/denso_robot_moveit_pickandplace_scara")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport.cmake"
         "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake" TYPE FILE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake" TYPE FILE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_demoExport-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport.cmake"
         "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake" TYPE FILE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake" TYPE FILE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplaceExport-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport.cmake"
         "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake" TYPE FILE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/denso_robot_moveit_demo/cmake" TYPE FILE FILES "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/CMakeFiles/Export/share/denso_robot_moveit_demo/cmake/export_denso_robot_moveit_pickandplace_scaraExport-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/antonin/workspace/denso_ros2_ws/build/denso_robot_moveit_demo/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
