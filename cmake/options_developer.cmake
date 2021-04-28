## -----------------------------------------------------------------------------
# developer (configurable) build options
## -----------------------------------------------------------------------------


## -----------------------------------------------------------------------------
# Ninja Build using job pools
#

# Check on low memory situations to compile "big" files
cmake_host_system_information(
    RESULT LOCALHOST_RAM_MiB
    QUERY  AVAILABLE_PHYSICAL_MEMORY
)

set(LOCALHOST_RAM_MiB "${LOCALHOST_RAM_MiB}" CACHE INTERNAL "" FORCE)

# Check for CPU core count for CMAKE_JOB_POOL_{COMPILE,LINK}
cmake_host_system_information(
    RESULT LOCALHOST_LOGICAL_CORES
    QUERY  NUMBER_OF_LOGICAL_CORES
)

# Some heuristic to tune Ninja's JOB_POOL
# Note: GiB = 2^30, MiB = 2^20 Bytes, hence 10*2^(30-20) = 10240 MiB
math(EXPR CORE_2048MiB  "${LOCALHOST_RAM_MiB} / 2048")
math(EXPR CORE_3072MiB  "${LOCALHOST_RAM_MiB} / 3072")
math(EXPR CORE_4096MiB  "${LOCALHOST_RAM_MiB} / 4096")
math(EXPR CORE_8192MiB  "${LOCALHOST_RAM_MiB} / 8192")
math(EXPR CORE_10240MiB "${LOCALHOST_RAM_MiB} / 10240")

message(STATUS "Host has ${LOCALHOST_RAM_MiB} MiB of available physical memory to build. Hence")

# test on low memory build hosts and warn
if(CORE_4096MiB EQUAL 0)
    message(WARNING "-- probably unable to compile files using 4096 MiB per CPU core")
    set(CORE_4096MiB 1)
endif()
if(CORE_8192MiB EQUAL 0)
    message(WARNING "-- probably unable to compile files using 8192 MiB per CPU core")
    set(CORE_8192MiB 1)
endif()
if(CORE_10240MiB EQUAL 0)
    message(WARNING "-- probably unable to compile files using 10240 MiB per CPU core")
    set(CORE_10240MiB 1)
endif()

message(STATUS "  ${LOCALHOST_LOGICAL_CORES} CPU core(s) for common jobs")
message(STATUS "  ${CORE_2048MiB} CPU core(s) for 2048 MiB to compile")
message(STATUS "  ${CORE_3072MiB} CPU core(s) for 3072 MiB to compile")
message(STATUS "  ${CORE_4096MiB} CPU core(s) for 4096 MiB to compile")
message(STATUS "  ${CORE_8192MiB} CPU core(s) for 8192 MiB to compile")
message(STATUS "  ${CORE_10240MiB} CPU core(s) for 10240 MiB to compile")

set_property(GLOBAL
    APPEND
        PROPERTY
            JOB_POOLS
                NINJA_JOBS_SINGLE_CORE=1
                NINJA_JOBS_CORE_MAX=${LOCALHOST_LOGICAL_CORES}
                NINJA_JOBS_CORE_2048MiB=${CORE_2048MiB}
                NINJA_JOBS_CORE_3072MiB=${CORE_3072MiB}
                NINJA_JOBS_CORE_4096MiB=${CORE_4096MiB}
                NINJA_JOBS_CORE_8192MiB=${CORE_8192MiB}
                NINJA_JOBS_CORE_10240MiB=${CORE_10240MiB}
)

set_property(GLOBAL
    PROPERTY
        JOB_POOL_COMPILE    NINJA_JOBS_CORE_MAX
)
set_property(GLOBAL
    PROPERTY
        JOB_POOL_LINK       NINJA_JOBS_CORE_MAX
)


