# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/marko/software/bin/cmake

# The command to remove a file.
RM = /home/marko/software/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marko/CLionProjects/TransformerSolver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marko/CLionProjects/TransformerSolver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TransformerSolver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TransformerSolver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TransformerSolver.dir/flags.make

CMakeFiles/TransformerSolver.dir/main.cpp.o: CMakeFiles/TransformerSolver.dir/flags.make
CMakeFiles/TransformerSolver.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marko/CLionProjects/TransformerSolver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TransformerSolver.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransformerSolver.dir/main.cpp.o -c /home/marko/CLionProjects/TransformerSolver/main.cpp

CMakeFiles/TransformerSolver.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransformerSolver.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marko/CLionProjects/TransformerSolver/main.cpp > CMakeFiles/TransformerSolver.dir/main.cpp.i

CMakeFiles/TransformerSolver.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransformerSolver.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marko/CLionProjects/TransformerSolver/main.cpp -o CMakeFiles/TransformerSolver.dir/main.cpp.s

CMakeFiles/TransformerSolver.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/TransformerSolver.dir/main.cpp.o.requires

CMakeFiles/TransformerSolver.dir/main.cpp.o.provides: CMakeFiles/TransformerSolver.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransformerSolver.dir/build.make CMakeFiles/TransformerSolver.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/TransformerSolver.dir/main.cpp.o.provides

CMakeFiles/TransformerSolver.dir/main.cpp.o.provides.build: CMakeFiles/TransformerSolver.dir/main.cpp.o


CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o: CMakeFiles/TransformerSolver.dir/flags.make
CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o: ../SMTTranslator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marko/CLionProjects/TransformerSolver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o -c /home/marko/CLionProjects/TransformerSolver/SMTTranslator.cpp

CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marko/CLionProjects/TransformerSolver/SMTTranslator.cpp > CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.i

CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marko/CLionProjects/TransformerSolver/SMTTranslator.cpp -o CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.s

CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.requires:

.PHONY : CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.requires

CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.provides: CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransformerSolver.dir/build.make CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.provides.build
.PHONY : CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.provides

CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.provides.build: CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o


CMakeFiles/TransformerSolver.dir/Solver.cpp.o: CMakeFiles/TransformerSolver.dir/flags.make
CMakeFiles/TransformerSolver.dir/Solver.cpp.o: ../Solver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marko/CLionProjects/TransformerSolver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TransformerSolver.dir/Solver.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransformerSolver.dir/Solver.cpp.o -c /home/marko/CLionProjects/TransformerSolver/Solver.cpp

CMakeFiles/TransformerSolver.dir/Solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransformerSolver.dir/Solver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marko/CLionProjects/TransformerSolver/Solver.cpp > CMakeFiles/TransformerSolver.dir/Solver.cpp.i

CMakeFiles/TransformerSolver.dir/Solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransformerSolver.dir/Solver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marko/CLionProjects/TransformerSolver/Solver.cpp -o CMakeFiles/TransformerSolver.dir/Solver.cpp.s

CMakeFiles/TransformerSolver.dir/Solver.cpp.o.requires:

.PHONY : CMakeFiles/TransformerSolver.dir/Solver.cpp.o.requires

CMakeFiles/TransformerSolver.dir/Solver.cpp.o.provides: CMakeFiles/TransformerSolver.dir/Solver.cpp.o.requires
	$(MAKE) -f CMakeFiles/TransformerSolver.dir/build.make CMakeFiles/TransformerSolver.dir/Solver.cpp.o.provides.build
.PHONY : CMakeFiles/TransformerSolver.dir/Solver.cpp.o.provides

CMakeFiles/TransformerSolver.dir/Solver.cpp.o.provides.build: CMakeFiles/TransformerSolver.dir/Solver.cpp.o


# Object files for target TransformerSolver
TransformerSolver_OBJECTS = \
"CMakeFiles/TransformerSolver.dir/main.cpp.o" \
"CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o" \
"CMakeFiles/TransformerSolver.dir/Solver.cpp.o"

# External object files for target TransformerSolver
TransformerSolver_EXTERNAL_OBJECTS =

TransformerSolver: CMakeFiles/TransformerSolver.dir/main.cpp.o
TransformerSolver: CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o
TransformerSolver: CMakeFiles/TransformerSolver.dir/Solver.cpp.o
TransformerSolver: CMakeFiles/TransformerSolver.dir/build.make
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCCommandLine.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCTools.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCOutput.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCCallGraph.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCPasses.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCEncoder.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCAnalysis.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCTransformer.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCSolver.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCILR.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCSMT.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCSolver.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCResource.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCUtil.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMObject.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMObjCARCOpts.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMMCParser.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMMC.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMInstrumentation.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMCodeGen.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMipo.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMVectorize.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMInstCombine.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMScalarOpts.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMTransformUtils.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMipa.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMAnalysis.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMTarget.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMLinker.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMIRReader.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMAsmParser.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMBitReader.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMBitWriter.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMProfileData.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMCore.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMOption.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMSupport.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCILR.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCSMT.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCResource.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLBMCUtil.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMObject.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMObjCARCOpts.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMMCParser.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMMC.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMInstrumentation.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMCodeGen.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMipo.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMVectorize.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMInstCombine.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMScalarOpts.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMTransformUtils.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMipa.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMAnalysis.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMTarget.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMLinker.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMIRReader.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMAsmParser.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMBitReader.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMBitWriter.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMProfileData.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMCore.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMOption.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMSupport.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMObject.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMObjCARCOpts.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMMCParser.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMMC.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMInstrumentation.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMCodeGen.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMipo.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMVectorize.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMInstCombine.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMScalarOpts.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMTransformUtils.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMipa.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMAnalysis.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMTarget.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMLinker.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMIRReader.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMAsmParser.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMBitReader.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMBitWriter.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMProfileData.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMCore.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMOption.a
TransformerSolver: /home/marko/workspace/install/reldeb-gcc/lib/libLLVMSupport.a
TransformerSolver: CMakeFiles/TransformerSolver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marko/CLionProjects/TransformerSolver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable TransformerSolver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TransformerSolver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TransformerSolver.dir/build: TransformerSolver

.PHONY : CMakeFiles/TransformerSolver.dir/build

CMakeFiles/TransformerSolver.dir/requires: CMakeFiles/TransformerSolver.dir/main.cpp.o.requires
CMakeFiles/TransformerSolver.dir/requires: CMakeFiles/TransformerSolver.dir/SMTTranslator.cpp.o.requires
CMakeFiles/TransformerSolver.dir/requires: CMakeFiles/TransformerSolver.dir/Solver.cpp.o.requires

.PHONY : CMakeFiles/TransformerSolver.dir/requires

CMakeFiles/TransformerSolver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TransformerSolver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TransformerSolver.dir/clean

CMakeFiles/TransformerSolver.dir/depend:
	cd /home/marko/CLionProjects/TransformerSolver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marko/CLionProjects/TransformerSolver /home/marko/CLionProjects/TransformerSolver /home/marko/CLionProjects/TransformerSolver/cmake-build-debug /home/marko/CLionProjects/TransformerSolver/cmake-build-debug /home/marko/CLionProjects/TransformerSolver/cmake-build-debug/CMakeFiles/TransformerSolver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TransformerSolver.dir/depend

