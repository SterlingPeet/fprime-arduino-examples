####
# Arduino Blink Deployment:
#
# This sets up the Arduino Blink deployment using CMake
# for use with F prime.
#
# This file has several sections.
#
# 1. Header Section: define basic properties of the build
# 2. F´ core: includes all F´ core components, and build-system properties
# 3. Local subdirectories: contains all deployment specific directory additions
####
project(ArduinoBlink C CXX ASM)
cmake_minimum_required(VERSION 3.16)
set(BAREMETAL_SCHEDULER CACHE BOOL ON "Uses the baremetal scheduler")

include("${CMAKE_CURRENT_LIST_DIR}/../fprime/cmake/FPrime.cmake")

# Use file hashes instead of full file paths in the compiled binary.  This can be
# converted back to a filename with the `fprime-util hashes` tool.
add_definitions(-DFW_ASSERT_LEVEL=2)

# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/LedBlinker/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Main.cpp" "${CMAKE_CURRENT_LIST_DIR}/setup2main.c")
set(MOD_DEPS ArduinoBlink/Top Os/Baremetal/TaskRunner)
register_fprime_deployment()
finalize_arduino_executable("${PROJECT_NAME}")
