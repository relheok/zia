# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/juniqu_v/cpp_zia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/juniqu_v/cpp_zia

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@echo "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@echo "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/juniqu_v/cpp_zia/CMakeFiles /home/juniqu_v/cpp_zia/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/juniqu_v/cpp_zia/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named clean_zia

# Build rule for target.
clean_zia: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 clean_zia
.PHONY : clean_zia

# fast build rule for target.
clean_zia/fast:
	$(MAKE) -f CMakeFiles/clean_zia.dir/build.make CMakeFiles/clean_zia.dir/build
.PHONY : clean_zia/fast

#=============================================================================
# Target rules for targets named zia

# Build rule for target.
zia: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 zia
.PHONY : zia

# fast build rule for target.
zia/fast:
	$(MAKE) -f CMakeFiles/zia.dir/build.make CMakeFiles/zia.dir/build
.PHONY : zia/fast

#=============================================================================
# Target rules for targets named fclean_zia

# Build rule for target.
fclean_zia: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 fclean_zia
.PHONY : fclean_zia

# fast build rule for target.
fclean_zia/fast:
	$(MAKE) -f CMakeFiles/fclean_zia.dir/build.make CMakeFiles/fclean_zia.dir/build
.PHONY : fclean_zia/fast

#=============================================================================
# Target rules for targets named test_zia

# Build rule for target.
test_zia: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 test_zia
.PHONY : test_zia

# fast build rule for target.
test_zia/fast:
	$(MAKE) -f CMakeFiles/test_zia.dir/build.make CMakeFiles/test_zia.dir/build
.PHONY : test_zia/fast

#=============================================================================
# Target rules for targets named re_zia

# Build rule for target.
re_zia: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 re_zia
.PHONY : re_zia

# fast build rule for target.
re_zia/fast:
	$(MAKE) -f CMakeFiles/re_zia.dir/build.make CMakeFiles/re_zia.dir/build
.PHONY : re_zia/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... clean_zia"
	@echo "... zia"
	@echo "... fclean_zia"
	@echo "... test_zia"
	@echo "... re_zia"
	@echo "... edit_cache"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

