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
include vendor/openal-soft/CMakeFiles/alrecord.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/openal-soft/CMakeFiles/alrecord.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/openal-soft/CMakeFiles/alrecord.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/openal-soft/CMakeFiles/alrecord.dir/flags.make

vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj: vendor/openal-soft/CMakeFiles/alrecord.dir/flags.make
vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj: vendor/openal-soft/CMakeFiles/alrecord.dir/includes_C.rsp
vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj: D:/Programming-Playground/flat2/vendor/openal-soft/examples/alrecord.c
vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj: vendor/openal-soft/CMakeFiles/alrecord.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj"
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj -MF CMakeFiles/alrecord.dir/examples/alrecord.c.obj.d -o CMakeFiles/alrecord.dir/examples/alrecord.c.obj -c D:/Programming-Playground/flat2/vendor/openal-soft/examples/alrecord.c

vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/alrecord.dir/examples/alrecord.c.i"
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/openal-soft/examples/alrecord.c > CMakeFiles/alrecord.dir/examples/alrecord.c.i

vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/alrecord.dir/examples/alrecord.c.s"
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/openal-soft/examples/alrecord.c -o CMakeFiles/alrecord.dir/examples/alrecord.c.s

# Object files for target alrecord
alrecord_OBJECTS = \
"CMakeFiles/alrecord.dir/examples/alrecord.c.obj"

# External object files for target alrecord
alrecord_EXTERNAL_OBJECTS =

bin/alrecord.exe: vendor/openal-soft/CMakeFiles/alrecord.dir/examples/alrecord.c.obj
bin/alrecord.exe: vendor/openal-soft/CMakeFiles/alrecord.dir/build.make
bin/alrecord.exe: bin/libex-common.a
bin/alrecord.exe: bin/libOpenAL32.dll.a
bin/alrecord.exe: vendor/openal-soft/CMakeFiles/alrecord.dir/linkLibs.rsp
bin/alrecord.exe: vendor/openal-soft/CMakeFiles/alrecord.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/alrecord.exe"
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/alrecord.dir/objects.a
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/alrecord.dir/objects.a @CMakeFiles/alrecord.dir/objects1
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -Wl,--whole-archive CMakeFiles/alrecord.dir/objects.a -Wl,--no-whole-archive -o ../../bin/alrecord.exe -Wl,--out-implib,../../bin/libalrecord.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/alrecord.dir/linkLibs.rsp

# Rule to build all files generated by this target.
vendor/openal-soft/CMakeFiles/alrecord.dir/build: bin/alrecord.exe
.PHONY : vendor/openal-soft/CMakeFiles/alrecord.dir/build

vendor/openal-soft/CMakeFiles/alrecord.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/openal-soft && $(CMAKE_COMMAND) -P CMakeFiles/alrecord.dir/cmake_clean.cmake
.PHONY : vendor/openal-soft/CMakeFiles/alrecord.dir/clean

vendor/openal-soft/CMakeFiles/alrecord.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/openal-soft D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/openal-soft D:/Programming-Playground/flat2/build/vendor/openal-soft/CMakeFiles/alrecord.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/openal-soft/CMakeFiles/alrecord.dir/depend
