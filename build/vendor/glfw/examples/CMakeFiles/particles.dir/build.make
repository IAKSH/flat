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
include vendor/glfw/examples/CMakeFiles/particles.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/glfw/examples/CMakeFiles/particles.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/glfw/examples/CMakeFiles/particles.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/glfw/examples/CMakeFiles/particles.dir/flags.make

vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/flags.make
vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/includes_C.rsp
vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj: D:/Programming-Playground/flat2/vendor/glfw/examples/particles.c
vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj -MF CMakeFiles/particles.dir/particles.c.obj.d -o CMakeFiles/particles.dir/particles.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/examples/particles.c

vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/particles.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/examples/particles.c > CMakeFiles/particles.dir/particles.c.i

vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/particles.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/examples/particles.c -o CMakeFiles/particles.dir/particles.c.s

vendor/glfw/examples/CMakeFiles/particles.dir/glfw.rc.obj: vendor/glfw/examples/CMakeFiles/particles.dir/flags.make
vendor/glfw/examples/CMakeFiles/particles.dir/glfw.rc.obj: D:/Programming-Playground/flat2/vendor/glfw/examples/glfw.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building RC object vendor/glfw/examples/CMakeFiles/particles.dir/glfw.rc.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/windres.exe -O coff $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) D:/Programming-Playground/flat2/vendor/glfw/examples/glfw.rc CMakeFiles/particles.dir/glfw.rc.obj

vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/flags.make
vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/includes_C.rsp
vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj: D:/Programming-Playground/flat2/vendor/glfw/deps/tinycthread.c
vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj -MF CMakeFiles/particles.dir/__/deps/tinycthread.c.obj.d -o CMakeFiles/particles.dir/__/deps/tinycthread.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/deps/tinycthread.c

vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/__/deps/tinycthread.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/deps/tinycthread.c > CMakeFiles/particles.dir/__/deps/tinycthread.c.i

vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/__/deps/tinycthread.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/deps/tinycthread.c -o CMakeFiles/particles.dir/__/deps/tinycthread.c.s

vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/flags.make
vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/includes_C.rsp
vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj: D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c
vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj: vendor/glfw/examples/CMakeFiles/particles.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj -MF CMakeFiles/particles.dir/__/deps/getopt.c.obj.d -o CMakeFiles/particles.dir/__/deps/getopt.c.obj -c D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c

vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/__/deps/getopt.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c > CMakeFiles/particles.dir/__/deps/getopt.c.i

vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/__/deps/getopt.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/glfw/deps/getopt.c -o CMakeFiles/particles.dir/__/deps/getopt.c.s

# Object files for target particles
particles_OBJECTS = \
"CMakeFiles/particles.dir/particles.c.obj" \
"CMakeFiles/particles.dir/glfw.rc.obj" \
"CMakeFiles/particles.dir/__/deps/tinycthread.c.obj" \
"CMakeFiles/particles.dir/__/deps/getopt.c.obj"

# External object files for target particles
particles_EXTERNAL_OBJECTS =

bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/particles.c.obj
bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/glfw.rc.obj
bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.obj
bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/__/deps/getopt.c.obj
bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/build.make
bin/particles.exe: bin/libglfw3.a
bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/linkLibs.rsp
bin/particles.exe: vendor/glfw/examples/CMakeFiles/particles.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../../../bin/particles.exe"
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/particles.dir/objects.a
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/particles.dir/objects.a @CMakeFiles/particles.dir/objects1
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -mwindows -Wl,--whole-archive CMakeFiles/particles.dir/objects.a -Wl,--no-whole-archive -o ../../../bin/particles.exe -Wl,--out-implib,../../../bin/libparticles.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/particles.dir/linkLibs.rsp

# Rule to build all files generated by this target.
vendor/glfw/examples/CMakeFiles/particles.dir/build: bin/particles.exe
.PHONY : vendor/glfw/examples/CMakeFiles/particles.dir/build

vendor/glfw/examples/CMakeFiles/particles.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/particles.dir/cmake_clean.cmake
.PHONY : vendor/glfw/examples/CMakeFiles/particles.dir/clean

vendor/glfw/examples/CMakeFiles/particles.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/glfw/examples D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/glfw/examples D:/Programming-Playground/flat2/build/vendor/glfw/examples/CMakeFiles/particles.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/glfw/examples/CMakeFiles/particles.dir/depend

