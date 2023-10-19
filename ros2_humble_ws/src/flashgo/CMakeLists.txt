cmake_minimum_required(VERSION 3.5)
project(flashgo)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

include_directories(include)

add_executable(flashgo_node src/flashgo_node.cpp src/flashgo.cpp)
add_executable(flashgo_client src/flashgo_client.cpp)

ament_target_dependencies(flashgo_node
  rclcpp
  sensor_msgs
)
ament_target_dependencies(flashgo_client
  rclcpp
)

install(TARGETS
  flashgo_node
  flashgo_client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
