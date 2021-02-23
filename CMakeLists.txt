################################################################################
## EDA project
##
## file: CMakeLists.txt
################################################################################

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/cmake/CompilerOptions.cmake")

cmake_minimum_required(VERSION 3.18)

project(eda VERSION 0.0.1 LANGUAGES CXX)
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "EDA version: ${eda_VERSION}")


## global C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(prevent_in_source_builds)
include(options_build)
include(options_developer)


##
# Ninja Build
cmake_host_system_information(
    RESULT localhost_logical_cores
    QUERY NUMBER_OF_LOGICAL_CORES
)

math(EXPR max_cores  "${localhost_logical_cores} - 1")
math(EXPR half_cores "${localhost_logical_cores} / 2")

set_property(GLOBAL PROPERTY JOB_POOLS
    job_pool_max_cores=${max_cores}
    job_pool_med_cores=${half_cores}
    job_pool_one_core=1
)
set_property(GLOBAL PROPERTY CMAKE_JOB_POOLS
    cmake_job_pool=1
)


##
# Boost.Org
# [Cmake doesn't find Boost](https://stackoverflow.com/questions/3808775/cmake-doesnt-find-boost)
#set(Boost_DEBUG 1)   
find_package(Boost 1.73.0 REQUIRED COMPONENTS 
    system 
    filesystem
    locale
    unit_test_framework 
)


##
# Bleeding Edge external Boost dependencies
if(EDA_EXTERNAL_BOOST_SPIRIT_X3)
    include(external_spirit_x3)
endif()
if(EDA_EXTERNAL_BOOST_UTF)
    include(external_boost_utf)
endif()


##
# Support for JSON
# Todo: as of v1.75.0 boost has boost.JSON
include(external_json)


## 
# Common build options: set the output folder where programs will be created.
# [Output Artifacts](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

## 
# Sub projects
add_subdirectory(sources/common)
add_subdirectory(sources/vhdl)
add_subdirectory(sources/ibis)
add_subdirectory(l10n)
if (EDA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(testsuite/common)
    add_subdirectory(testsuite/vhdl/numeric_convert)
    add_subdirectory(testsuite/vhdl/ast)
    add_subdirectory(testsuite/vhdl/librules)
    add_subdirectory(testsuite/vhdl/parser_rules)
    add_subdirectory(testsuite/vhdl/syntax)
    add_subdirectory(testsuite/ibis)
endif()


##
# playground projects
# - not build by default
# - excluded for MSVC
if (NOT MSVC)
add_subdirectory(playground/vhdl93)
add_subdirectory(playground/cxx)
add_subdirectory(playground/boost_test)
add_subdirectory(playground/x3)
endif()


## 
# project doc
add_subdirectory(doc)


##
# Install
include(GNUInstallDirs)


##
# Ignore build dir by backup apps using some 'magic'; e.g. Bacula/Bareos has
# "Exclude Dir Containing" directive for filesets
file(WRITE ${CMAKE_BINARY_DIR}/.no_backup "Don't backup the build dir\n")

