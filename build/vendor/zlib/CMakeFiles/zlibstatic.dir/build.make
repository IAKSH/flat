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
include vendor/zlib/CMakeFiles/zlibstatic.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/zlib/CMakeFiles/zlibstatic.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make

vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj: D:/Programming-Playground/flat2/vendor/zlib/adler32.c
vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj -MF CMakeFiles/zlibstatic.dir/adler32.obj.d -o CMakeFiles/zlibstatic.dir/adler32.obj -c D:/Programming-Playground/flat2/vendor/zlib/adler32.c

vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/adler32.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/adler32.c > CMakeFiles/zlibstatic.dir/adler32.i

vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/adler32.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/adler32.c -o CMakeFiles/zlibstatic.dir/adler32.s

vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj: D:/Programming-Playground/flat2/vendor/zlib/compress.c
vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj -MF CMakeFiles/zlibstatic.dir/compress.obj.d -o CMakeFiles/zlibstatic.dir/compress.obj -c D:/Programming-Playground/flat2/vendor/zlib/compress.c

vendor/zlib/CMakeFiles/zlibstatic.dir/compress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/compress.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/compress.c > CMakeFiles/zlibstatic.dir/compress.i

vendor/zlib/CMakeFiles/zlibstatic.dir/compress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/compress.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/compress.c -o CMakeFiles/zlibstatic.dir/compress.s

vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj: D:/Programming-Playground/flat2/vendor/zlib/crc32.c
vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj -MF CMakeFiles/zlibstatic.dir/crc32.obj.d -o CMakeFiles/zlibstatic.dir/crc32.obj -c D:/Programming-Playground/flat2/vendor/zlib/crc32.c

vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/crc32.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/crc32.c > CMakeFiles/zlibstatic.dir/crc32.i

vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/crc32.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/crc32.c -o CMakeFiles/zlibstatic.dir/crc32.s

vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj: D:/Programming-Playground/flat2/vendor/zlib/deflate.c
vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj -MF CMakeFiles/zlibstatic.dir/deflate.obj.d -o CMakeFiles/zlibstatic.dir/deflate.obj -c D:/Programming-Playground/flat2/vendor/zlib/deflate.c

vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/deflate.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/deflate.c > CMakeFiles/zlibstatic.dir/deflate.i

vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/deflate.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/deflate.c -o CMakeFiles/zlibstatic.dir/deflate.s

vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj: D:/Programming-Playground/flat2/vendor/zlib/gzclose.c
vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj -MF CMakeFiles/zlibstatic.dir/gzclose.obj.d -o CMakeFiles/zlibstatic.dir/gzclose.obj -c D:/Programming-Playground/flat2/vendor/zlib/gzclose.c

vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzclose.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/gzclose.c > CMakeFiles/zlibstatic.dir/gzclose.i

vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzclose.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/gzclose.c -o CMakeFiles/zlibstatic.dir/gzclose.s

vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj: D:/Programming-Playground/flat2/vendor/zlib/gzlib.c
vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj -MF CMakeFiles/zlibstatic.dir/gzlib.obj.d -o CMakeFiles/zlibstatic.dir/gzlib.obj -c D:/Programming-Playground/flat2/vendor/zlib/gzlib.c

vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzlib.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/gzlib.c > CMakeFiles/zlibstatic.dir/gzlib.i

vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzlib.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/gzlib.c -o CMakeFiles/zlibstatic.dir/gzlib.s

vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj: D:/Programming-Playground/flat2/vendor/zlib/gzread.c
vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj -MF CMakeFiles/zlibstatic.dir/gzread.obj.d -o CMakeFiles/zlibstatic.dir/gzread.obj -c D:/Programming-Playground/flat2/vendor/zlib/gzread.c

vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzread.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/gzread.c > CMakeFiles/zlibstatic.dir/gzread.i

vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzread.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/gzread.c -o CMakeFiles/zlibstatic.dir/gzread.s

vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj: D:/Programming-Playground/flat2/vendor/zlib/gzwrite.c
vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj -MF CMakeFiles/zlibstatic.dir/gzwrite.obj.d -o CMakeFiles/zlibstatic.dir/gzwrite.obj -c D:/Programming-Playground/flat2/vendor/zlib/gzwrite.c

vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/gzwrite.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/gzwrite.c > CMakeFiles/zlibstatic.dir/gzwrite.i

vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/gzwrite.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/gzwrite.c -o CMakeFiles/zlibstatic.dir/gzwrite.s

vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj: D:/Programming-Playground/flat2/vendor/zlib/inflate.c
vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj -MF CMakeFiles/zlibstatic.dir/inflate.obj.d -o CMakeFiles/zlibstatic.dir/inflate.obj -c D:/Programming-Playground/flat2/vendor/zlib/inflate.c

vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/inflate.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/inflate.c > CMakeFiles/zlibstatic.dir/inflate.i

vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/inflate.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/inflate.c -o CMakeFiles/zlibstatic.dir/inflate.s

vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj: D:/Programming-Playground/flat2/vendor/zlib/infback.c
vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj -MF CMakeFiles/zlibstatic.dir/infback.obj.d -o CMakeFiles/zlibstatic.dir/infback.obj -c D:/Programming-Playground/flat2/vendor/zlib/infback.c

vendor/zlib/CMakeFiles/zlibstatic.dir/infback.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/infback.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/infback.c > CMakeFiles/zlibstatic.dir/infback.i

vendor/zlib/CMakeFiles/zlibstatic.dir/infback.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/infback.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/infback.c -o CMakeFiles/zlibstatic.dir/infback.s

vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj: D:/Programming-Playground/flat2/vendor/zlib/inftrees.c
vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj -MF CMakeFiles/zlibstatic.dir/inftrees.obj.d -o CMakeFiles/zlibstatic.dir/inftrees.obj -c D:/Programming-Playground/flat2/vendor/zlib/inftrees.c

vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/inftrees.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/inftrees.c > CMakeFiles/zlibstatic.dir/inftrees.i

vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/inftrees.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/inftrees.c -o CMakeFiles/zlibstatic.dir/inftrees.s

vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj: D:/Programming-Playground/flat2/vendor/zlib/inffast.c
vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj -MF CMakeFiles/zlibstatic.dir/inffast.obj.d -o CMakeFiles/zlibstatic.dir/inffast.obj -c D:/Programming-Playground/flat2/vendor/zlib/inffast.c

vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/inffast.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/inffast.c > CMakeFiles/zlibstatic.dir/inffast.i

vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/inffast.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/inffast.c -o CMakeFiles/zlibstatic.dir/inffast.s

vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj: D:/Programming-Playground/flat2/vendor/zlib/trees.c
vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj -MF CMakeFiles/zlibstatic.dir/trees.obj.d -o CMakeFiles/zlibstatic.dir/trees.obj -c D:/Programming-Playground/flat2/vendor/zlib/trees.c

vendor/zlib/CMakeFiles/zlibstatic.dir/trees.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/trees.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/trees.c > CMakeFiles/zlibstatic.dir/trees.i

vendor/zlib/CMakeFiles/zlibstatic.dir/trees.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/trees.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/trees.c -o CMakeFiles/zlibstatic.dir/trees.s

vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj: D:/Programming-Playground/flat2/vendor/zlib/uncompr.c
vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj -MF CMakeFiles/zlibstatic.dir/uncompr.obj.d -o CMakeFiles/zlibstatic.dir/uncompr.obj -c D:/Programming-Playground/flat2/vendor/zlib/uncompr.c

vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/uncompr.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/uncompr.c > CMakeFiles/zlibstatic.dir/uncompr.i

vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/uncompr.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/uncompr.c -o CMakeFiles/zlibstatic.dir/uncompr.s

vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/flags.make
vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/includes_C.rsp
vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj: D:/Programming-Playground/flat2/vendor/zlib/zutil.c
vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj: vendor/zlib/CMakeFiles/zlibstatic.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj -MF CMakeFiles/zlibstatic.dir/zutil.obj.d -o CMakeFiles/zlibstatic.dir/zutil.obj -c D:/Programming-Playground/flat2/vendor/zlib/zutil.c

vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zlibstatic.dir/zutil.i"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Programming-Playground/flat2/vendor/zlib/zutil.c > CMakeFiles/zlibstatic.dir/zutil.i

vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zlibstatic.dir/zutil.s"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Programming-Playground/flat2/vendor/zlib/zutil.c -o CMakeFiles/zlibstatic.dir/zutil.s

# Object files for target zlibstatic
zlibstatic_OBJECTS = \
"CMakeFiles/zlibstatic.dir/adler32.obj" \
"CMakeFiles/zlibstatic.dir/compress.obj" \
"CMakeFiles/zlibstatic.dir/crc32.obj" \
"CMakeFiles/zlibstatic.dir/deflate.obj" \
"CMakeFiles/zlibstatic.dir/gzclose.obj" \
"CMakeFiles/zlibstatic.dir/gzlib.obj" \
"CMakeFiles/zlibstatic.dir/gzread.obj" \
"CMakeFiles/zlibstatic.dir/gzwrite.obj" \
"CMakeFiles/zlibstatic.dir/inflate.obj" \
"CMakeFiles/zlibstatic.dir/infback.obj" \
"CMakeFiles/zlibstatic.dir/inftrees.obj" \
"CMakeFiles/zlibstatic.dir/inffast.obj" \
"CMakeFiles/zlibstatic.dir/trees.obj" \
"CMakeFiles/zlibstatic.dir/uncompr.obj" \
"CMakeFiles/zlibstatic.dir/zutil.obj"

# External object files for target zlibstatic
zlibstatic_EXTERNAL_OBJECTS =

bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/adler32.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/compress.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/crc32.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/deflate.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/gzclose.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/gzlib.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/gzread.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/gzwrite.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/inflate.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/infback.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/inftrees.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/inffast.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/trees.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/uncompr.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/zutil.obj
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/build.make
bin/libzlibstatic.a: vendor/zlib/CMakeFiles/zlibstatic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C static library ../../bin/libzlibstatic.a"
	cd D:/Programming-Playground/flat2/build/vendor/zlib && $(CMAKE_COMMAND) -P CMakeFiles/zlibstatic.dir/cmake_clean_target.cmake
	cd D:/Programming-Playground/flat2/build/vendor/zlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zlibstatic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/zlib/CMakeFiles/zlibstatic.dir/build: bin/libzlibstatic.a
.PHONY : vendor/zlib/CMakeFiles/zlibstatic.dir/build

vendor/zlib/CMakeFiles/zlibstatic.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/zlib && $(CMAKE_COMMAND) -P CMakeFiles/zlibstatic.dir/cmake_clean.cmake
.PHONY : vendor/zlib/CMakeFiles/zlibstatic.dir/clean

vendor/zlib/CMakeFiles/zlibstatic.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/zlib D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/zlib D:/Programming-Playground/flat2/build/vendor/zlib/CMakeFiles/zlibstatic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/zlib/CMakeFiles/zlibstatic.dir/depend
