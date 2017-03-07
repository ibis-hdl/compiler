## The EDA project
cmake_minimum_required(VERSION 3.6)

project(eda VERSION 0.0.1 LANGUAGES CXX)

# Catch in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "\
In-source builds not allowed. Please make a new directory (called a build \
directory) and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    message(NOTICE "Build type unspecified, set to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Catch unsupported build-type strings
string(TOLOWER "${CMAKE_BUILD_TYPE}" project_build_type)
if(     NOT project_build_type STREQUAL "debug"
    AND NOT project_build_type STREQUAL "release"
    AND NOT project_build_type STREQUAL "relwithdebinfo")
    message(FATAL_ERROR "\
Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, \
Release, RelWithDebInfo (case-insensitive).")
endif()


# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR            ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH         ${CMAKE_BINARY_DIR})


## External, 3rd party projects
include(ExternalProject)

## Requirements
find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(external-gsl)
#include(external-spirit-x3)


## IDE support
# Parsing Errors more efficiently in eclipse
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "(GNU|Clang)")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif()


add_subdirectory(sources)

add_subdirectory(playground)


