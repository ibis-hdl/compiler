################################################################################
## IBIS HDL project
##
## file: CMakeLists.txt
################################################################################

cmake_minimum_required(VERSION 3.28)

include("${CMAKE_SOURCE_DIR}/cmake/project-meta-info.cmake")

project(ibis_hdl
    VERSION      "${ibis_version}"
    DESCRIPTION  "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS "    Project:     ${CMAKE_PROJECT_NAME}: ${ibis_description} v${ibis_version} [${ibis_homepage}]")
message(STATUS "    System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "    Compiler:    ${CMAKE_CXX_COMPILER}")
message(STATUS "    Build type:  ${CMAKE_BUILD_TYPE}") # ToDo maybe uninitialized!


## global C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


## CMake modules
list(APPEND
    CMAKE_MODULE_PATH
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_SOURCE_DIR}/cmake/module
)

include(prevent_in_source_builds)   # prelude
include(options_build)
include(options_developer)
include(external_deps)
include(codespell-targets)
include(format-targets)


# This requirement rises by use of CMake's PCH support, otherwise
# linker errors occur. Probably due to boost.org
# [How do I force CMake to include '-pthread' option during compilation?](
#   https://stackoverflow.com/questions/5395309/how-do-i-force-cmake-to-include-pthread-option-during-compilation)
#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


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
add_subdirectory(source/pch)
add_subdirectory(source/common)
add_subdirectory(source/vhdl)
add_subdirectory(source/frontend)
add_subdirectory(l10n)
if (IBIS_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(testsuite/common)
    add_subdirectory(testsuite/misc)
    add_subdirectory(testsuite/testsuite_util)
    # ToDo consider (simpler) approach for testing as using the parser
    #add_subdirectory(testsuite/vhdl/numeric_convert)
    add_subdirectory(testsuite/vhdl/ast)
    add_subdirectory(testsuite/vhdl/grammar)
    add_subdirectory(testsuite/vhdl/parser_rules)
    add_subdirectory(testsuite/vhdl/syntax)
    add_subdirectory(testsuite/frontend)
endif()
add_subdirectory(doc)
add_subdirectory(doc_ng)
