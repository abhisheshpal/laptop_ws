cmake_minimum_required(VERSION 2.8.3)
project(thorvald_2d_nav)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  move_base
  roscpp
  rospy
  geometry_msgs
  sensor_msgs
  std_msgs
  actionlib_msgs
  tf
  visualization_msgs
  message_generation
  nav_msgs
  std_srvs
)

find_package(Eigen3 REQUIRED)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
 add_compile_options(-std=c++11)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
add_message_files(
   FILES
   scan_detected_line.msg
   landmarks.msg
 )

## Generate services in the 'srv' folder
 add_service_files(
   DIRECTORY srv
   FILES
   GpsSwitch.srv
   sub_goal.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#  DIRECTORY action
#  FILES gps_switch.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs geometry_msgs actionlib_msgs std_srvs# Or other packages containing msgs
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES thorvald_2dnav
 CATKIN_DEPENDS 
  actionlib_msgs
  move_base
  roscpp
  rospy
  geometry_msgs
  sensor_msgs
  std_msgs
  actionlib_msgs
  tf
  visualization_msgs
  message_generation
  nav_msgs
  std_srvs

#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(include/${PROJECT_NAME})
include_directories(
  ${catkin_INCLUDE_DIRS}
)

include_directories(EIGEN3_INCLUDE_DIR)
include_directories(/usr/include/eigen3)
	
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
#target_link_libraries(hoge )

## Declare a C++ library
# add_library(thorvald_2dnav
#   src/${PROJECT_NAME}/thorvald_2dnav.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
 add_executable(thorvald_laserscan src/thorvald_laserscan.cpp)
 target_link_libraries(thorvald_laserscan ${catkin_LIBRARIES})

 add_executable(thorvald_RANSAC src/thorvald_RANSAC.cpp)
 target_link_libraries(thorvald_RANSAC ${catkin_LIBRARIES})

 add_executable(thorvald_control_modes src/thorvald_control_modes.cpp)
 target_link_libraries(thorvald_control_modes ${catkin_LIBRARIES})

 add_executable(thorvald_line_SLAM src/thorvald_line_SLAM.cpp)
 target_link_libraries(thorvald_line_SLAM ${catkin_LIBRARIES})

 add_executable(thorvald_row_transition src/thorvald_row_transition.cpp)
 target_link_libraries(thorvald_row_transition ${catkin_LIBRARIES})

 add_executable(test_RANSAC src/test_RANSAC.cpp)
 target_link_libraries(test_RANSAC ${catkin_LIBRARIES})

 add_executable(test_row_transition src/test_row_transition.cpp)
 target_link_libraries(test_row_transition ${catkin_LIBRARIES})

 add_executable(test_control_modes src/test_control_modes.cpp)
 target_link_libraries(test_control_modes ${catkin_LIBRARIES})

 add_executable(test_line_SLAM src/test_line_SLAM.cpp)
 target_link_libraries(test_line_SLAM ${catkin_LIBRARIES})

 add_executable(fastSLAM src/fastSLAM.cpp)
 target_link_libraries(fastSLAM ${catkin_LIBRARIES} ${PYTHON_LIBRARIES})

 #add_executable(gps_switch_server src/gps_server.cpp)
 #target_link_libraries(gps_switch_server ${catkin_LIBRARIES})

 #add_executable(gps_switch_client src/gps_client.cpp)
 #target_link_libraries(gps_switch_client ${catkin_LIBRARIES})

 #add_executable(fake_lines src/fake_line.cpp)
 #target_link_libraries(fake_lines ${catkin_LIBRARIES})

 #add_executable(laser_points src/laser_points_count.cpp)
 #target_link_libraries(laser_points ${catkin_LIBRARIES})

 #add_executable(gazebo_line src/gazebo_line.cpp)
 #target_link_libraries(gazebo_line ${catkin_LIBRARIES})



## Declare a C++ executable
# add_executable(thorvald_2dnav_node src/thorvald_2dnav_node.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(thorvald_laserscan ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(thorvald_RANSAC ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(thorvald_line_SLAM ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(thorvald_control_modes ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(thorvald_row_transition ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_dependencies(test_row_transition ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_RANSAC ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_control_modes ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(test_line_SLAM ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
add_dependencies(fastSLAM ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#add_dependencies(gazebo_line ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#add_dependencies(gps_switch_server ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#add_dependencies(gps_switch_client ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#add_dependencies(fake_lines ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#add_dependencies(laser_points ${${thorvald_2d_nav}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(thorvald_2dnav_node
#   ${catkin_LIBRARIES}
# )


#SET_SOURCE_FILES_PROPERTIES(thorvald_line_SLAM.cpp PROPERTIES COMPILE_FLAGS -std=c++11)

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS thorvald_2dnav thorvald_2dnav_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_thorvald_2dnav.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

