# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/ubuntu/workspace/LABS/L5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/workspace/LABS/L5/build

# Include any dependencies generated for this target.
include CMakeFiles/L5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/L5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/L5.dir/flags.make

CMakeFiles/L5.dir/src/main.cpp.o: CMakeFiles/L5.dir/flags.make
CMakeFiles/L5.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/workspace/LABS/L5/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/L5.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/L5.dir/src/main.cpp.o -c /home/ubuntu/workspace/LABS/L5/src/main.cpp

CMakeFiles/L5.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/L5.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/workspace/LABS/L5/src/main.cpp > CMakeFiles/L5.dir/src/main.cpp.i

CMakeFiles/L5.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/L5.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/workspace/LABS/L5/src/main.cpp -o CMakeFiles/L5.dir/src/main.cpp.s

CMakeFiles/L5.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/L5.dir/src/main.cpp.o.requires

CMakeFiles/L5.dir/src/main.cpp.o.provides: CMakeFiles/L5.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/L5.dir/build.make CMakeFiles/L5.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/L5.dir/src/main.cpp.o.provides

CMakeFiles/L5.dir/src/main.cpp.o.provides.build: CMakeFiles/L5.dir/src/main.cpp.o

# Object files for target L5
L5_OBJECTS = \
"CMakeFiles/L5.dir/src/main.cpp.o"

# External object files for target L5
L5_EXTERNAL_OBJECTS =

L5: CMakeFiles/L5.dir/src/main.cpp.o
L5: CMakeFiles/L5.dir/build.make
L5: CMakeFiles/L5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable L5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/L5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/L5.dir/build: L5
.PHONY : CMakeFiles/L5.dir/build

CMakeFiles/L5.dir/requires: CMakeFiles/L5.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/L5.dir/requires

CMakeFiles/L5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/L5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/L5.dir/clean

CMakeFiles/L5.dir/depend:
	cd /home/ubuntu/workspace/LABS/L5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/workspace/LABS/L5 /home/ubuntu/workspace/LABS/L5 /home/ubuntu/workspace/LABS/L5/build /home/ubuntu/workspace/LABS/L5/build /home/ubuntu/workspace/LABS/L5/build/CMakeFiles/L5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/L5.dir/depend

