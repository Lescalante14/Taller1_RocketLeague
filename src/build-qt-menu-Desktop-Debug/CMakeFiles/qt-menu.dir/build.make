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

# Include any dependencies generated for this target.
include CMakeFiles/qt-menu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qt-menu.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qt-menu.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qt-menu.dir/flags.make

CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o: qt-menu_autogen/mocs_compilation.cpp
CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o -MF CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/qt-menu_autogen/mocs_compilation.cpp

CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/qt-menu_autogen/mocs_compilation.cpp > CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.i

CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/qt-menu_autogen/mocs_compilation.cpp -o CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.s

CMakeFiles/qt-menu.dir/main.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/main.cpp.o: /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/main.cpp
CMakeFiles/qt-menu.dir/main.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/qt-menu.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/main.cpp.o -MF CMakeFiles/qt-menu.dir/main.cpp.o.d -o CMakeFiles/qt-menu.dir/main.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/main.cpp

CMakeFiles/qt-menu.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/main.cpp > CMakeFiles/qt-menu.dir/main.cpp.i

CMakeFiles/qt-menu.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/main.cpp -o CMakeFiles/qt-menu.dir/main.cpp.s

CMakeFiles/qt-menu.dir/menu.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/menu.cpp.o: /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/menu.cpp
CMakeFiles/qt-menu.dir/menu.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/qt-menu.dir/menu.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/menu.cpp.o -MF CMakeFiles/qt-menu.dir/menu.cpp.o.d -o CMakeFiles/qt-menu.dir/menu.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/menu.cpp

CMakeFiles/qt-menu.dir/menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/menu.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/menu.cpp > CMakeFiles/qt-menu.dir/menu.cpp.i

CMakeFiles/qt-menu.dir/menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/menu.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/menu.cpp -o CMakeFiles/qt-menu.dir/menu.cpp.s

CMakeFiles/qt-menu.dir/joingamewidget.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/joingamewidget.cpp.o: /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/joingamewidget.cpp
CMakeFiles/qt-menu.dir/joingamewidget.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/qt-menu.dir/joingamewidget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/joingamewidget.cpp.o -MF CMakeFiles/qt-menu.dir/joingamewidget.cpp.o.d -o CMakeFiles/qt-menu.dir/joingamewidget.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/joingamewidget.cpp

CMakeFiles/qt-menu.dir/joingamewidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/joingamewidget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/joingamewidget.cpp > CMakeFiles/qt-menu.dir/joingamewidget.cpp.i

CMakeFiles/qt-menu.dir/joingamewidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/joingamewidget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/joingamewidget.cpp -o CMakeFiles/qt-menu.dir/joingamewidget.cpp.s

CMakeFiles/qt-menu.dir/creategamewidget.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/creategamewidget.cpp.o: /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/creategamewidget.cpp
CMakeFiles/qt-menu.dir/creategamewidget.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/qt-menu.dir/creategamewidget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/creategamewidget.cpp.o -MF CMakeFiles/qt-menu.dir/creategamewidget.cpp.o.d -o CMakeFiles/qt-menu.dir/creategamewidget.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/creategamewidget.cpp

CMakeFiles/qt-menu.dir/creategamewidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/creategamewidget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/creategamewidget.cpp > CMakeFiles/qt-menu.dir/creategamewidget.cpp.i

CMakeFiles/qt-menu.dir/creategamewidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/creategamewidget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/creategamewidget.cpp -o CMakeFiles/qt-menu.dir/creategamewidget.cpp.s

CMakeFiles/qt-menu.dir/configwidget.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/configwidget.cpp.o: /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/configwidget.cpp
CMakeFiles/qt-menu.dir/configwidget.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/qt-menu.dir/configwidget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/configwidget.cpp.o -MF CMakeFiles/qt-menu.dir/configwidget.cpp.o.d -o CMakeFiles/qt-menu.dir/configwidget.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/configwidget.cpp

CMakeFiles/qt-menu.dir/configwidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/configwidget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/configwidget.cpp > CMakeFiles/qt-menu.dir/configwidget.cpp.i

CMakeFiles/qt-menu.dir/configwidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/configwidget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/configwidget.cpp -o CMakeFiles/qt-menu.dir/configwidget.cpp.s

CMakeFiles/qt-menu.dir/aboutwidget.cpp.o: CMakeFiles/qt-menu.dir/flags.make
CMakeFiles/qt-menu.dir/aboutwidget.cpp.o: /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/aboutwidget.cpp
CMakeFiles/qt-menu.dir/aboutwidget.cpp.o: CMakeFiles/qt-menu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/qt-menu.dir/aboutwidget.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qt-menu.dir/aboutwidget.cpp.o -MF CMakeFiles/qt-menu.dir/aboutwidget.cpp.o.d -o CMakeFiles/qt-menu.dir/aboutwidget.cpp.o -c /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/aboutwidget.cpp

CMakeFiles/qt-menu.dir/aboutwidget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/qt-menu.dir/aboutwidget.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/aboutwidget.cpp > CMakeFiles/qt-menu.dir/aboutwidget.cpp.i

CMakeFiles/qt-menu.dir/aboutwidget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/qt-menu.dir/aboutwidget.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu/aboutwidget.cpp -o CMakeFiles/qt-menu.dir/aboutwidget.cpp.s

# Object files for target qt-menu
qt__menu_OBJECTS = \
"CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/qt-menu.dir/main.cpp.o" \
"CMakeFiles/qt-menu.dir/menu.cpp.o" \
"CMakeFiles/qt-menu.dir/joingamewidget.cpp.o" \
"CMakeFiles/qt-menu.dir/creategamewidget.cpp.o" \
"CMakeFiles/qt-menu.dir/configwidget.cpp.o" \
"CMakeFiles/qt-menu.dir/aboutwidget.cpp.o"

# External object files for target qt-menu
qt__menu_EXTERNAL_OBJECTS =

qt-menu: CMakeFiles/qt-menu.dir/qt-menu_autogen/mocs_compilation.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/main.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/menu.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/joingamewidget.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/creategamewidget.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/configwidget.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/aboutwidget.cpp.o
qt-menu: CMakeFiles/qt-menu.dir/build.make
qt-menu: /home/santiago/anaconda3/lib/libQt5Widgets.so.5.9.7
qt-menu: /home/santiago/anaconda3/lib/libQt5Gui.so.5.9.7
qt-menu: /home/santiago/anaconda3/lib/libQt5Core.so.5.9.7
qt-menu: CMakeFiles/qt-menu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable qt-menu"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qt-menu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qt-menu.dir/build: qt-menu
.PHONY : CMakeFiles/qt-menu.dir/build

CMakeFiles/qt-menu.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qt-menu.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qt-menu.dir/clean

CMakeFiles/qt-menu.dir/depend:
	cd /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu /home/santiago/Documents/FIUBA/taller1/tps/rl/src/qt-menu /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug /home/santiago/Documents/FIUBA/taller1/tps/rl/src/build-qt-menu-Desktop-Debug/CMakeFiles/qt-menu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/qt-menu.dir/depend