##
# Developer Build Option: Use PCH
# Starting with CMake 3.16 projects can use precompiled headers
# ToDo: Study [Faster builds with PCH suggestions from C++ Build Insights](
#   https://devblogs.microsoft.com/cppblog/faster-builds-with-pch-suggestions-from-c-build-insights/)
# Note: PCH seems to slow down (Clang11/Fedora)! compilation time especially
# on testsuite's vhdl_rulesproject, even at system update PCH are invalided
# and hence all is compiled now. Hence disabled for now.
option(IBIS_ENABLE_PCH
    "Enable pre-compiled headers support. This can speed up compilation time."
    OFF)
mark_as_advanced(IBIS_ENABLE_PCH)


## -----------------------------------------------------------------------------
# Project wide compiler options
#
# Note [Spaces in conditional output of generator expressions](
# http://cmake.3232098.n2.nabble.com/Spaces-in-conditional-output-of-generator-expressions-td7597652.html)
add_compile_options(
    #  ---- common warnings ----
    # http://clang.llvm.org/docs/DiagnosticsReference.html
    "$<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-c11-extensions>"
    # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic>"
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level
    "$<$<CXX_COMPILER_ID:MSVC>:/W4>"

    # ---- Special treatment for CLang/Windows ----
    # hide warning: enumerator value is not representable in the underlying type 'int'
    # at <boost/spirit/home/support/char_encoding/standard_wide.hpp>
    "$<$<AND:$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:Windows>>:-Wno-microsoft-enum-value>"

    # ---- Big files on Win32 (Boost Spirit-X3, e.g. grammar.cpp) ----
    # Fix Fatal Error C1128: number of sections exceeded object file format limit
    "$<$<CXX_COMPILER_ID:MSVC>:/bigobj>"
    # [GCC equivalent of MS's /bigobj](https://stackoverflow.com/questions/16596876/gcc-equivalent-of-mss-bigobj)
    "$<$<AND:$<CXX_COMPILER_ID:GNU>,$<PLATFORM_ID:Windows>>:-Wa,-mbig-obj>"
)

# cope with low memory situations
# for Window compiler reference: [X3: recursive rules reach template instantiation limit too quickly? #575](
#  https://github.com/boostorg/spirit/issues/575)
if(LOCALHOST_RAM_MiB GREATER 10240)
    add_compile_options(
        # - limit gcc/clang template error depth printing
        # - increase limit especially for clang recursive template instantiation,
        #   otherwise exceedes maximum depth
        "$<$<CXX_COMPILER_ID:GNU>:-ftemplate-backtrace-limit=0;-ftemplate-depth=1024>"
        "$<$<CXX_COMPILER_ID:Clang>:-ftemplate-backtrace-limit=0;-ftemplate-depth=1024>"
    )
else()
    message(STATUS "limit template optimization level to cope with low memory on build host!")
    add_compile_options(
        # Default settings:
        # [template-backtrace-limit](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html)
        #  = 10
        # [-ftemplate-depth](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html)
        # = 900
        "$<$<CXX_COMPILER_ID:GNU>:-ftemplate-backtrace-limit=10;-ftemplate-depth=900>"
        "$<$<CXX_COMPILER_ID:Clang>:-ftemplate-backtrace-limit=10;-ftemplate-depth=900>"
    )
endif()



## -----------------------------------------------------------------------------
# Satanizer compiler options
#
# FixMe: Check and test flags, only added

# --- ThreadSanitizer ---
option(IBIS_ENABLE_TSAN "Enable ThreadSanitizer builds." OFF)
mark_as_advanced(IBIS_ENABLE_TSAN)

set(CMAKE_CXX_FLAGS_TSAN "-fsanitize=thread")
set(CMAKE_LINK_FLAGS_TSAN "-fsanitize=thread")

# --- AddressSanitize ---
option(IBIS_ENABLE_ASAN "Enable AddressSanitize builds." OFF)
mark_as_advanced(IBIS_ENABLE_ASAN)

