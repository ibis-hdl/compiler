################################################################################
## EDA project
##
## file: CMakeLists.txt
################################################################################

set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/cmake/module/CompilerOptions.cmake")

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

set(DEVELOPER_RUN_CLANG_TIDY TRUE)
set(DEVELOPER_RUN_CLANG_FORMAT TRUE)

include(prevent_in_source_builds)
include(options_build)
include(options_developer)


##
# Ninja Build
cmake_host_system_information(
    RESULT localhost_logical_cores
    QUERY NUMBER_OF_LOGICAL_CORES
)
math(EXPR CPU_CORES_100pc "${localhost_logical_cores}")
math(EXPR CPU_CORES_50pc  "${localhost_logical_cores} / 2")

set_property(GLOBAL 
    PROPERTY 
        JOB_POOLS
            NINJA_JOBS_100pc_CPU=${CPU_CORES_100pc}
            NINJA_JOBS_50pc_CPU=${CPU_CORES_50pc}
            NINJA_JOBS_TWO_CPU=2
            NINJA_JOBS_ONE_CPU=1
)

set(CMAKE_JOB_POOL_COMPILE NINJA_JOBS_100pc_CPU)
set(CMAKE_JOB_POOL_LINK    NINJA_JOBS_100pc_CPU)


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
# ToDo: stick at C++17 gsl::string_span, with C++20 std::span [unused]
include(external_gsl) 


## 
# Common build options: set the output folder where programs will be created.
# [Output Artifacts](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

## 
# Sub projects
add_subdirectory(doc)
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
# Install
include(GNUInstallDirs)


##
# Ignore build dir by backup apps using some 'magic'; e.g. Bacula/Bareos has
# "Exclude Dir Containing" directive for filesets
file(WRITE ${CMAKE_BINARY_DIR}/.no_backup "Don't backup the build dir\n")

