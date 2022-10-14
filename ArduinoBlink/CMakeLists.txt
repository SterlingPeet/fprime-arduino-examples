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

message(STATUS ">>>>>${CMAKE_SYSTEM_PROCESSOR}")

include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")


# Use file hashes instead of full file paths in the compiled binary.  This can be
# converted back to a filename with the `fprime-util hashes` tool.
add_definitions(-DFW_ASSERT_LEVEL=2)


# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

# Disable targets not supported on Arduino
#set_target_properties(Svc_LinuxTime  PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/ATmegaOs")
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/Drv/ATmegaGpioDriver")
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/Drv/ATmegaSerialDriver")
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/Svc/ATmegaTime")
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/Svc/AssertReset/")
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/Drv/HardwareRateDriver/")
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../fprime-arduino/ATmega/Svc/EePrmDb/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/LedBlinker/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Main.cpp")
set(MOD_DEPS ArduinoBlink/Top)

register_fprime_deployment()

# Add Topology subdirectory
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

