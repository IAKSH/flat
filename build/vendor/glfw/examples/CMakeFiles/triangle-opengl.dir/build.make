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
include vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/flags.make

vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/flags.make
vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/includes_C.rsp
vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj: D:/Programming-Playground/flat2/vendor/glfw/examples/triangle-opengl.c
vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj -MF CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj.d -o CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/examples/triangle-opengl.c

vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-opengl.dir/triangle-opengl.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/examples/triangle-opengl.c > CMakeFiles/triangle-opengl.dir/triangle-opengl.c.i

vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-opengl.dir/triangle-opengl.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/examples/triangle-opengl.c -o CMakeFiles/triangle-opengl.dir/triangle-opengl.c.s

vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/glfw.rc.obj: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/flags.make
vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/glfw.rc.obj: D:/Programming-Playground/flat2/vendor/glfw/examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/glfw.rc.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) D:/Programming-Playground/flat2/vendor/glfw/examples/glfw.rc CMakeFiles/triangle-opengl.dir/glfw.rc.obj

# Object files for target triangle-opengl
triangle__opengl_OBJECTS = \
"CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj" \
"CMakeFiles/triangle-opengl.dir/glfw.rc.obj"

# External object files for target triangle-opengl
triangle__opengl_EXTERNAL_OBJECTS =

bin/triangle-opengl.exe: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/triangle-opengl.c.obj
bin/triangle-opengl.exe: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/glfw.rc.obj
bin/triangle-opengl.exe: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/build.make
bin/triangle-opengl.exe: bin/libglfw3.a
bin/triangle-opengl.exe: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/linkLibs.rsp
bin/triangle-opengl.exe: vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../../../bin/triangle-opengl.exe"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/triangle-opengl.dir/objects.a
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/triangle-opengl.dir/objects.a @CMakeFiles/triangle-opengl.dir/objects1
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -mwindows -Wl,--whole-archive CMakeFiles/triangle-opengl.dir/objects.a -Wl,--no-whole-archive -o ../../../bin/triangle-opengl.exe -Wl,--out-implib,../../../bin/libtriangle-opengl.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/triangle-opengl.dir/linkLibs.rsp

# Rule to build all files generated by this target.
vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/build: bin/triangle-opengl.exe
.PHONY : vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/build

vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/triangle-opengl.dir/cmake_clean.cmake
.PHONY : vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/clean

vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/glfw/examples D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/glfw/examples D:/Programming-Playground/flat2/build/vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/glfw/examples/CMakeFiles/triangle-opengl.dir/depend

