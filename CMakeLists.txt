cmake_minimum_required(VERSION 2.8.3)
project(xyconverter)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)
add_message_files(
  FILES
  Cartesian.msg
  Polar.msg
)
generate_messages(
DEPENDENCIES
std_msgs
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES xyconverter
CATKIN_DEPENDS message_runtime
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(tester_node src/tester.cpp)
target_link_libraries(tester_node ${catkin_LIBRARIES})
#add_dependencies()

add_executable(receiver_node src/receiver.cpp)
target_link_libraries(receiver_node ${catkin_LIBRARIES})
#add_dependencies()

add_executable(keyboard_node src/keyboardxy.cpp)
target_link_libraries(keyboard_node ${catkin_LIBRARIES})
#add_dependencies()

add_executable(parser_node src/parserxy.cpp)
target_link_libraries(parser_node ${catkin_LIBRARIES})
#add_dependencies()

add_executable(converter_node src/converter.cpp)
target_link_libraries(converter_node ${catkin_LIBRARIES})
#add_dependencies()
