# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/psiembab/Desktop/Inter/Framework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/psiembab/Desktop/Inter/build

# Include any dependencies generated for this target.
include CMakeFiles/FrameworkRelease.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/FrameworkRelease.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/FrameworkRelease.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FrameworkRelease.dir/flags.make

CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o: CMakeFiles/FrameworkRelease.dir/flags.make
CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o: /home/psiembab/Desktop/Inter/Framework/src/launch.cpp
CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o: CMakeFiles/FrameworkRelease.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/psiembab/Desktop/Inter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o -MF CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o.d -o CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o -c /home/psiembab/Desktop/Inter/Framework/src/launch.cpp

CMakeFiles/FrameworkRelease.dir/src/launch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrameworkRelease.dir/src/launch.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/psiembab/Desktop/Inter/Framework/src/launch.cpp > CMakeFiles/FrameworkRelease.dir/src/launch.cpp.i

CMakeFiles/FrameworkRelease.dir/src/launch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrameworkRelease.dir/src/launch.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/psiembab/Desktop/Inter/Framework/src/launch.cpp -o CMakeFiles/FrameworkRelease.dir/src/launch.cpp.s

# Object files for target FrameworkRelease
FrameworkRelease_OBJECTS = \
"CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o"

# External object files for target FrameworkRelease
FrameworkRelease_EXTERNAL_OBJECTS =

libFrameworkRelease.so.0.0.1: CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o
libFrameworkRelease.so.0.0.1: CMakeFiles/FrameworkRelease.dir/build.make
libFrameworkRelease.so.0.0.1: CMakeFiles/FrameworkRelease.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/psiembab/Desktop/Inter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libFrameworkRelease.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FrameworkRelease.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libFrameworkRelease.so.0.0.1 libFrameworkRelease.so.0.0.1 libFrameworkRelease.so

libFrameworkRelease.so: libFrameworkRelease.so.0.0.1
	@$(CMAKE_COMMAND) -E touch_nocreate libFrameworkRelease.so

# Rule to build all files generated by this target.
CMakeFiles/FrameworkRelease.dir/build: libFrameworkRelease.so
.PHONY : CMakeFiles/FrameworkRelease.dir/build

CMakeFiles/FrameworkRelease.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FrameworkRelease.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FrameworkRelease.dir/clean

CMakeFiles/FrameworkRelease.dir/depend:
	cd /home/psiembab/Desktop/Inter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/psiembab/Desktop/Inter/Framework /home/psiembab/Desktop/Inter/Framework /home/psiembab/Desktop/Inter/build /home/psiembab/Desktop/Inter/build /home/psiembab/Desktop/Inter/build/CMakeFiles/FrameworkRelease.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FrameworkRelease.dir/depend
