cmake_minimum_required(VERSION 3.24)

cmake_policy(PUSH)
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
        include/mpf/core/Subsystem.h
        src/mpf/core/Subsystem.cpp
        include/mpf/core/SubsystemList.h
        src/mpf/core/SubsystemList.cpp
        include/mpf/util/macros.h
        include/mpf/conf/BuildConfig.h
        include/mpf/conf/LibraryConfig.h
        include/mpf/concepts/Types.h
        include/mpf/types/List.h
        include/mpf/types/FixedPackedString.h
        include/mpf/types/FixedFormattedString.h
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

message(STATUS "Generating MPF library config file")

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/src/mpf/conf/LibraryConfig.cpp.in"
        "${CMAKE_CURRENT_BINARY_DIR}/generated/src/mpf/conf/LibraryConfig.cpp"
        @ONLY
)

add_custom_target(micro-program-framework-generate-build-config
        COMMENT "Generating MPF library build config file"
        SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/mpf/conf/BuildConfig.cpp.in"
        BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/generated/src/mpf/conf/BuildConfig.cpp"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        VERBATIM
        COMMAND ${CMAKE_COMMAND}
        -DCONFIG_INPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/src/mpf/conf/BuildConfig.cpp.in
        -DCONFIG_OUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/generated/src/mpf/conf/BuildConfig.cpp
        -P "${PROJECT_SOURCE_DIR}/cmake/GenerateMPFBuildConfigFile.cmake"
)

target_sources(micro-program-framework PRIVATE
        "${CMAKE_CURRENT_BINARY_DIR}/generated/src/mpf/conf/BuildConfig.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/generated/src/mpf/conf/LibraryConfig.cpp"
)

add_dependencies(micro-program-framework micro-program-framework-generate-build-config)

cmake_policy(POP)
