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
include 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/compiler_depend.make

# Include the progress variables for this target.
include 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/progress.make

# Include the compile flags for this target's objects.
include 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/flags.make

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/flags.make
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/includes_C.rsp
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj: D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/tests/tearing.c
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj -MF CMakeFiles/tearing.dir/tearing.c.obj.d -o CMakeFiles/tearing.dir/tearing.c.obj -c D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/tests/tearing.c

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tearing.dir/tearing.c.i"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/tests/tearing.c > CMakeFiles/tearing.dir/tearing.c.i

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tearing.dir/tearing.c.s"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/tests/tearing.c -o CMakeFiles/tearing.dir/tearing.c.s

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/flags.make
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/includes_C.rsp
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj: D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/deps/glad_gl.c
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj -MF CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj.d -o CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj -c D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/deps/glad_gl.c

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tearing.dir/__/deps/glad_gl.c.i"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/deps/glad_gl.c > CMakeFiles/tearing.dir/__/deps/glad_gl.c.i

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tearing.dir/__/deps/glad_gl.c.s"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/deps/glad_gl.c -o CMakeFiles/tearing.dir/__/deps/glad_gl.c.s

# Object files for target tearing
tearing_OBJECTS = \
"CMakeFiles/tearing.dir/tearing.c.obj" \
"CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj"

# External object files for target tearing
tearing_EXTERNAL_OBJECTS =

3rdparty/glfw-3.3.8/tests/tearing.exe: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/tearing.c.obj
3rdparty/glfw-3.3.8/tests/tearing.exe: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.obj
3rdparty/glfw-3.3.8/tests/tearing.exe: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/build.make
3rdparty/glfw-3.3.8/tests/tearing.exe: 3rdparty/glfw-3.3.8/src/libglfw3.a
3rdparty/glfw-3.3.8/tests/tearing.exe: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/linkLibs.rsp
3rdparty/glfw-3.3.8/tests/tearing.exe: 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tearing.exe"
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/tearing.dir/objects.a
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/tearing.dir/objects.a @CMakeFiles/tearing.dir/objects1
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -mwindows -Wl,--whole-archive CMakeFiles/tearing.dir/objects.a -Wl,--no-whole-archive -o tearing.exe -Wl,--out-implib,libtearing.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/tearing.dir/linkLibs.rsp

# Rule to build all files generated by this target.
3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/build: 3rdparty/glfw-3.3.8/tests/tearing.exe
.PHONY : 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/build

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/clean:
	cd D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests && $(CMAKE_COMMAND) -P CMakeFiles/tearing.dir/cmake_clean.cmake
.PHONY : 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/clean

3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/3rdparty/glfw-3.3.8/tests D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests D:/Programming-Playground/flat2/build/3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rdparty/glfw-3.3.8/tests/CMakeFiles/tearing.dir/depend

