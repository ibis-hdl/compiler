# Find the clang-format executable
#
# This module defines
#  CLANG_FORMAT_EXECUTABLE
#     full path to clang-format executable
#
#  CLANG_FORMAT_VERSION
#     the full version of the executable in the major.minor.patch format
#
#  CLANG_FORMAT_VERSION_MAJOR, CLANG_FORMAT_VERSION_MINOR, CLANG_FORMAT_VERSION_PATCH
#     individual components of the executable version.
#
#  CLANG_FORMAT_FOUND
#     If found
#
# As an hint, the script looks for CLANG_FORMAT_ROOT_DIR environment
# variable to extend the earch path for the executable.
#=============================================================================

# If CLANG_FORMAT_ROOT_DIR was defined in the environment, use it
if(NOT CLANG_FORMAT_ROOT_DIR AND NOT $ENV{CLANG_FORMAT_ROOT_DIR} STREQUAL "")
  set(CLANG_FORMAT_ROOT_DIR $ENV{CLANG_FORMAT_ROOT_DIR})
endif()

set(_clang_format_search_dirs
  ${CLANG_FORMAT_ROOT_DIR}
  /usr/local/bin
)

find_program(CLANG_FORMAT_EXECUTABLE
  NAMES
    clang-format-13
    clang-format-12
    clang-format-11
    clang-format-10
    clang-format
  HINTS
    ${_CLANG_FORMAT_SEARCH_DIRS}
)

if(CLANG_FORMAT_EXECUTABLE AND NOT EXISTS ${CLANG_FORMAT_EXECUTABLE})
  message(WARNING "Cached or specified Clang-format executable does not exist.")
  set(CLANG_FORMAT_FOUND FALSE)
elseif(CLANG_FORMAT_EXECUTABLE)
  set(CLANG_FORMAT_FOUND TRUE)

  # get version from the output
  execute_process(
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -version
    OUTPUT_VARIABLE CLANG_FORMAT_VERSION_RAW
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # parse parts
  if(CLANG_FORMAT_VERSION_RAW MATCHES "^clang-format version .*")
    # extract individual version components by using a list
    string(REGEX REPLACE
           "clang-format version ([.0-9]+).*" "\\1"
           CLANG_FORMAT_SEMANTIC_VERSION "${CLANG_FORMAT_VERSION_RAW}")
    string(REPLACE "." ";" CLANG_FORMAT_VERSION_PARTS "${CLANG_FORMAT_SEMANTIC_VERSION}")
    list(LENGTH CLANG_FORMAT_VERSION_PARTS CLANG_FORMAT_VERSION_PARTS_COUNT)

    # semantic version variables defaults
    set(CLANG_FORMAT_VERSION_MAJOR 0)
    set(CLANG_FORMAT_VERSION_MINOR 0)
    set(CLANG_FORMAT_VERSION_PATCH 0)

    # extract components into corresponding variables
    if(CLANG_FORMAT_VERSION_PARTS_COUNT GREATER 0)
      list(GET CLANG_FORMAT_VERSION_PARTS 0 CLANG_FORMAT_VERSION_MAJOR)
    endif()
    if(CLANG_FORMAT_VERSION_PARTS_COUNT GREATER 1)
      list(GET CLANG_FORMAT_VERSION_PARTS 1 CLANG_FORMAT_VERSION_MINOR)
    endif()
    if(CLANG_FORMAT_VERSION_PARTS_COUNT GREATER 2)
      list(GET CLANG_FORMAT_VERSION_PARTS 2 CLANG_FORMAT_VERSION_PATCH)
    endif()

    # construct full semantic version
    set(CLANG_FORMAT_VERSION 
      "${CLANG_FORMAT_VERSION_MAJOR}.${CLANG_FORMAT_VERSION_MINOR}.${CLANG_FORMAT_VERSION_PATCH}"
    )

    # unset variables no longer needed
    unset(CLANG_FORMAT_VERSION_PARTS_COUNT)
    unset(CLANG_FORMAT_SEMANTIC_VERSION)
    unset(CLANG_FORMAT_VERSION_PARTS)
  endif()

  # unset variables no longer needed
  unset(CLANG_FORMAT_VERSION_RAW)

  message(STATUS "Found Clang-Format ${CLANG_FORMAT_EXECUTABLE} v${CLANG_FORMAT_VERSION}")
else()
  set(CLANG_FORMAT_FOUND FALSE)
endif()
