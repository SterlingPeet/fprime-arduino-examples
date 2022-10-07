####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/ArduinoBlinkTopologyAppAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Topology.cpp"
)
# Note: supply non-explicit dependencies here
set(MOD_DEPS
    Fw/Logger
    ATmega/Svc/ATmegaTime
    Os/Baremetal/TaskRunner
)

register_fprime_executable()
#if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
#    set(ARDUINO_DEPENDENCY_TARGET_TOP "${PROJECT_NAME}")
#    add_arduino_dependency("${PROJECT_NAME}_exe")
#    unset(ARDUINO_DEPENDENCY_TARGET_TOP)
#endif()
