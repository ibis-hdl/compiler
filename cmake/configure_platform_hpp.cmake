# Platform configuration
# [How To Write Platform Checks](
#  https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks)

if (UNIX)
    set(BUILD_PLATFORM_UNIX TRUE)
elseif (WIN32)
    set(BUILD_PLATFORM_WIN32 TRUE)
elseif(APPLE)
    set(BUILD_PLATFORM_APPLE TRUE)
elseif(MINGW)
    set(BUILD_PLATFORM_MINGW TRUE)
elseif(MSYS)
    set(BUILD_PLATFORM_MSYS TRUE)
elseif(CYGWIN)
    set(BUILD_PLATFORM_CYGWIN TRUE)
else()
    message(FATAL_ERROR "CMake is unable to determine build platform information.")
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(BUILD_SYSTEM_LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(BUILD_SYSTEM_WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(BUILD_SYSTEM_DARWIN TRUE)
elseif (${CMAKE_SYSTEM_} STREQUAL "FreeBSD")
    set(BUILD_SYSTEM_FREEBSD TRUE)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "MSYS")
    set(BUILD_SYSTEM_MSYS TRUE)
else()
    message(FATAL_ERROR "CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME} not supported.")
endif()


configure_file(
  "${PROJECT_SOURCE_DIR}/include/eda/platform.hpp.in"
  "${PROJECT_BINARY_DIR}/include/eda/platform.hpp"
)
