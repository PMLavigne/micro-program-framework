cmake_minimum_required(VERSION 3.24)

# Enable setting VERSION in project() call
cmake_policy(SET CMP0048 NEW)

project(micro-program-framework
        VERSION 0.1.0
        DESCRIPTION "Tiny, basic framework for C++ microcontroller programs"
        LANGUAGES C CXX)

set(MPF_LOG_LEVEL "Info" CACHE STRING "MPF Log Level. Can be one of: None, Error, Warn, Info, Debug, or Trace.")


add_library(micro-program-framework STATIC
        include/mpf/core/Logging.h
        src/mpf/core/Logging.cpp
        include/mpf/util/StringUtil.h
        src/mpf/util/StringUtil.cpp
        include/mpf/core/Program.h
        src/mpf/core/Program.cpp
        include/mpf/core/List.h
        include/mpf/core/Subsystem.h
        src/mpf/core/Subsystem.cpp
        include/mpf/core/SubsystemList.h
        src/mpf/core/SubsystemList.cpp
        include/mpf/util/macros.h
)

target_compile_options(micro-program-framework PRIVATE
        -Wall
        -Wextra
)

target_include_directories(micro-program-framework PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_include_directories(micro-program-framework PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/src"
)

set_target_properties(micro-program-framework PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
)

string(TOLOWER "${MPF_LOG_LEVEL}" MPF_LOG_LEVEL_LOWER)

if ("${MPF_LOG_LEVEL_LOWER}" STREQUAL "error")
    set(MPF_LOG_VALUE 1)
elseif("${MPF_LOG_LEVEL_LOWER}" STREQUAL "warn")
    set(MPF_LOG_VALUE 2)
elseif("${MPF_LOG_LEVEL_LOWER}" STREQUAL "info")
    set(MPF_LOG_VALUE 3)
elseif("${MPF_LOG_LEVEL_LOWER}" STREQUAL "debug")
    set(MPF_LOG_VALUE 4)
elseif("${MPF_LOG_LEVEL_LOWER}" STREQUAL "trace")
    set(MPF_LOG_VALUE 5)
else()
    set(MPF_LOG_VALUE 0)
endif()

target_compile_definitions(micro-program-framework PUBLIC
        MPF_LOG_VALUE=${MPF_LOG_VALUE}
)


