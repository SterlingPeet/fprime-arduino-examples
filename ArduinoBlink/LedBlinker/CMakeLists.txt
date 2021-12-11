####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponent.cpp"
)

# Determine the platform specific source files to append:
string(TOLOWER "${CMAKE_SYSTEM_NAME}" CMAKE_SYSTEM_NAME_LOWER)

# Arduino additions
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponentArduino.cpp")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponentLinux.cpp")
endif()

register_fprime_module()


# Add Arduino dependency
if(${CMAKE_SYSTEM_NAME_LOWER} STREQUAL "arduino")
    get_module_name(${CMAKE_CURRENT_LIST_DIR})
    add_arduino_dependency("${MODULE_NAME}")
endif()
