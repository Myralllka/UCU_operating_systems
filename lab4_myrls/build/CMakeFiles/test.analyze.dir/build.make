# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/myralllka/Documents/cpp-template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/myralllka/Documents/cpp-template/build

# Utility rule file for test.analyze.

# Include the progress variables for this target.
include CMakeFiles/test.analyze.dir/progress.make

CMakeFiles/test.analyze: ../bin/test
CMakeFiles/test.analyze: target_test.err
	cat target_test.err 1>&2

target_test.err: PVS-Studio/src/main.cpp.plog
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/myralllka/Documents/cpp-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating target_test.err"
	cat /home/myralllka/Documents/cpp-template/build/PVS-Studio/src/main.cpp.plog > target_test.err
	/usr/bin/cmake -E remove -f target_test.err.pvs.raw
	/usr/bin/cmake -E rename target_test.err target_test.err.pvs.raw
	/usr/bin/plog-converter -t errorfile target_test.err.pvs.raw -o target_test.err -a GA:1,2,3+OP:1,2,3+GA:1,2,3+OP:1,2,3+64:1,2,3+CS:1,2,3+MISRA:1,2,3
	/usr/bin/cmake -E remove -f target_test.err.pvs.raw

PVS-Studio/src/main.cpp.plog: ../src/main.cpp
PVS-Studio/src/main.cpp.plog: PVS-Studio.cfg
PVS-Studio/src/main.cpp.plog: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/myralllka/Documents/cpp-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Analyzing CXX file src/main.cpp"
	/usr/bin/cmake -E make_directory /home/myralllka/Documents/cpp-template/build/PVS-Studio/src
	/usr/bin/cmake -E remove_directory /home/myralllka/Documents/cpp-template/build/PVS-Studio/src/main.cpp.plog
	/usr/bin/cmake -D PVS_STUDIO_AS_SCRIPT=TRUE -D "PVS_STUDIO_COMMAND=/usr/bin/pvs-studio-analyzer;analyze;--output-file;/home/myralllka/Documents/cpp-template/build/PVS-Studio/src/main.cpp.plog;--source-file;/home/myralllka/Documents/cpp-template/src/main.cpp;--cfg;/home/myralllka/Documents/cpp-template/build/PVS-Studio.cfg;--platform;linux64;--preprocessor;gcc;--cxx;/usr/bin/c++;--cl-params;-std=c++17;-I/home/myralllka/Documents/cpp-template/inc;-I/usr/include;-I/home/myralllka/Documents/cpp-template/inc;-I/usr/include;-I/home/myralllka/Documents/cpp-template/inc;-I/usr/include;-I/usr/include;-I/usr/include;-DBOOST_PROGRAM_OPTIONS_DYN_LINK;-DBOOST_ALL_NO_LIB;-DPVS_STUDIO;/home/myralllka/Documents/cpp-template/src/main.cpp" -P /home/myralllka/Documents/cpp-template/PVS-Studio.cmake

PVS-Studio.cfg:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/myralllka/Documents/cpp-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating PVS-Studio.cfg"
	/usr/bin/cmake -E echo analysis-mode=31 > /home/myralllka/Documents/cpp-template/build/PVS-Studio.cfg

test.analyze: CMakeFiles/test.analyze
test.analyze: target_test.err
test.analyze: PVS-Studio/src/main.cpp.plog
test.analyze: PVS-Studio.cfg
test.analyze: CMakeFiles/test.analyze.dir/build.make

.PHONY : test.analyze

# Rule to build all files generated by this target.
CMakeFiles/test.analyze.dir/build: test.analyze

.PHONY : CMakeFiles/test.analyze.dir/build

CMakeFiles/test.analyze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.analyze.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.analyze.dir/clean

CMakeFiles/test.analyze.dir/depend:
	cd /home/myralllka/Documents/cpp-template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/myralllka/Documents/cpp-template /home/myralllka/Documents/cpp-template /home/myralllka/Documents/cpp-template/build /home/myralllka/Documents/cpp-template/build /home/myralllka/Documents/cpp-template/build/CMakeFiles/test.analyze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.analyze.dir/depend