set(CMAKE_CXX_FLAGS_ASAN "-fsanitize=address;-fno-omit-frame-pointer")
set(CMAKE_LINK_FLAGS_ASAN "-fsanitize=address;-fno-omit-frame-pointer")

# --- LeakSanitizer ---
option(IBIS_ENABLE_LSAN "Enable LeakSanitizer builds." OFF)
mark_as_advanced(IBIS_ENABLE_LSAN)

set(CMAKE_CXX_FLAGS_LSAN "-fsanitize=leak;-fno-omit-frame-pointer")
set(CMAKE_LINK_FLAGS_LSAN "-fsanitize=leak;-fno-omit-frame-pointer")

# --- MemorySanitizer ---
option(IBIS_ENABLE_MSAN "Enable MemorySanitizer builds." OFF)
mark_as_advanced(IBIS_ENABLE_MSAN)

set(CMAKE_CXX_FLAGS_MSAN "-fsanitize=memory;-fno-omit-frame-pointer")
set(CMAKE_LINK_FLAGS_MSAN "-fsanitize=memory;-fno-omit-frame-pointer")

# --- UndefinedBehaviour ---
option(IBIS_ENABLE_UBSAN "Enable UndefinedBehaviour builds." OFF)
mark_as_advanced(IBIS_ENABLE_UBSAN)

set(CMAKE_CXX_FLAGS_UBSAN "-fsanitize=undefined")
set(CMAKE_LINK_FLAGS_UBSAN "-fsanitize=undefined")

# FixMe: Sanity checks

add_compile_options(
    "$<$<BOOL:${IBIS_ENABLE_TSAN}>:${CMAKE_CXX_FLAGS_TSAN}>"
    "$<$<BOOL:${IBIS_ENABLE_ASAN}>:${CMAKE_CXX_FLAGS_ASAN}>"
    "$<$<BOOL:${IBIS_ENABLE_LSAN}>:${CMAKE_CXX_FLAGS_LSAN}>"
    "$<$<BOOL:${IBIS_ENABLE_MSAN}>:${CMAKE_CXX_FLAGS_MSAN}>"
    "$<$<BOOL:${IBIS_ENABLE_UBSAN}>:${CMAKE_CXX_FLAGS_UBSAN}>"
)

add_link_options(
    "$<$<BOOL:${IBIS_ENABLE_TSAN}>:${CMAKE_LINK_FLAGS_TSAN}>"
    "$<$<BOOL:${IBIS_ENABLE_ASAN}>:${CMAKE_LINK_FLAGS_ASAN}>"
    "$<$<BOOL:${IBIS_ENABLE_LSAN}>:${CMAKE_LINK_FLAGS_LSAN}>"
    "$<$<BOOL:${IBIS_ENABLE_MSAN}>:${CMAKE_LINK_FLAGS_MSAN}>"
    "$<$<BOOL:${IBIS_ENABLE_UBSAN}>:${CMAKE_LINK_FLAGS_UBSAN}>"
)


## -----------------------------------------------------------------------------
# CLang extra warnings, see
# - [Better Apps with Clang's Weverything or Wall is a Lie!](
#    https://amattn.com/p/better_apps_clang_weverything_or_wall_is_a_lie.html)
# - [Warnings: -Weverything and the Kitchen Sink](
#    https://embeddedartistry.com/blog/2017/3/7/clang-weverythings
#
# May require special treatment for clang to prevent contamination with pragmas
# by using -Weverything
option(DEVELOPER_CLANG_WARN_EVERYTHING
    "Use Clang compiler's -Weverything option"
    OFF)
mark_as_advanced(DEVELOPER_CLANG_WARN_EVERYTHING)

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
#   get_property could not find TARGET boost-utf. Perhaps it has not yet been
#   created -> investigate if the time is coming.
option(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3
    "Configure IBIS HDL to use external Boost.Org Spirit Parser X3 - LL(k) Parser Framework.\
    This is useful for developers which has to work on more recent versions\
    as the build host/system supplies."
    OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)

