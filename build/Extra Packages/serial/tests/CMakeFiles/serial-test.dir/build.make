# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vigneshnuc/laptop_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vigneshnuc/laptop_ws/build

# Include any dependencies generated for this target.
include Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/depend.make

# Include the progress variables for this target.
include Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/progress.make

# Include the compile flags for this target's objects.
include Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/flags.make

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/flags.make
Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o: /home/vigneshnuc/laptop_ws/src/Extra\ Packages/serial/tests/unix_serial_tests.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vigneshnuc/laptop_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Extra Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o"
	cd "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial-test.dir/unix_serial_tests.cc.o -c "/home/vigneshnuc/laptop_ws/src/Extra Packages/serial/tests/unix_serial_tests.cc"

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial-test.dir/unix_serial_tests.cc.i"
	cd "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/vigneshnuc/laptop_ws/src/Extra Packages/serial/tests/unix_serial_tests.cc" > CMakeFiles/serial-test.dir/unix_serial_tests.cc.i

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial-test.dir/unix_serial_tests.cc.s"
	cd "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/vigneshnuc/laptop_ws/src/Extra Packages/serial/tests/unix_serial_tests.cc" -o CMakeFiles/serial-test.dir/unix_serial_tests.cc.s

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.requires:

.PHONY : Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.requires

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.provides: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.requires
	$(MAKE) -f "Extra Packages/serial/tests/CMakeFiles/serial-test.dir/build.make" "Extra Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.provides.build"
.PHONY : Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.provides

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.provides.build: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o


# Object files for target serial-test
serial__test_OBJECTS = \
"CMakeFiles/serial-test.dir/unix_serial_tests.cc.o"

# External object files for target serial-test
serial__test_EXTERNAL_OBJECTS =

/home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o
/home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/build.make
/home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test: gtest/gtest/libgtest.so
/home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test: /home/vigneshnuc/laptop_ws/devel/lib/libserial.so
/home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vigneshnuc/laptop_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test"
	cd "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/build: /home/vigneshnuc/laptop_ws/devel/lib/serial/serial-test

.PHONY : Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/build

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/requires: Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/unix_serial_tests.cc.o.requires

.PHONY : Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/requires

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/clean:
	cd "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests" && $(CMAKE_COMMAND) -P CMakeFiles/serial-test.dir/cmake_clean.cmake
.PHONY : Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/clean

Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/depend:
	cd /home/vigneshnuc/laptop_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vigneshnuc/laptop_ws/src "/home/vigneshnuc/laptop_ws/src/Extra Packages/serial/tests" /home/vigneshnuc/laptop_ws/build "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests" "/home/vigneshnuc/laptop_ws/build/Extra Packages/serial/tests/CMakeFiles/serial-test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Extra\ Packages/serial/tests/CMakeFiles/serial-test.dir/depend

