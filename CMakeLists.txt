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

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "EDA version: ${eda_VERSION}")


## global C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(options)


##
# Ninja Build
cmake_host_system_information(
    RESULT localhost_logical_cores
    QUERY NUMBER_OF_LOGICAL_CORES
)

math(EXPR half_cores "${localhost_logical_cores}/2")

set_property(GLOBAL PROPERTY JOB_POOLS
    job_pool_max_cores=${localhost_logical_cores}
    job_pool_med_cores=${half_cores}
    job_pool_one_core=1
)
set_property(GLOBAL PROPERTY CMAKE_JOB_POOLS
    cmake_job_pool=1
)


##
# Globally Boost.Spirit.X3 clone
# EDA project parser depends on newer Spirit.X3 versions as commonly shiped
# by the linux distributions. Create an own up-to-date clone of Boost.Spirit's
# project. This is used by the depending sub projects
include(external_spirit_x3)


##
# Globally Boost.UTF
# - [access to master_test_suite().{argc, argv}](
#    https://svn.boost.org/trac10/ticket/12953)
# - [[Boost.Test] access to boost::unit_test::framework::master_test_suite().{argc, argv} outside from BOOST_TEST](
#    https://groups.google.com/forum/#!topic/boost-developers-archive/wtnY9F2cWNI)
include(external_boost_utf)


## 
# Common build options: set the output folder where programs will be created
set(CMAKE_BINARY_DIR            ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH         ${CMAKE_BINARY_DIR})


## 
# Sub projects
add_subdirectory(sources/common)
add_subdirectory(sources/vhdl)
add_subdirectory(sources/ibis)
if (EDA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(testsuite/common)
    add_subdirectory(testsuite/vhdl/numeric_convert)
    add_subdirectory(testsuite/vhdl/parser_rules)
    add_subdirectory(testsuite/vhdl/syntax)
endif()

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
