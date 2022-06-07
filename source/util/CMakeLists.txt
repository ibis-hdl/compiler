################################################################################
## IBIS/auxiliary project
##
## Just for curiosity: [Windows 10 Still Won’t Let You Use These File Names Reserved in 1974](
## https://www.howtogeek.com/fyi/windows-10-still-wont-let-you-use-these-file-names-reserved-in-1974/)
##
## file: source/aux/CMakeLists.txt
################################################################################

project(ibis_util LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ibis::util ALIAS ${PROJECT_NAME})


if(${PROJECT_NAME}_PCH)
    # override ibis_pch helper
    target_precompile_headers(${PROJECT_NAME}
        PRIVATE
            $<$<BOOL:${IBIS_ENABLE_PCH_DEFAULT}>:${PROJECT_SOURCE_DIR}/include/ibis/util/detail/pch_default.hpp>
            $<$<BOOL:${IBIS_ENABLE_PCH_IBIS}>:${PROJECT_SOURCE_DIR}/include/ibis/util/detail/pch_ibis.hpp>
    )
elseif(IBIS_ENABLE_PCH_DEFAULT OR IBIS_ENABLE_PCH_IBIS)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
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


## -----------------------------------------------------------------------------
## Compiler Features required for common/utils
##  -----------------------------------------------------------------------------

include(CheckCXXCompilerFlag)

##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_expect(1, 0);
    return 0;
}
" IBIS_HAVE_BUILTIN_EXPECT)


##
# MSVC extension
check_cxx_source_compiles("
#include <cstddef>
int main() {
    int x = 3;
    __assume(x == 3);
    return 0;
}
" IBIS_HAVE_BUILTIN_ASSUME)


##
# GCC extension
check_cxx_source_compiles("
int main() {
    __builtin_unreachable();
    return 0;
}
" IBIS_HAVE_BUILTIN_UNREACHABLE)


##
# Pre C++20 support for std::source_location
check_cxx_source_compiles("
#include <experimental/source_location>
int main() {
  std::experimental::source_location location{ std::experimental::source_location::current() };
  return 0;
}
" IBIS_HAVE_EXPERIMENTAL_SOURCE_LOCATION)


# The platform/compiler checks belongs to eda::common
configure_file(
  "${PROJECT_SOURCE_DIR}/include/ibis/util/compiler/compiler_support.hpp.in"
  "${PROJECT_BINARY_DIR}/include/ibis/util/compiler/compiler_support.hpp"
)
