cmake_minimum_required(VERSION 3.0.2)
project(point_tf_changer)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

set(PCL_DIR "/usr/lib/x86_64-linux-gnu/cmake/pcl/")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  tf
  pcl_ros
)

catkin_package()
       

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(pc2_tf_changer src/pc2_tf_changer.cpp)
add_dependencies(pc2_tf_changer ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(pc2_tf_changer
  ${catkin_LIBRARIES}
)

