cmake_minimum_required(VERSION 3.16)
project(robot_controller2_ackm LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# set the same behavior for windows as it is on linux
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
)

# find dependencies
find_package(backward_ros REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

## COMPILE
add_library(
  robot_controller2_ackm
  SHARED
  hardware/carlikebot_system.cpp
  hardware/motor.cpp
)
target_compile_features(robot_controller2_ackm PUBLIC cxx_std_17)
target_include_directories(robot_controller2_ackm PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
  $<INSTALL_INTERFACE:include/robot_controller2_ackm>
)
ament_target_dependencies(
  robot_controller2_ackm PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface robot_controller2_ackm.xml)

# INSTALL
install(
  DIRECTORY hardware/include/
  DESTINATION include/robot_controller2_ackm
)
install(
  DIRECTORY description/launch description/ros2_control description/urdf
  DESTINATION share/robot_controller2_ackm
)
install(
  DIRECTORY bringup/launch bringup/config
  DESTINATION share/robot_controller2_ackm
)
install(TARGETS robot_controller2_ackm
  EXPORT export_robot_controller2_ackm
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Unit test for modules
if(UNIT_TESTING)
  ament_add_gtest(module_unit_test
    test/modules/test_motor.cpp
    test/modules/ada_servo_driver.cpp

  )
  target_link_libraries(module_unit_test
    robot_controller2_ackm
  )
  # ament_target_dependencies(unit_test_publisher
  #   rclcpp
  #   std_msgs
  # )

endif()

# Package test
if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)

  ament_add_pytest_test(robot_controller2_ackm_urdf_xacro test/test_urdf_xacro.py)
  ament_add_pytest_test(view_robot_controller2_ackm_launch test/test_view_robot_launch.py)
  ament_add_pytest_test(run_robot_controller2_ackm_launch test/test_carlikebot_launch.py)
  ament_add_pytest_test(run_robot_controller2_ackm_launch_remapped test/test_carlikebot_launch_remapped.py)
endif()

## EXPORTS
ament_export_targets(export_robot_controller2_ackm HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
