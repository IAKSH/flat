# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe

# The command to remove a file.
RM = D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/Programming-Playground/flat2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/Programming-Playground/flat2/build

# Include any dependencies generated for this target.
include vendor/glfw/tests/CMakeFiles/events.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/glfw/tests/CMakeFiles/events.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/glfw/tests/CMakeFiles/events.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/glfw/tests/CMakeFiles/events.dir/flags.make

vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj: vendor/glfw/tests/CMakeFiles/events.dir/flags.make
vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj: vendor/glfw/tests/CMakeFiles/events.dir/includes_C.rsp
vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj: D:/Programming-Playground/flat2/vendor/glfw/tests/events.c
vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj: vendor/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj -MF CMakeFiles/events.dir/events.c.obj.d -o CMakeFiles/events.dir/events.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/tests/events.c

vendor/glfw/tests/CMakeFiles/events.dir/events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/events.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/tests/events.c > CMakeFiles/events.dir/events.c.i

vendor/glfw/tests/CMakeFiles/events.dir/events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/events.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/tests/events.c -o CMakeFiles/events.dir/events.c.s

vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj: vendor/glfw/tests/CMakeFiles/events.dir/flags.make
vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj: vendor/glfw/tests/CMakeFiles/events.dir/includes_C.rsp
vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj: D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c
vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj: vendor/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj -MF CMakeFiles/events.dir/__/deps/getopt.c.obj.d -o CMakeFiles/events.dir/__/deps/getopt.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c

vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/getopt.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c > CMakeFiles/events.dir/__/deps/getopt.c.i

vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/getopt.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c -o CMakeFiles/events.dir/__/deps/getopt.c.s

# Object files for target events
events_OBJECTS = \
"CMakeFiles/events.dir/events.c.obj" \
"CMakeFiles/events.dir/__/deps/getopt.c.obj"

# External object files for target events
events_EXTERNAL_OBJECTS =

bin/events.exe: vendor/glfw/tests/CMakeFiles/events.dir/events.c.obj
bin/events.exe: vendor/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.obj
bin/events.exe: vendor/glfw/tests/CMakeFiles/events.dir/build.make
bin/events.exe: bin/libglfw3.a
bin/events.exe: vendor/glfw/tests/CMakeFiles/events.dir/linkLibs.rsp
bin/events.exe: vendor/glfw/tests/CMakeFiles/events.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../../../bin/events.exe"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/events.dir/objects.a
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/events.dir/objects.a @CMakeFiles/events.dir/objects1
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -Wl,--whole-archive CMakeFiles/events.dir/objects.a -Wl,--no-whole-archive -o ../../../bin/events.exe -Wl,--out-implib,../../../bin/libevents.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/events.dir/linkLibs.rsp

# Rule to build all files generated by this target.
vendor/glfw/tests/CMakeFiles/events.dir/build: bin/events.exe
.PHONY : vendor/glfw/tests/CMakeFiles/events.dir/build

vendor/glfw/tests/CMakeFiles/events.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/events.dir/cmake_clean.cmake
.PHONY : vendor/glfw/tests/CMakeFiles/events.dir/clean

vendor/glfw/tests/CMakeFiles/events.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/glfw/tests D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/glfw/tests D:/Programming-Playground/flat2/build/vendor/glfw/tests/CMakeFiles/events.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/glfw/tests/CMakeFiles/events.dir/depend

