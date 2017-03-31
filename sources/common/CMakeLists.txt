cmake_minimum_required(VERSION 3.6)

## The EDA/common project
project(eda_common VERSION 0.0.1 LANGUAGES CXX)

## C++ Standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## create a dummy header-only target
add_library(eda_common INTERFACE)
target_sources(eda_common PUBLIC include/eda/version.hpp)
target_include_directories(eda_common PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

## Requirements: Boost headers
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

## Compiler Features required for common/utils
include(CheckCXXCompilerFlag)

check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}" EDA_HAVE_BUILTIN_UNREACHABLE)

check_cxx_source_compiles("
int main() {
    __builtin_expect(1, 0);
    return 0;
}" EDA_HAVE_BUILTIN_EXPECT)

if(EDA_HAVE_BUILTIN_UNREACHABLE)
    target_compile_definitions(eda_common
        PUBLIC EDA_HAVE_BUILTIN_UNREACHABLE 
    )
endif()

if(EDA_HAVE_BUILTIN_EXPECT)
    target_compile_definitions(eda_common
        PUBLIC EDA_HAVE_BUILTIN_EXPECT 
    )
endif()
    