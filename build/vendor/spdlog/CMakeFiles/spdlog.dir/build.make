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
include vendor/spdlog/CMakeFiles/spdlog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/spdlog/CMakeFiles/spdlog.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/spdlog/CMakeFiles/spdlog.dir/flags.make

vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/spdlog.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj -MF CMakeFiles/spdlog.dir/src/spdlog.cpp.obj.d -o CMakeFiles/spdlog.dir/src/spdlog.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/spdlog.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/spdlog.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/spdlog.cpp > CMakeFiles/spdlog.dir/src/spdlog.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/spdlog.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/spdlog.cpp -o CMakeFiles/spdlog.dir/src/spdlog.cpp.s

vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/stdout_sinks.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj -MF CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj.d -o CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/stdout_sinks.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/stdout_sinks.cpp > CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/stdout_sinks.cpp -o CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.s

vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/color_sinks.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj -MF CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj.d -o CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/color_sinks.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/color_sinks.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/color_sinks.cpp > CMakeFiles/spdlog.dir/src/color_sinks.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/color_sinks.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/color_sinks.cpp -o CMakeFiles/spdlog.dir/src/color_sinks.cpp.s

vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/file_sinks.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj -MF CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj.d -o CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/file_sinks.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/file_sinks.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/file_sinks.cpp > CMakeFiles/spdlog.dir/src/file_sinks.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/file_sinks.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/file_sinks.cpp -o CMakeFiles/spdlog.dir/src/file_sinks.cpp.s

vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/async.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj -MF CMakeFiles/spdlog.dir/src/async.cpp.obj.d -o CMakeFiles/spdlog.dir/src/async.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/async.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/async.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/async.cpp > CMakeFiles/spdlog.dir/src/async.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/async.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/async.cpp -o CMakeFiles/spdlog.dir/src/async.cpp.s

vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/cfg.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj -MF CMakeFiles/spdlog.dir/src/cfg.cpp.obj.d -o CMakeFiles/spdlog.dir/src/cfg.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/cfg.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/cfg.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/cfg.cpp > CMakeFiles/spdlog.dir/src/cfg.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/cfg.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/cfg.cpp -o CMakeFiles/spdlog.dir/src/cfg.cpp.s

vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/includes_CXX.rsp
vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj: D:/Programming-Playground/flat2/vendor/spdlog/src/bundled_fmtlib_format.cpp
vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj: vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj -MF CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj.d -o CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj -c D:/Programming-Playground/flat2/vendor/spdlog/src/bundled_fmtlib_format.cpp

vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.i"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:/Programming-Playground/flat2/vendor/spdlog/src/bundled_fmtlib_format.cpp > CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.i

vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.s"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && D:/Programming-Tools/llvm-mingw-20230320-ucrt-x86_64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:/Programming-Playground/flat2/vendor/spdlog/src/bundled_fmtlib_format.cpp -o CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.s

# Object files for target spdlog
spdlog_OBJECTS = \
"CMakeFiles/spdlog.dir/src/spdlog.cpp.obj" \
"CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj" \
"CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj" \
"CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj" \
"CMakeFiles/spdlog.dir/src/async.cpp.obj" \
"CMakeFiles/spdlog.dir/src/cfg.cpp.obj" \
"CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj"

# External object files for target spdlog
spdlog_EXTERNAL_OBJECTS =

bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.obj
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/build.make
bin/libspdlogd.a: vendor/spdlog/CMakeFiles/spdlog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Programming-Playground/flat2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library ../../bin/libspdlogd.a"
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/spdlog.dir/cmake_clean_target.cmake
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spdlog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/spdlog/CMakeFiles/spdlog.dir/build: bin/libspdlogd.a
.PHONY : vendor/spdlog/CMakeFiles/spdlog.dir/build

vendor/spdlog/CMakeFiles/spdlog.dir/clean:
	cd D:/Programming-Playground/flat2/build/vendor/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/spdlog.dir/cmake_clean.cmake
.PHONY : vendor/spdlog/CMakeFiles/spdlog.dir/clean

vendor/spdlog/CMakeFiles/spdlog.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Programming-Playground/flat2 D:/Programming-Playground/flat2/vendor/spdlog D:/Programming-Playground/flat2/build D:/Programming-Playground/flat2/build/vendor/spdlog D:/Programming-Playground/flat2/build/vendor/spdlog/CMakeFiles/spdlog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/spdlog/CMakeFiles/spdlog.dir/depend

