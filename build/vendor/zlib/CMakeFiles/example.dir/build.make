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
include vendor/zlib/CMakeFiles/example.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/zlib/CMakeFiles/example.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/zlib/CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/zlib/CMakeFiles/example.dir/flags.make

vendor/zlib/CMakeFiles/example.dir/test/example.obj: vendor/zlib/CMakeFiles/example.dir/flags.make
vendor/zlib/CMakeFiles/example.dir/test/example.obj: vendor/zlib/CMakeFiles/example.dir/includes_C.rsp
vendor/zlib/CMakeFiles/example.dir/test/example.obj: D:/Programming-Playground/flat2/vendor/zlib/test/example.c
vendor/zlib/CMakeFiles/example.dir/test/example.obj: vendor/zlib/CMakeFiles/example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/zlib/CMakeFiles/example.dir/test/example.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/example.dir/test/example.obj -MF CMakeFiles/example.dir/test/example.obj.d -o CMakeFiles/example.dir/test/example.obj -c D:/Programming-Playground/flat2/vendor/zlib/test/example.c

vendor/zlib/CMakeFiles/example.dir/test/example.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/example.dir/test/example.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/test/example.c > CMakeFiles/example.dir/test/example.i

vendor/zlib/CMakeFiles/example.dir/test/example.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/example.dir/test/example.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/test/example.c -o CMakeFiles/example.dir/test/example.s

# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/test/example.obj"

# External object files for target example
example_EXTERNAL_OBJECTS =

bin/example.exe: vendor/zlib/CMakeFiles/example.dir/test/example.obj
bin/example.exe: vendor/zlib/CMakeFiles/example.dir/build.make
bin/example.exe: bin/libzlib.dll.a
bin/example.exe: vendor/zlib/CMakeFiles/example.dir/linkLibs.rsp
bin/example.exe: vendor/zlib/CMakeFiles/example.dir/objects1
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../bin/example.exe"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/cmake-3.25.0-rc1-windows-x86_64/bin/cmake.exe -E rm -f CMakeFiles/example.dir/objects.a
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/llvm-ar.exe qc CMakeFiles/example.dir/objects.a @CMakeFiles/example.dir/objects1
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe -g -Wl,--whole-archive CMakeFiles/example.dir/objects.a -Wl,--no-whole-archive -o ../../bin/example.exe -Wl,--out-implib,../../bin/libexample.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/example.dir/linkLibs.rsp

# Rule to build all files generated by this target.
vendor/zlib/CMakeFiles/example.dir/build: bin/example.exe
.PHONY : vendor/zlib/CMakeFiles/example.dir/build

vendor/zlib/CMakeFiles/example.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/zlib && $(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : vendor/zlib/CMakeFiles/example.dir/clean

vendor/zlib/CMakeFiles/example.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/zlib D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/zlib D:/Programming-Playground/flat2/build/vendor/zlib/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/zlib/CMakeFiles/example.dir/depend
