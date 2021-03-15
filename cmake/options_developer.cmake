## -----------------------------------------------------------------------------
# developer configureable build options
## -----------------------------------------------------------------------------


##
# Developer Build Option: Use PCH
# Starting with cmake 3.16 projects can use precompiled headers
# ToDO: Study [Faster builds with PCH suggestions from C++ Build Insights](
#   https://devblogs.microsoft.com/cppblog/faster-builds-with-pch-suggestions-from-c-build-insights/)
option(EDA_ENABLE_PCH
    "Enable precompile headers support. This can speed up compilation time."
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
    "Configure EDA to use external Boost.Org Spirit Parser X3 - LL(k) Parser Framework.\
    This is useful for developers which has to work on more recent versions\
    as the build host/system supplies."
    OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)

option(DEVELOPER_EXTERNAL_BOOST_UTF 
    "Configure EDA to use external Boost.Org Unit Test Framework (UTF).\
    This is useful for developers which has to work on more recent versions\
    as the build host/system supplies."
    OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_UTF)


## -----------------------------------------------------------------------------
# evaluate options
## -----------------------------------------------------------------------------


## -----------------------------------------------------------------------------
# Project wide compiler options
#
# Note [Spaces in conditional output of generator expressions](
# http://cmake.3232098.n2.nabble.com/Spaces-in-conditional-output-of-generator-expressions-td7597652.html)
add_compile_options( # FixMe: Fails on Clang-Win actually (cmake 3.19.6)
    #  ---- warnings ----
    # http://clang.llvm.org/docs/DiagnosticsReference.html
    "$<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-c99-extensions>"
    # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic>"
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level
    "$<$<CXX_COMPILER_ID:MSVC>:/W4>"

    # ---- Big files on Win32 (grammar.cpp) ----
    # Fix Fatal Error C1128: number of sections exceeded object file format limit
    "$<$<CXX_COMPILER_ID:MSVC>:/bigobj>"
    # [GCC equivalent of MS's /bigobj](https://stackoverflow.com/questions/16596876/gcc-equivalent-of-mss-bigobj)
    "$<$<AND:$<CXX_COMPILER_ID:GNU>,$<PLATFORM_ID:Windows>>:-Wa,-mbig-obj>"
)

if(DEVELOPER_CLANG_WARN_EVERYTHING)
    add_compile_options(
        "$<$<CXX_COMPILER_ID:Clang>:-Weverything>"
    )
endif()


## -----------------------------------------------------------------------------
# Project wide compiler definitions
#

add_compile_definitions(
    # ---- Win32 ----
    # Boost Libs; see https://cmake.org/cmake/help/latest/module/FindBoost.html
    "$<$<PLATFORM_ID:Windows>:${Boost_LIB_DIAGNOSTIC_DEFINITIONS};BOOST_ALL_NO_LIB>"
    # [What does #defining WIN32_LEAN_AND_MEAN exclude exactly?](
    #  https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly)
    "$<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN;VC_EXTRALEAN>"
    # Note: MSVC/Clang-Win etc. all have min/max macro problems
    # [Possible problem with min() and max()](https://github.com/bkaradzic/bx/issues/252)
    "$<$<PLATFORM_ID:Windows>:NOMINMAX;_CRT_SECURE_NO_WARNINGS>"
)


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

