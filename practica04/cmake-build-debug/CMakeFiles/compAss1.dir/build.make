# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/pedro/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.3727.114/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/pedro/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.3727.114/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pedro/semestre1_2017/compiladores/practicas/compAss1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compAss1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compAss1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compAss1.dir/flags.make

CMakeFiles/compAss1.dir/main.c.o: CMakeFiles/compAss1.dir/flags.make
CMakeFiles/compAss1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/compAss1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/compAss1.dir/main.c.o   -c /home/pedro/semestre1_2017/compiladores/practicas/compAss1/main.c

CMakeFiles/compAss1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compAss1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/pedro/semestre1_2017/compiladores/practicas/compAss1/main.c > CMakeFiles/compAss1.dir/main.c.i

CMakeFiles/compAss1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compAss1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/pedro/semestre1_2017/compiladores/practicas/compAss1/main.c -o CMakeFiles/compAss1.dir/main.c.s

CMakeFiles/compAss1.dir/main.c.o.requires:

.PHONY : CMakeFiles/compAss1.dir/main.c.o.requires

CMakeFiles/compAss1.dir/main.c.o.provides: CMakeFiles/compAss1.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/compAss1.dir/build.make CMakeFiles/compAss1.dir/main.c.o.provides.build
.PHONY : CMakeFiles/compAss1.dir/main.c.o.provides

CMakeFiles/compAss1.dir/main.c.o.provides.build: CMakeFiles/compAss1.dir/main.c.o


# Object files for target compAss1
compAss1_OBJECTS = \
"CMakeFiles/compAss1.dir/main.c.o"

# External object files for target compAss1
compAss1_EXTERNAL_OBJECTS =

compAss1: CMakeFiles/compAss1.dir/main.c.o
compAss1: CMakeFiles/compAss1.dir/build.make
compAss1: CMakeFiles/compAss1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable compAss1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compAss1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compAss1.dir/build: compAss1

.PHONY : CMakeFiles/compAss1.dir/build

CMakeFiles/compAss1.dir/requires: CMakeFiles/compAss1.dir/main.c.o.requires

.PHONY : CMakeFiles/compAss1.dir/requires

CMakeFiles/compAss1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compAss1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compAss1.dir/clean

CMakeFiles/compAss1.dir/depend:
	cd /home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pedro/semestre1_2017/compiladores/practicas/compAss1 /home/pedro/semestre1_2017/compiladores/practicas/compAss1 /home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug /home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug /home/pedro/semestre1_2017/compiladores/practicas/compAss1/cmake-build-debug/CMakeFiles/compAss1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compAss1.dir/depend
