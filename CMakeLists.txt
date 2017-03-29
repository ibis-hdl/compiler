cmake_minimum_required(VERSION 3.6)

## The EDA project
project(eda VERSION 0.0.1 LANGUAGES CXX)


## create a dummy header-only target
add_library(eda INTERFACE)
target_include_directories(eda INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

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


## C++ Standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


## Compiler Features
include(CheckCXXCompilerFlag)

check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}" EDA_HAVE_BUILTIN_UNREACHABLE)

if(EDA_HAVE_BUILTIN_UNREACHABLE)
    add_definitions( -DEDA_HAVE_BUILTIN_UNREACHABLE )
endif()

check_cxx_source_compiles("
int main() {
    __builtin_expect(1, 0);
    return 0;
}" EDA_HAVE_BUILTIN_EXPECT)

if(EDA_HAVE_BUILTIN_EXPECT)
    add_definitions( -DEDA_HAVE_BUILTIN_EXPECT )
endif()


## IDE support
# Parsing Errors more efficiently in eclipse
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "(GNU|Clang)")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif()


## Sub Projects
enable_testing()
add_subdirectory(sources/vhdl93)

add_subdirectory(playground/vhdl93)
add_subdirectory(playground/boost_test)

