# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/firejox/develop/uml_editor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/firejox/develop/uml_editor/build

# Utility rule file for plugins.

# Include the progress variables for this target.
include plugins/CMakeFiles/plugins.dir/progress.make

plugins: plugins/CMakeFiles/plugins.dir/build.make
	cd /home/firejox/develop/uml_editor/build/plugins && /usr/bin/cmake -E echo 
.PHONY : plugins

# Rule to build all files generated by this target.
plugins/CMakeFiles/plugins.dir/build: plugins

.PHONY : plugins/CMakeFiles/plugins.dir/build

plugins/CMakeFiles/plugins.dir/clean:
	cd /home/firejox/develop/uml_editor/build/plugins && $(CMAKE_COMMAND) -P CMakeFiles/plugins.dir/cmake_clean.cmake
.PHONY : plugins/CMakeFiles/plugins.dir/clean

plugins/CMakeFiles/plugins.dir/depend:
	cd /home/firejox/develop/uml_editor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/firejox/develop/uml_editor /home/firejox/develop/uml_editor/plugins /home/firejox/develop/uml_editor/build /home/firejox/develop/uml_editor/build/plugins /home/firejox/develop/uml_editor/build/plugins/CMakeFiles/plugins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : plugins/CMakeFiles/plugins.dir/depend

