################################################################################
## IBIS/util project
##
## Just for curiosity: [Windows 10 Still Won’t Let You Use These File Names Reserved in 1974](
## https://www.howtogeek.com/fyi/windows-10-still-wont-let-you-use-these-file-names-reserved-in-1974/)
##
## file: source/util/CMakeLists.txt
################################################################################

project(ibis_util
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")

add_library(${PROJECT_NAME} INTERFACE)
add_library(ibis::util ALIAS ${PROJECT_NAME})


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Boost::headers
        fmt::fmt    # FixMe [CMake]: Even not required, MSVC PCH errors due to /utf-8 compile flag
        Boost::unit_test_framework  # FixMe [CMake]: ibis::util shouldn't be depend on Boost::Utf
)


## -----------------------------------------------------------------------------
## Platform configuration
## -----------------------------------------------------------------------------
# Generate <platform.hpp> header to allow if constexpr () expressions to get rid off
# most C++ preprocessor #ifdef code.
# See [How To Write Platform Checks](
#  https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(IBIS_BUILD_PLATFORM_LINUX TRUE)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(IBIS_BUILD_PLATFORM_WINDOWS TRUE)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(IBIS_BUILD_PLATFORM_DARWIN TRUE)
elseif (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(IBIS_BUILD_PLATFORM_FREEBSD TRUE)
else()
    message(FATAL_ERROR "CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} not supported.")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(IBIS_BUILD_COMPILER_Clang TRUE)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(IBIS_BUILD_COMPILER_GNU TRUE)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(IBIS_BUILD_COMPILER_Intel TRUE)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(IBIS_BUILD_COMPILER_MSVC TRUE)
else()
    message(FATAL_ERROR "CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID} not supported.")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
        set(IBIS_BUILD_COMPILER_Clang_GNU TRUE)
    elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        set(IBIS_BUILD_COMPILER_CLANG_MSVC TRUE)
    else()
        message(FATAL_ERROR "Clang's CMAKE_CXX_COMPILER_FRONTEND_VARIANT ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} not expected.")
    endif()
endif()

configure_file(
  "${PROJECT_SOURCE_DIR}/include/ibis/util/platform.hpp.in"
  "${PROJECT_BINARY_DIR}/include/ibis/util/platform.hpp"
)
