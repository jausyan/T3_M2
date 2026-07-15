cmake_minimum_required(VERSION 3.8)
project(t3_pose_estimation)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
add_compile_options(-Wall -Wextra)

# Prefer the system OpenCV (the one cv_bridge is linked against) over any
# locally installed OpenCV found first on this machine — mixing the two
# crashes at runtime. Must be set BEFORE cv_bridge's find_dependency(OpenCV).
if(NOT DEFINED OpenCV_DIR AND EXISTS "/usr/lib/x86_64-linux-gnu/cmake/opencv4")
  set(OpenCV_DIR "/usr/lib/x86_64-linux-gnu/cmake/opencv4")
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(t3_interfaces REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs calib3d video)
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

# ---------------------------------------------------------- frame_client_node
add_executable(frame_client_node src/frame_client_node.cpp)
target_include_directories(frame_client_node PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_link_libraries(frame_client_node
  ${OpenCV_LIBS} CURL::libcurl ${JSONCPP_LIBRARIES})
ament_target_dependencies(frame_client_node
  rclcpp std_msgs sensor_msgs cv_bridge t3_interfaces)

# --------------------------------------------------------- pose_estimator_node
add_executable(pose_estimator_node src/pose_estimator_node.cpp)
target_link_libraries(pose_estimator_node ${OpenCV_LIBS})
ament_target_dependencies(pose_estimator_node
  rclcpp std_msgs sensor_msgs geometry_msgs nav_msgs tf2_ros cv_bridge t3_interfaces)

install(TARGETS frame_client_node pose_estimator_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch config rviz
  DESTINATION share/${PROJECT_NAME})

ament_package()
