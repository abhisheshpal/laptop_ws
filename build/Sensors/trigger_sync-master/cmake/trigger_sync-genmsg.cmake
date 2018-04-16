# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "trigger_sync: 2 messages, 0 services")

set(MSG_I_FLAGS "-Itrigger_sync:/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg;-Istd_msgs:/opt/ros/kinetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(trigger_sync_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" NAME_WE)
add_custom_target(_trigger_sync_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "trigger_sync" "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" "trigger_sync/Event:std_msgs/Header"
)

get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" NAME_WE)
add_custom_target(_trigger_sync_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "trigger_sync" "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/trigger_sync
)
_generate_msg_cpp(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/trigger_sync
)

### Generating Services

### Generating Module File
_generate_module_cpp(trigger_sync
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/trigger_sync
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(trigger_sync_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(trigger_sync_generate_messages trigger_sync_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_cpp _trigger_sync_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_cpp _trigger_sync_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(trigger_sync_gencpp)
add_dependencies(trigger_sync_gencpp trigger_sync_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS trigger_sync_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/trigger_sync
)
_generate_msg_eus(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/trigger_sync
)

### Generating Services

### Generating Module File
_generate_module_eus(trigger_sync
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/trigger_sync
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(trigger_sync_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(trigger_sync_generate_messages trigger_sync_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_eus _trigger_sync_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_eus _trigger_sync_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(trigger_sync_geneus)
add_dependencies(trigger_sync_geneus trigger_sync_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS trigger_sync_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/trigger_sync
)
_generate_msg_lisp(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/trigger_sync
)

### Generating Services

### Generating Module File
_generate_module_lisp(trigger_sync
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/trigger_sync
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(trigger_sync_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(trigger_sync_generate_messages trigger_sync_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_lisp _trigger_sync_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_lisp _trigger_sync_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(trigger_sync_genlisp)
add_dependencies(trigger_sync_genlisp trigger_sync_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS trigger_sync_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/trigger_sync
)
_generate_msg_nodejs(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/trigger_sync
)

### Generating Services

### Generating Module File
_generate_module_nodejs(trigger_sync
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/trigger_sync
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(trigger_sync_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(trigger_sync_generate_messages trigger_sync_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_nodejs _trigger_sync_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_nodejs _trigger_sync_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(trigger_sync_gennodejs)
add_dependencies(trigger_sync_gennodejs trigger_sync_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS trigger_sync_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg"
  "${MSG_I_FLAGS}"
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg;/opt/ros/kinetic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/trigger_sync
)
_generate_msg_py(trigger_sync
  "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/trigger_sync
)

### Generating Services

### Generating Module File
_generate_module_py(trigger_sync
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/trigger_sync
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(trigger_sync_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(trigger_sync_generate_messages trigger_sync_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/EventStamped.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_py _trigger_sync_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/vignesh/laptop_ws/src/Sensors/trigger_sync-master/msg/Event.msg" NAME_WE)
add_dependencies(trigger_sync_generate_messages_py _trigger_sync_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(trigger_sync_genpy)
add_dependencies(trigger_sync_genpy trigger_sync_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS trigger_sync_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/trigger_sync)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/trigger_sync
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(trigger_sync_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/trigger_sync)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/trigger_sync
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(trigger_sync_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/trigger_sync)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/trigger_sync
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(trigger_sync_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/trigger_sync)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/trigger_sync
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(trigger_sync_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/trigger_sync)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/trigger_sync\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/trigger_sync
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(trigger_sync_generate_messages_py std_msgs_generate_messages_py)
endif()
