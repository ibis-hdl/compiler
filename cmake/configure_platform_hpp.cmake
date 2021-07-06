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
