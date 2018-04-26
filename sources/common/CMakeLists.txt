cmake_minimum_required(VERSION 3.8)

## The EDA/common project
project(eda_common VERSION 0.0.1 LANGUAGES CXX)

## C++ Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


## create a dummy header-only target
add_library(${PROJECT_NAME} INTERFACE)
add_library(eda::common ALIAS ${PROJECT_NAME})

target_include_directories(eda_common INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )


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

# MinGW doesn't seems to have C++11 std::quick_exit()
check_cxx_source_compiles("
#include <cstdlib>
int main() {
	std::quick_exit(EXIT_FAILURE);
    return 0;
}" EDA_HAVE_STD_QUICK_EXIT)

configure_file(
  "${PROJECT_SOURCE_DIR}/include/eda/utils/compiler_support.hpp.in"
  "${PROJECT_BINARY_DIR}/include//eda/utils/compiler_support.hpp"
)


## Install targets
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${PROJECT_NAME}
    LIBRARY  DESTINATION ${PROJECT_NAME}
    RUNTIME  DESTINATION ${PROJECT_NAME})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config
    DESTINATION share/cmake/${PROJECT_NAME}Config)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)

