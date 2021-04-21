################################################################################
## EDA project
##
## file: CMakeLists.txt
################################################################################

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/cmake/module/CxxFlagOverrides.cmake")

cmake_minimum_required(VERSION 3.18)

project(eda VERSION 0.0.1 LANGUAGES CXX)
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "EDA version: ${eda_VERSION}")


## global C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


list(APPEND
    CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake
    CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/module
)


include(prevent_in_source_builds)
include(options_build)
include(options_developer)


##
# Boost.Org
# [Cmake doesn't find Boost](https://stackoverflow.com/questions/3808775/cmake-doesnt-find-boost)
#set(Boost_DEBUG 1)
find_package(Boost 1.73.0
    REQUIRED COMPONENTS
        system
        locale
        filesystem   # Boost::process depends Boost::filesystem
        unit_test_framework
    OPTIONAL_COMPONENTS
        stacktrace_basic
        stacktrace_backtrace
        stacktrace_addr2line
        stacktrace_noop
        stacktrace_windbg   # only @Windows
)
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


# This requirement rises by use of cmake's PCH support, otherwise
# linker errors occour. Probably due to boost.org
# [How do I force cmake to include “-pthread” option during compilation?](
#   https://stackoverflow.com/questions/5395309/how-do-i-force-cmake-to-include-pthread-option-during-compilation)
#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


##
# External dependencies
# Todo: as of v1.75.0 boost has boost.JSON
include(external_json)
include(external_cli11)
# ToDo: stick at C++17 gsl::string_span, with C++20 use std::span [unused]
#include(external_gsl)


##
# Ensure that all runtime components end up in the bin directory, including
# both .exe's and .dll's. All link-time components, including .so's
# and .a's in Linux and .lib's on Windows, end up in the the lib directory.
# [Output Artifacts](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


##
# Sub projects
add_subdirectory(source/common)
add_subdirectory(source/vhdl)
add_subdirectory(source/ibis)
add_subdirectory(l10n)
if (EDA_BUILD_TESTS)
    add_subdirectory(testsuite/vhdl/util)
    add_subdirectory(testsuite/vhdl/numeric_convert)
    add_subdirectory(testsuite/vhdl/ast)
    add_subdirectory(testsuite/vhdl/librules)
    add_subdirectory(testsuite/vhdl/parser_rules)
    add_subdirectory(testsuite/vhdl/syntax)
    add_subdirectory(testsuite/ibis)
endif()
add_subdirectory(doc)
add_subdirectory(doc_ng)


##
# Install
include(GNUInstallDirs)


##
# Ignore build dir by backup apps using some 'magic'; e.g. Bacula/Bareos has
# "Exclude Dir Containing" directive for filesets
file(WRITE ${CMAKE_BINARY_DIR}/.no_backup "Don't backup the build dir\n")