if(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)
    include(external_spirit_x3)
endif()

option(DEVELOPER_EXTERNAL_BOOST_UTF
    "Configure IBIS HDL to use external Boost.Org Unit Test Framework (UTF).\
    This is useful for developers which has to work on more recent versions\
    as the build host/system supplies."
    OFF)
mark_as_advanced(DEVELOPER_EXTERNAL_BOOST_UTF)

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
        message(STATUS "=> Configure Fix: <DEVELOPER_RUN_CLANG_TIDY> is ON but clang-tidy is not found, disabled")
        set(CLANG_TIDY_FOUND OFF CACHE BOOL "clang-tidy (not found)" FORCE)
    endif()

    # Run clang-tidy on each of the C++ source file of the project
    # Don't apply on 3rd party libraries, see
    # [What is the correct way of providing header-filter for clang-tidy in Cmake?](
    # https://stackoverflow.com/questions/61001314/what-is-the-correct-way-of-providing-header-filter-for-clang-tidy-in-cmake)
    # '-header-filter' overrides the 'HeaderFilterRegex' option in .clang-tidy file,
    # using POSIX RE expression (ERE) syntax (see llvm::Regex Class Reference)
    set(_cltidy_filter_re "^((?!(/external/|/boost/|/testsuite/)).)*$")
    # clang-tidy lookup for .clang-tidy upwards and uses it
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-header-filter='${_cltidy_filter_re}'")
    # ... alternatively apply some fixes
    #set(_cltidy_checks "-*,modernize-concat-nested-namespaces")
    #set(_cltidy_fix    "-fix -fix-errors")
    #set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-checks=${_cltidy_checks};${_cltidy_fix};-header-filter='${_cltidy_filter_re}'")

    # About [How to integrate clang-tidy with CMake](
    #  https://gitlab.kitware.com/cmake/cmake/-/issues/18926):
    # My google foo shows many copy&paste solutions, but no one seems to use the
    # CLANG_TIDY_DEFINITIONS (or even CLANG_TIDY_SHA1) with preprocessor
    # definition finally. Some please on clarification aren't answered.
    # IMO in this state it does nothing, hence not used/omitted.
endif()

configure_file(${CMAKE_SOURCE_DIR}/.clang-tidy ${CMAKE_BINARY_DIR}/.clang-tidy COPYONLY)

# Special handling for MSVC
# FixMe: Clang-Tidy and MSVC aren't compatible? Got error about:
# error: cannot use 'throw' with exceptions disabled [clang-diagnostic-error]
if(MSVC)
    if(DEVELOPER_RUN_CLANG_TIDY)
        message(STATUS "=> Configure Fix: Disable <DEVELOPER_RUN_CLANG_TIDY> while using MSVC compiler")
        set(DEVELOPER_RUN_CLANG_TIDY "FALSE" CACHE STRING "")
    endif()
else()
    # always enable it on others platforms
    set(DEVELOPER_RUN_CLANG_TIDY TRUE CACHE STRING "")
endif()


## -----------------------------------------------------------------------------
# Include What You Use (IWYU)
#
# https://github.com/include-what-you-use/include-what-you-use
option(DEVELOPER_RUN_IWYU
    "Run include-what-you-use with the compiler."
    OFF)
mark_as_advanced(DEVELOPER_RUN_IWYU)

