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
CMAKE_SOURCE_DIR = /home/radekaadek/prg/Hexagon/Multiplayer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/radekaadek/prg/Hexagon/Multiplayer/build

# Include any dependencies generated for this target.
include CMakeFiles/Hexagon.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Hexagon.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Hexagon.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hexagon.dir/flags.make

CMakeFiles/Hexagon.dir/main.cpp.o: CMakeFiles/Hexagon.dir/flags.make
CMakeFiles/Hexagon.dir/main.cpp.o: ../main.cpp
CMakeFiles/Hexagon.dir/main.cpp.o: CMakeFiles/Hexagon.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/radekaadek/prg/Hexagon/Multiplayer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Hexagon.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hexagon.dir/main.cpp.o -MF CMakeFiles/Hexagon.dir/main.cpp.o.d -o CMakeFiles/Hexagon.dir/main.cpp.o -c /home/radekaadek/prg/Hexagon/Multiplayer/main.cpp

CMakeFiles/Hexagon.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hexagon.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/radekaadek/prg/Hexagon/Multiplayer/main.cpp > CMakeFiles/Hexagon.dir/main.cpp.i

CMakeFiles/Hexagon.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hexagon.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/radekaadek/prg/Hexagon/Multiplayer/main.cpp -o CMakeFiles/Hexagon.dir/main.cpp.s

# Object files for target Hexagon
Hexagon_OBJECTS = \
"CMakeFiles/Hexagon.dir/main.cpp.o"

# External object files for target Hexagon
Hexagon_EXTERNAL_OBJECTS =

Hexagon: CMakeFiles/Hexagon.dir/main.cpp.o
Hexagon: CMakeFiles/Hexagon.dir/build.make
Hexagon: _deps/sfml-build/lib/libsfml-system-s-d.a
Hexagon: _deps/sfml-build/lib/libsfml-window-s-d.a
Hexagon: _deps/sfml-build/lib/libsfml-graphics-s-d.a
Hexagon: _deps/sfml-build/lib/libsfml-window-s-d.a
Hexagon: _deps/sfml-build/lib/libsfml-system-s-d.a
Hexagon: /usr/lib/x86_64-linux-gnu/libXrandr.so
Hexagon: /usr/lib/x86_64-linux-gnu/libXext.so
Hexagon: /usr/lib/x86_64-linux-gnu/libXcursor.so
Hexagon: /usr/lib/x86_64-linux-gnu/libXrender.so
Hexagon: /usr/lib/x86_64-linux-gnu/libXfixes.so
Hexagon: /usr/lib/x86_64-linux-gnu/libX11.so
Hexagon: /usr/lib/x86_64-linux-gnu/libGL.so
Hexagon: /usr/lib/x86_64-linux-gnu/libudev.so
Hexagon: /usr/lib/x86_64-linux-gnu/libfreetype.so
Hexagon: CMakeFiles/Hexagon.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/radekaadek/prg/Hexagon/Multiplayer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Hexagon"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Hexagon.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hexagon.dir/build: Hexagon
.PHONY : CMakeFiles/Hexagon.dir/build

CMakeFiles/Hexagon.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Hexagon.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Hexagon.dir/clean

CMakeFiles/Hexagon.dir/depend:
	cd /home/radekaadek/prg/Hexagon/Multiplayer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/radekaadek/prg/Hexagon/Multiplayer /home/radekaadek/prg/Hexagon/Multiplayer /home/radekaadek/prg/Hexagon/Multiplayer/build /home/radekaadek/prg/Hexagon/Multiplayer/build /home/radekaadek/prg/Hexagon/Multiplayer/build/CMakeFiles/Hexagon.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Hexagon.dir/depend

