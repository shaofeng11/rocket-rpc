# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shaofeng/workspace2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shaofeng/workspace2

# Include any dependencies generated for this target.
include CMakeFiles/test_eventloop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_eventloop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_eventloop.dir/flags.make

CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.o: CMakeFiles/test_eventloop.dir/flags.make
CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.o: tests/test_eventloop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shaofeng/workspace2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.o -c /home/shaofeng/workspace2/tests/test_eventloop.cc

CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shaofeng/workspace2/tests/test_eventloop.cc > CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.i

CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shaofeng/workspace2/tests/test_eventloop.cc -o CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.s

# Object files for target test_eventloop
test_eventloop_OBJECTS = \
"CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.o"

# External object files for target test_eventloop
test_eventloop_EXTERNAL_OBJECTS =

bin/test_eventloop: CMakeFiles/test_eventloop.dir/tests/test_eventloop.cc.o
bin/test_eventloop: CMakeFiles/test_eventloop.dir/build.make
bin/test_eventloop: lib/librocket.so
bin/test_eventloop: lib/libtinyxml.so
bin/test_eventloop: CMakeFiles/test_eventloop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shaofeng/workspace2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/test_eventloop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_eventloop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_eventloop.dir/build: bin/test_eventloop

.PHONY : CMakeFiles/test_eventloop.dir/build

CMakeFiles/test_eventloop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_eventloop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_eventloop.dir/clean

CMakeFiles/test_eventloop.dir/depend:
	cd /home/shaofeng/workspace2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shaofeng/workspace2 /home/shaofeng/workspace2 /home/shaofeng/workspace2 /home/shaofeng/workspace2 /home/shaofeng/workspace2/CMakeFiles/test_eventloop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_eventloop.dir/depend

