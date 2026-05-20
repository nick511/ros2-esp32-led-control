cmake_minimum_required(VERSION 3.8)
project(led_control_msgs)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# List your message files here
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/LedStatus.msg"
)

ament_package()
