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
CMAKE_SOURCE_DIR = /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build

# Include any dependencies generated for this target.
include semana_2/threads/CMakeFiles/multithread.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include semana_2/threads/CMakeFiles/multithread.dir/compiler_depend.make

# Include the progress variables for this target.
include semana_2/threads/CMakeFiles/multithread.dir/progress.make

# Include the compile flags for this target's objects.
include semana_2/threads/CMakeFiles/multithread.dir/flags.make

semana_2/threads/CMakeFiles/multithread.dir/multithread.c.o: semana_2/threads/CMakeFiles/multithread.dir/flags.make
semana_2/threads/CMakeFiles/multithread.dir/multithread.c.o: ../semana_2/threads/multithread.c
semana_2/threads/CMakeFiles/multithread.dir/multithread.c.o: semana_2/threads/CMakeFiles/multithread.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object semana_2/threads/CMakeFiles/multithread.dir/multithread.c.o"
	cd /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT semana_2/threads/CMakeFiles/multithread.dir/multithread.c.o -MF CMakeFiles/multithread.dir/multithread.c.o.d -o CMakeFiles/multithread.dir/multithread.c.o -c /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/semana_2/threads/multithread.c

semana_2/threads/CMakeFiles/multithread.dir/multithread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/multithread.dir/multithread.c.i"
	cd /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/semana_2/threads/multithread.c > CMakeFiles/multithread.dir/multithread.c.i

semana_2/threads/CMakeFiles/multithread.dir/multithread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/multithread.dir/multithread.c.s"
	cd /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/semana_2/threads/multithread.c -o CMakeFiles/multithread.dir/multithread.c.s

# Object files for target multithread
multithread_OBJECTS = \
"CMakeFiles/multithread.dir/multithread.c.o"

# External object files for target multithread
multithread_EXTERNAL_OBJECTS =

semana_2/threads/multithread: semana_2/threads/CMakeFiles/multithread.dir/multithread.c.o
semana_2/threads/multithread: semana_2/threads/CMakeFiles/multithread.dir/build.make
semana_2/threads/multithread: semana_2/threads/CMakeFiles/multithread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable multithread"
	cd /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multithread.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
semana_2/threads/CMakeFiles/multithread.dir/build: semana_2/threads/multithread
.PHONY : semana_2/threads/CMakeFiles/multithread.dir/build

semana_2/threads/CMakeFiles/multithread.dir/clean:
	cd /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads && $(CMAKE_COMMAND) -P CMakeFiles/multithread.dir/cmake_clean.cmake
.PHONY : semana_2/threads/CMakeFiles/multithread.dir/clean

semana_2/threads/CMakeFiles/multithread.dir/depend:
	cd /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/semana_2/threads /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads /home/davi/MONITORIA_SISTEMAS_DISTRIBUIDOS/build/semana_2/threads/CMakeFiles/multithread.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : semana_2/threads/CMakeFiles/multithread.dir/depend

