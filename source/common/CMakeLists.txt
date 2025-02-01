################################################################################
## IBIS/common project
##
## file: source/common/CMakeLists.txt
################################################################################

project(ibis_common
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_library(${PROJECT_NAME})
add_library(ibis::common ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        fmt::fmt    # FixMe [CMake]: Even not required, MSVC PCH errors due to /utf-8 compile flag
        Boost::headers
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/indent_stream.cpp
        src/buildinfo.cpp
        src/file_loader.cpp
        src/settings.cpp
        src/user_home_dir.cpp
        src/message.cpp
)
# https://cmake.org/cmake/help/latest/prop_tgt/UNITY_BUILD_MODE.html
set_target_properties(${PROJECT_NAME} PROPERTIES
    UNITY_BUILD_MODE BATCH
    UNITY_BUILD_BATCH_SIZE 3
)
set_source_files_properties(
    src/file_loader.cpp # disabled during working on branch code-review-2024
    PROPERTIES
        SKIP_UNITY_BUILD_INCLUSION true
)


if(IBIS_ENABLE_PCH
)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)


configure_file(
    "${PROJECT_SOURCE_DIR}/include/ibis/buildinfo_static.hpp.in"
    "${PROJECT_BINARY_DIR}/include/ibis/buildinfo_static.hpp"
    ESCAPE_QUOTES
    @ONLY
)

##
# Windows MinGW
# [How to fix undefined reference to `__imp_WSACleanup' (Boost.Asio) in CLion](
#  https://stackoverflow.com/questions/38767653/how-to-fix-undefined-reference-to-imp-wsacleanup-boost-asio-in-clion)
if(MINGW)
    target_link_libraries(${PROJECT_NAME}
        ws2_32
    )
endif()


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
  "${PROJECT_SOURCE_DIR}/include/ibis/platform.hpp.in"
  "${PROJECT_BINARY_DIR}/include/ibis/platform.hpp"
)
