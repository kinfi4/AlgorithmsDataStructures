# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kini4/c++/BiTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kini4/c++/BiTree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/BiTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/BiTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BiTree.dir/flags.make

CMakeFiles/BiTree.dir/main.cpp.o: CMakeFiles/BiTree.dir/flags.make
CMakeFiles/BiTree.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kini4/c++/BiTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BiTree.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BiTree.dir/main.cpp.o -c /home/kini4/c++/BiTree/main.cpp

CMakeFiles/BiTree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BiTree.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kini4/c++/BiTree/main.cpp > CMakeFiles/BiTree.dir/main.cpp.i

CMakeFiles/BiTree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BiTree.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kini4/c++/BiTree/main.cpp -o CMakeFiles/BiTree.dir/main.cpp.s

# Object files for target BiTree
BiTree_OBJECTS = \
"CMakeFiles/BiTree.dir/main.cpp.o"

# External object files for target BiTree
BiTree_EXTERNAL_OBJECTS =

BiTree: CMakeFiles/BiTree.dir/main.cpp.o
BiTree: CMakeFiles/BiTree.dir/build.make
BiTree: CMakeFiles/BiTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kini4/c++/BiTree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BiTree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BiTree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BiTree.dir/build: BiTree

.PHONY : CMakeFiles/BiTree.dir/build

CMakeFiles/BiTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BiTree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BiTree.dir/clean

CMakeFiles/BiTree.dir/depend:
	cd /home/kini4/c++/BiTree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kini4/c++/BiTree /home/kini4/c++/BiTree /home/kini4/c++/BiTree/cmake-build-debug /home/kini4/c++/BiTree/cmake-build-debug /home/kini4/c++/BiTree/cmake-build-debug/CMakeFiles/BiTree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BiTree.dir/depend

