## -----------------------------------------------------------------------------
# developer configureable build options
## -----------------------------------------------------------------------------


##
# Developer Build Option: Use PCH
# Starting with cmake 3.16 projects can use precompiled headers
# ToDO: Study [Faster builds with PCH suggestions from C++ Build Insights](
#   https://devblogs.microsoft.com/cppblog/faster-builds-with-pch-suggestions-from-c-build-insights/)
option(EDA_ENABLE_PCH
  "Enable precompile headers support. \"
   This can speed up compilation time."
  ON)
mark_as_advanced(EDA_ENABLE_PCH)


## 
# CLang extra warnings
# - [Better Apps with Clang's Weverything or Wall is a Lie!](
#    https://amattn.com/p/better_apps_clang_weverything_or_wall_is_a_lie.html)
# - [Warnings: -Weverything and the Kitchen Sink](
#    https://embeddedartistry.com/blog/2017/3/7/clang-weverythings
#
# May require special treatment for clang to prevent contamination with pragmas 
# by using -Weverything
#
# ToDo: modern CMake uses add_compile_options()?

## -----------------------------------------------------------------------------
# Developer Build Option: Use Clang's -Weverything (Clang only)
option(DEVELOPER_CLANG_WARN_EVERYTHING 
  "Use Clang compiler's -Weverything option"
  OFF)
mark_as_advanced(DEVELOPER_CLANG_WARN_EVERYTHING)


## -----------------------------------------------------------------------------
# Developer Build Option: run EDA under Valgrind.
# FixMe: not implemented
option(DEVELOPER_RUN_ON_VALGRIND 
  "Configure EDA to be run on Valgrind." 
  OFF)
mark_as_advanced(DEVELOPER_RUN_ON_VALGRIND)

##------------------------------------------------------------------------------
# Developer Build Option: Boost.Org @BleedingEdge
option(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3 
  "Configure EDA to use external Boost.Org Spirit Parser X3 - LL(k) Parser Framework. \" 
  This is usefull for developers which has to work on more recent versions \"
  as the build host/system supplies."
  OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)

option(DEVELOPER_EXTERNAL_BOOST_UTF 
  "Configure EDA to use external Boost.Org Unit Test Framework (UTF). \"
  This is usefull for developers which has to work on more recent versions \"
  as the build host/system supplies."
  OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_UTF)


## -----------------------------------------------------------------------------
# evaluate options
## -----------------------------------------------------------------------------


## -----------------------------------------------------------------------------
# Common Compiler Options
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-c99-extensions)
  add_compile_definitions()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_definitions()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_definitions()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_options(/W4)
  add_compile_definitions()
endif()

if(DEVELOPER_CLANG_WARN_EVERYTHING)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(
      -Weverything
      #-Wno-c++98-compat -Wno-c++98-compat-pedantic
      #-Wno-padded
    )
  endif()
endif()


## -----------------------------------------------------------------------------
# Bleeding Edge external Boost dependencies
# FixMe: Won't work any more: ExternalProject.cmake:1679 (get_property):
#   get_property could not find TARGET boost-utf.  Perhaps it has not yet been
#   created.
if(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)
    include(external_spirit_x3)
endif()
if(DEVELOPER_EXTERNAL_BOOST_UTF)
    include(external_boost_utf)
endif()


################################################################################
# CMake source code analysis support
#
# [Static checks with CMake/CDash (iwyu, clang-tidy, lwyu, cpplint and cppcheck)](
# https://blog.kitware.com/static-checks-with-cmake-cdash-iwyu-clang-tidy-lwyu-cpplint-and-cppcheck/)
################################################################################

## -----------------------------------------------------------------------------
# CMake Tidy
#
# $ clang-tidy --checks='modernize*,performance*' --header-filter=\*.hpp$ -dump-config 
option(DEVELOPER_RUN_CLANG_TIDY 
  "Run clang-tidy with the compiler." 
  OFF)
mark_as_advanced(DEVELOPER_RUN_CLANG_TIDY)

if(DEVELOPER_RUN_CLANG_TIDY)

  include(FindClangTidy)

  if(NOT CLANG_TIDY_FOUND)
    message(FATAL_ERROR "DEVELOPER_RUN_CLANG_TIDY is ON but clang-tidy is not found!")
  endif()

  # Run clang-tidy on each of the C++ source file of the project
  # Don't apply on 3rd party libraries, see
  # [What is the correct way of providing header-filter for clang-tidy in Cmake?](
  # https://stackoverflow.com/questions/61001314/what-is-the-correct-way-of-providing-header-filter-for-clang-tidy-in-cmake)
  # '-header-filter' overrides the 'HeaderFilterRegex' option in .clang-tidy file,
  # using POSIX RE expression (ERE) syntax (see llvm::Regex Class Reference)
  set(_cltidy_filter_re "^((?!(/external/|/boost/|/testsuite/)).)*$")
  set(_cltidy_checks    "-*,modernize-*")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-header-filter='${_cltidy_filter_re}'")
  # alternative/temporary
  #set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-checks=${_cltidy_checks};-header-filter='${_cltidy_filter_re}'")

  # [How to integrate clang-tidy with CMake](
  #  https://gitlab.kitware.com/cmake/cmake/-/issues/18926)
  # Create a preprocessor definition that depends on .clang-tidy content so
  # the compile command will change when .clang-tidy changes.  This ensures
  # that a subsequent build re-runs clang-tidy on all sources even if they
  # do not otherwise need to be recompiled.  Nothing actually uses this
  # definition.  We add it to targets on which we run clang-tidy just to
  # get the build dependency on the .clang-tidy file.
  file(SHA1 ${CMAKE_SOURCE_DIR}/.clang-tidy clang_tidy_sha1)
  set(CLANG_TIDY_DEFINITIONS "CLANG_TIDY_SHA1=${clang_tidy_sha1}")
  unset(clang_tidy_sha1)
endif()

configure_file(${eda_SOURCE_DIR}/.clang-tidy ${eda_BINARY_DIR}/.clang-tidy COPYONLY)


## -----------------------------------------------------------------------------
# Clang-format
#
# https://github.com/ttroy50/cmake-examples/tree/master/04-static-analysis/clang-format
option(DEVELOPER_RUN_CLANG_FORMAT
  "Run clang-format with the compiler." 
  OFF)
mark_as_advanced(DEVELOPER_RUN_CLANG_FORMAT)

if(DEVELOPER_RUN_CLANG_FORMAT)

  include(FindClangFormat)

  if(NOT CLANG_FORMAT_FOUND)
    message(FATAL_ERROR "DEVELOPER_RUN_CLANG_FORMAT is ON but clang-format is not found!")
  else()
    include(clang-format)
  endif()
endif()


## -----------------------------------------------------------------------------
# Include What You Use (IWYU)
# https://github.com/include-what-you-use/include-what-you-use
# on Unix/Linux only
# FixMe: Update with https://github.com/miurahr/cmake-qt-packaging-example/blob/master/CMakeLists.txt
if(UNIX)
  configure_file(${CMAKE_SOURCE_DIR}/cmake/util/cmake-iwyu.sh.cmake
                 ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cmake-iwyu.sh @ONLY
  )
  file(COPY ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/cmake-iwyu.sh
        DESTINATION ${CMAKE_BINARY_DIR}
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ
        GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  )
endif()

