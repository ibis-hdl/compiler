cmake_minimum_required(VERSION 3.6)

project(ibis VERSION 0.0.1 LANGUAGES CXX)

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


#set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
#ExternalProject_Add(googletest
#    GIT_REPOSITORY https://github.com/google/googletest
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#)

#include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
#link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

#add_executable(FirstTest main.cpp)
#add_dependencies(FirstTest googletest)
#target_link_libraries(FirstTest gtest gtest_main pthread)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(external-gsl)
include(external-spirit-x3)


## IDE support
# Parsing Errors more efficiently in eclipse
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "(GNU|Clang)")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif()


include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${GSL_INCLUDE_DIR})
include_directories(${SPIRIT_X3_INCLUDE_DIR})


add_executable(hello ${PROJECT_SOURCE_DIR}/src/test.cpp)
add_dependencies(hello gsl)
add_dependencies(hello boost-spirit-x3)

set_target_properties(hello PROPERTIES CXX_STANDARD 14)
set_target_properties(hello PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(hello PROPERTIES DEBUG_POSTFIX "_d")
target_compile_options(hello PRIVATE -Wall -Wextra)


#target_compile_options(foo PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
#target_compile_options(foo PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

# https://ecrafter.wordpress.com/2012/05/01/cmake-tutorial-part-4/
