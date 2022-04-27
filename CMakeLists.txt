################################################################################
## IBIS HDL project
##
## file: CMakeLists.txt
################################################################################

#set (CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/cmake/module/CxxFlagOverrides.cmake")

cmake_minimum_required(VERSION 3.20)

project(ibis
    VERSION 0.0.1
    DESCRIPTION "HDL compiler and simulator"
    HOMEPAGE_URL "https://github.com/ibis-hdl/compiler"
    LANGUAGES CXX
)
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Version: ${ibis_VERSION}")


## global C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


## CMake modules
list(APPEND
    CMAKE_MODULE_PATH
        ${CMAKE_BINARY_DIR} # conan
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_SOURCE_DIR}/cmake/module
)


include(prevent_in_source_builds)


## Conan C/C++ Open Source Package Manager
## [https://docs.conan.io/en/latest/howtos/cmake_launch.html]
## [https://github.com/conan-io/cmake-conan]
##
## FixMe:
## - [https://github.com/conan-io/conan-center-index/pull/9069]
## - [https://github.com/conan-io/cmake-conan/issues/416]
find_package(Python3 COMPONENTS Interpreter REQUIRED)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD
        #                                   CHECK RELEASES -----v
        "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(
    REQUIRES
        boost/1.78.0
        cli11/2.2.0
        #fmt/8.1.1
    GENERATORS
        cmake_find_package
        #virtualenv
    #BUILD_REQUIRES cmake/3.23.1 ninja/1.10.2
    IMPORTS "bin, *.dll -> ${CMAKE_BINARY_DIR}/bin"
    IMPORTS "lib, *.dylib* -> ${CMAKE_BINARY_DIR}/lib"
    # override defaults [https://github.com/conan-io/conan-center-index/blob/master/recipes/boost/all/conanfile.py]
    # > conan inspect boost/1.X.Y@ -a options
    OPTIONS "boost:zstd=True"
    OPTIONS "boost:system_no_deprecated=True"
    OPTIONS "boost:asio_no_deprecated=True"
    OPTIONS "boost:filesystem_no_deprecated=True"
    OPTIONS "boost:diagnostic_definitions=False"
    #OPTIONS "boost:python_executable=${Python3_EXECUTABLE}"
    # boost libs, avoid unnecessary builds; Note: python is disabled due to NumPy dependency
    # [conan-center-index/issues/8826]{https://github.com/conan-io/conan-center-index/issues/8826}
    OPTIONS "boost:without_python=True"
    OPTIONS "boost:without_context=True"
    OPTIONS "boost:without_contract=True"
    OPTIONS "boost:without_coroutine=True"
    OPTIONS "boost:without_fiber=True"
    OPTIONS "boost:without_graph=True"
    OPTIONS "boost:without_iostreams=True"
    OPTIONS "boost:without_log=True"
    OPTIONS "boost:without_math=True"
    OPTIONS "boost:without_nowide=True"
    OPTIONS "boost:without_program_options=True"
    OPTIONS "boost:without_random=True"
    OPTIONS "boost:without_regex=True"
    OPTIONS "boost:without_serialization=True"
    OPTIONS "boost:without_timer=True"
    OPTIONS "boost:without_type_erasure=True"
    OPTIONS "boost:without_wave=True"
    #OPTIONS "fmt:shared=True"
)

conan_cmake_autodetect(conan_settings)

conan_cmake_install(
    PATH_OR_REFERENCE .
    BUILD missing
    REMOTE conancenter
    SETTINGS ${conan_settings} # compiler.libcxx=libstdc++11"
)


# [cpm-cmake/CPM.cmake](https://github.com/cpm-cmake/CPM.cmake)
include(cmake/module/CPM.cmake) # FixMe full path

include(options_build)
include(options_developer)
include(external_deps)
include(external_optional)
include(py_env)


# This requirement rises by use of CMake's PCH support, otherwise
# linker errors occur. Probably due to boost.org
# [How do I force CMake to include “-pthread” option during compilation?](
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
    add_subdirectory(testsuite/pch)
    add_subdirectory(testsuite/common_util)
    add_subdirectory(testsuite/util)
    add_subdirectory(testsuite/vhdl/numeric_convert)
    add_subdirectory(testsuite/vhdl/ast)
    add_subdirectory(testsuite/vhdl/parser_rules)
    add_subdirectory(testsuite/vhdl/syntax)
    add_subdirectory(testsuite/frontend)
endif()
add_subdirectory(doc)
add_subdirectory(doc_ng)


##
# Install
include(GNUInstallDirs)
