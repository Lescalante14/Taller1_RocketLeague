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
CMAKE_SOURCE_DIR = /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug

# Utility rule file for qt-menu_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/qt-menu_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qt-menu_autogen.dir/progress.make

CMakeFiles/qt-menu_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target qt-menu"
	/usr/bin/cmake -E cmake_autogen /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles/qt-menu_autogen.dir/AutogenInfo.json Debug

qt-menu_autogen: CMakeFiles/qt-menu_autogen
qt-menu_autogen: CMakeFiles/qt-menu_autogen.dir/build.make
.PHONY : qt-menu_autogen

# Rule to build all files generated by this target.
CMakeFiles/qt-menu_autogen.dir/build: qt-menu_autogen
.PHONY : CMakeFiles/qt-menu_autogen.dir/build

CMakeFiles/qt-menu_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt-menu_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt-menu_autogen.dir/clean

CMakeFiles/qt-menu_autogen.dir/depend:
	cd /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles/qt-menu_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qt-menu_autogen.dir/depend
