# Find the clang-tidy executable
#
# This module defines
#  CLANG_TIDY_EXECUTABLE
#     the full path to clang-tidy executable
#
#  CLANG_TIDY_VERSION
#     the full version of the clang-tidy in the major.minor.patch format
#
#  CLANG_TIDY_VERSION_MAJOR, CLANG_TIDY_VERSION_MINOR, CLANG_TIDY_VERSION_PATCH
#     individual components of the clang-tidy version.
#
#  CLANG_TIDY_FOUND
#     If found
#
# As an hint, the script looks for CLANG_TIDY_ROOT_DIR environment
# variable to extend the earch path for the executable.
#=============================================================================

# If CLANG_TIDY_ROOT_DIR was defined in the environment, use it.
if(NOT CLANG_TIDY_ROOT_DIR AND NOT $ENV{CLANG_TIDY_ROOT_DIR} STREQUAL "")
  set(CLANG_TIDY_ROOT_DIR $ENV{CLANG_TIDY_ROOT_DIR})
endif()

set(_clang_tidy_search_dirs
  ${CLANG_TIDY_ROOT_DIR}
  /usr/local/bin
)

find_program(CLANG_TIDY_EXECUTABLE
  NAMES
    clang-tidy-13
    clang-tidy-12
    clang-tidy-11
    clang-tidy-10
    clang-tidy
  HINTS
    ${_clang_tidy_SEARCH_DIRS}
)

if(CLANG_TIDY_EXECUTABLE AND NOT EXISTS ${CLANG_TIDY_EXECUTABLE})
  message(WARNING "Cached or specified Clang-Tidy executable does not exist.")
  set(CLANG_TIDY_FOUND FALSE)
elseif(CLANG_TIDY_EXECUTABLE)
  set(CLANG_TIDY_FOUND TRUE)

  # get version from the output
  execute_process(
    COMMAND ${CLANG_TIDY_EXECUTABLE} -version
    OUTPUT_VARIABLE CLANG_TIDY_VERSION_RAW
    ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  # parse parts.
  if(CLANG_TIDY_VERSION_RAW MATCHES "LLVM version .*")
    # extract individual version components by using a list
    string(REGEX REPLACE
           ".*LLVM version ([.0-9]+).*" "\\1"
           CLANG_TIDY_SEMANTIC_VERSION "${CLANG_TIDY_VERSION_RAW}")
    string(REPLACE "." ";" CLANG_TIDY_VERSION_PARTS "${CLANG_TIDY_SEMANTIC_VERSION}")
    list(LENGTH CLANG_TIDY_VERSION_PARTS CLANG_TIDY_VERSION_PARTS_COUNT)

    # semantic version variables defaults
    set(CLANG_TIDY_VERSION_MAJOR 0)
    set(CLANG_TIDY_VERSION_MINOR 0)
    set(CLANG_TIDY_VERSION_PATCH 0)

    # extract components into corresponding variables
    if(CLANG_TIDY_VERSION_PARTS_COUNT GREATER 0)
      list(GET CLANG_TIDY_VERSION_PARTS 0 CLANG_TIDY_VERSION_MAJOR)
    endif()
    if(CLANG_TIDY_VERSION_PARTS_COUNT GREATER 1)
      list(GET CLANG_TIDY_VERSION_PARTS 1 CLANG_TIDY_VERSION_MINOR)
    endif()
    if(CLANG_TIDY_VERSION_PARTS_COUNT GREATER 2)
      list(GET CLANG_TIDY_VERSION_PARTS 2 CLANG_TIDY_VERSION_PATCH)
    endif()

    # construct full semantic version
    set(CLANG_TIDY_VERSION 
      "${CLANG_TIDY_VERSION_MAJOR}.${CLANG_TIDY_VERSION_MINOR}.${CLANG_TIDY_VERSION_PATCH}"
    )

    # unset variables no longer needed
    unset(CLANG_TIDY_VERSION_PARTS_COUNT)
    unset(CLANG_TIDY_SEMANTIC_VERSION)
    unset(CLANG_TIDY_VERSION_PARTS)
  endif()

  # unset variables no longer needed
  unset(CLANG_TIDY_VERSION_RAW)

  message(STATUS "Found Clang-Tidy ${CLANG_TIDY_EXECUTABLE} v${CLANG_TIDY_VERSION}")
else()
  set(CLANG_TIDY_FOUND FALSE)
endif()
