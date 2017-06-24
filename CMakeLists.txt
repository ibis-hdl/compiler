cmake_minimum_required(VERSION 3.8)

## The EDA project
project(eda VERSION 0.0.1 LANGUAGES CXX)


## Common build options
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR            ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH         ${CMAKE_BINARY_DIR})


set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


# set the build root dir for sub projects
set(EDA_BINARY_ROOT_DIR ${PROJECT_BINARY_DIR})


## Sub Projects
enable_testing()
add_subdirectory(sources/common)
add_subdirectory(sources/vhdl)

# other playground projects, not build by default
add_subdirectory(playground/vhdl93)
add_subdirectory(playground/boost_test)

