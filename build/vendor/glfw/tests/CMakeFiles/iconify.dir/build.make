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
include vendor/glfw/tests/CMakeFiles/iconify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/glfw/tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/glfw/tests/CMakeFiles/iconify.dir/flags.make

vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj: vendor/glfw/tests/CMakeFiles/iconify.dir/flags.make
vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj: vendor/glfw/tests/CMakeFiles/iconify.dir/includes_C.rsp
vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj: D:/Programming-Playground/flat2/vendor/glfw/tests/iconify.c
vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj: vendor/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj -MF CMakeFiles/iconify.dir/iconify.c.obj.d -o CMakeFiles/iconify.dir/iconify.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/tests/iconify.c

vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/tests/iconify.c > CMakeFiles/iconify.dir/iconify.c.i

vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/tests/iconify.c -o CMakeFiles/iconify.dir/iconify.c.s

vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: vendor/glfw/tests/CMakeFiles/iconify.dir/flags.make
vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: vendor/glfw/tests/CMakeFiles/iconify.dir/includes_C.rsp
vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c
vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: vendor/glfw/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj -MF CMakeFiles/iconify.dir/__/deps/getopt.c.obj.d -o CMakeFiles/iconify.dir/__/deps/getopt.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c

vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c > CMakeFiles/iconify.dir/__/deps/getopt.c.i

vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c -o CMakeFiles/iconify.dir/__/deps/getopt.c.s

# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.obj" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.obj"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

bin/iconify.exe: vendor/glfw/tests/CMakeFiles/iconify.dir/iconify.c.obj
bin/iconify.exe: vendor/glfw/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj
bin/iconify.exe: vendor/glfw/tests/CMakeFiles/iconify.dir/build.make
bin/iconify.exe: bin/libglfw3.a
bin/iconify.exe: vendor/glfw/tests/CMakeFiles/iconify.dir/linkLibs.rsp
bin/iconify.exe: vendor/glfw/tests/CMakeFiles/iconify.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ../../../bin/iconify.exe"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/iconify.dir/objects.a
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/iconify.dir/objects.a @CMakeFiles/iconify.dir/objects1
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -Wl,--whole-archive CMakeFiles/iconify.dir/objects.a -Wl,--no-whole-archive -o ../../../bin/iconify.exe -Wl,--out-implib,../../../bin/libiconify.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/iconify.dir/linkLibs.rsp

# Rule to build all files generated by this target.
vendor/glfw/tests/CMakeFiles/iconify.dir/build: bin/iconify.exe
.PHONY : vendor/glfw/tests/CMakeFiles/iconify.dir/build

vendor/glfw/tests/CMakeFiles/iconify.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/iconify.dir/cmake_clean.cmake
.PHONY : vendor/glfw/tests/CMakeFiles/iconify.dir/clean

vendor/glfw/tests/CMakeFiles/iconify.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/glfw/tests D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/glfw/tests D:/Programming-Playground/flat2/build/vendor/glfw/tests/CMakeFiles/iconify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/glfw/tests/CMakeFiles/iconify.dir/depend