if(DEVELOPER_RUN_IWYU AND UNIX)
    find_program(IWYU_EXECUTABLE NAMES include-what-you-use iwyu)
    if(NOT IWYU_EXECUTABLE)
        message(STATUS "=> Configure Fix: include-what-you-use not found, no analysis of include files possible, disabled")
        set(DEVELOPER_RUN_IWYU OFF CACHE BOOL "include-what-you-use (not found)" FORCE)
    else()
        # [IWYU Mappings](https://github.com/include-what-you-use/include-what-you-use/blob/master/docs/IWYUMappings.md)
        #set(_iwyu_mapping "-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/misc_iwyu.imp;-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/boost-1.75-all.imp")
        set(_iwyu_mapping "-Xiwyu;--mapping_file=${CMAKE_SOURCE_DIR}/cmake/utils/iwyu/project.imp")
        # misc
        set(_iwyu_comment "-Xiwyu;--no_comments")
        #set(_iwyu_comment "-Xiwyu;--max_line_length=160")
        set(_iwyu_misc "-Xiwyu;--transitive_includes_only;-Xiwyu;--quoted_includes_first;-Xiwyu;--cxx17ns")
        # https://cmake.org/cmake/help/v3.20/prop_tgt/LANG_INCLUDE_WHAT_YOU_USE.html
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_EXECUTABLE};${_iwyu_mapping};${_iwyu_comment};${_iwyu_misc}")
    endif()
    # Sanity check: If PCH is enabled, IWYU lookup definitions etc. at precompiled headers
    # which breaks builds without it, giving false positives. Hence disable PCH if using IWYU.
    if(IBIS_ENABLE_PCH AND DEVELOPER_RUN_IWYU)
        message(STATUS "=> Configure Fix: include-what-you-use my trigger false positives if PCH is enabled, disabled")
        set(IBIS_ENABLE_PCH OFF CACHE BOOL "PCH disabled due to use of include-what-you-use" FORCE)
    endif()
endif()


## -----------------------------------------------------------------------------
# Developer Build Option: run IBIS under Valgrind.
# FixMe: Implement, Check and test it, only added (remnants from old project)
option(DEVELOPER_RUN_ON_VALGRIND
    "Configure IBIS HDL to be run on Valgrind."
    OFF)
mark_as_advanced(DEVELOPER_RUN_ON_VALGRIND)


## -----------------------------------------------------------------------------
# Clang-format
#
# https://github.com/ttroy50/cmake-examples/tree/master/04-static-analysis/clang-format
# Maybe: https://github.com/TheLartians/Format.cmake , or https://github.com/zemasoft/clangformat-cmake ??
option(DEVELOPER_RUN_CLANG_FORMAT
    "Run clang-format with the compiler."
    OFF)
mark_as_advanced(DEVELOPER_RUN_CLANG_FORMAT)

if(DEVELOPER_RUN_CLANG_FORMAT)
    include(FindClangFormat)

    if(NOT CLANG_FORMAT_FOUND)
        message(STATUS "=> Configure Fix: <DEVELOPER_RUN_CLANG_FORMAT> is ON but clang-format is not found, disabled")
        set(DEVELOPER_RUN_CLANG_FORMAT ON CACHE BOOL "clang-format (not found)" FORCE)
    else()
        include(clang-format)
    endif()
endif()


include(cmake/module/CPM.cmake)

CPMAddPackage(
  NAME Format.cmake
  VERSION 1.7.0
  GITHUB_REPOSITORY TheLartians/Format.cmake
  OPTIONS # set to yes skip cmake formatting
          "FORMAT_SKIP_CMAKE YES"
          # path to exclude (optional, supports regular expressions)
          "CMAKE_FORMAT_EXCLUDE cmake/CPM.cmake"
)

################################################################################
# CMake Miscellaneous
#
################################################################################

## -----------------------------------------------------------------------------
# Compile Command JSON, e.g. VS Code
#
# [Copy compile_commands.json to project root folder](
#  https://stackoverflow.com/questions/57464766/copy-compile-commands-json-to-project-root-folder)
#
# FixMe: Option #2 doesn't work for me :(
#
# Nevertheless, an easy solution is to add on '.vscode/c_cpp_properties.json':
# {
#     "configurations": [
#         {
#             ...
#             "compileCommands": "${workspaceFolder}/compile_commands.json"
#     ],
#     "version": 4
# }
add_custom_target(copy-compile-commands ALL
    COMMENT "copy compiler database 'compile_commands.json' to source directory."
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}
    VERBATIM
)

