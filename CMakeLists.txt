################################################################################
## CMakeLists.txt
################################################################################

################################################################################
## The EDA project
################################################################################

# new behavior of VERSION variable handled by cmake's PROJECT, see
# cmake --help-policy CMP0048
cmake_policy(SET CMP0048 NEW)           
cmake_minimum_required(VERSION 3.11)

project(eda VERSION 0.0.1 LANGUAGES CXX)


## global C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)


##
# Plattform and compiler checks
include(build_config_hpp)


##
# Globally Boost.Spirit.X3 clone
# EDA project parser depends on newer Spirit.X3 versions as commonly shiped
# by the linux distributions. Create an own up-to-date clone of Boost.Spirit's
# project. This is used by the depending sub projects
include(external_spirit_x3)

##
# Boost.UTF 
# see https://svn.boost.org/trac10/ticket/12953
include(external_boost_utf)

## 
# Common build options: set the output folder where programs will be created
set(CMAKE_BINARY_DIR            ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH         ${CMAKE_BINARY_DIR})


## 
# Sub projects
enable_testing()
add_subdirectory(sources/common)
add_subdirectory(sources/vhdl)
add_subdirectory(testsuite/common)
add_subdirectory(testsuite/vhdl/numeric_convert)
add_subdirectory(testsuite/vhdl/parser)
add_subdirectory(testsuite/vhdl/syntax)


##
# playground projects, not build by default
add_subdirectory(playground/vhdl93)
add_subdirectory(playground/cxx)
add_subdirectory(playground/boost_test)
add_subdirectory(playground/x3)





## This is only a reminder, COTIRE doesn't works at last with the VHDL parser
## and his testsuite 
#set_target_properties(${PROJECT_NAME} PROPERTIES
#    COTIRE_PREFIX_HEADER_IGNORE_PATH "${Boost_INCLUDE_DIRS}/boost;${SPIRIT_X3_INCLUDE_DIR}"
#    #COTIRE_PREFIX_HEADER_IGNORE_PATH "${Boost_INCLUDE_DIRS}/boost"
#    #COTIRE_PREFIX_HEADER_INCLUDE_PATH eda::vhdl_parser
#)
#
# FAILED with Boost.PP and others
#cotire(${PROJECT_NAME})
#
# disable PCH date-time check, Boost.Spirit uses __DATE__ and __TIME__ 
# [Can cotire be made to work properly with Boost?](
#  https://stackoverflow.com/questions/44350219/can-cotire-be-made-to-work-properly-with-boost)
#if(_cotireTargetName)
#    target_compile_options(${PROJECT_NAME} PRIVATE
#        -Wno-pch-date-time
#    )
#endif()
