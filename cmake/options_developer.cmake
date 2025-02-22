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
    #message(WARNING "-- probably unable to compile files using 4096 MiB per CPU core")
    set(CORE_4096MiB 1)
endif()
if(CORE_8192MiB EQUAL 0)
    #message(WARNING "-- probably unable to compile files using 8192 MiB per CPU core")
    set(CORE_8192MiB 1)
endif()
if(CORE_10240MiB EQUAL 0)
    #message(WARNING "-- probably unable to compile files using 10240 MiB per CPU core")
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
# Note: Don't put all headers into PCH, this may slow down
# compilation time, especially on testsuite's vhdl_rules project. See also
# DEVELOPER_RUN_CLANG_TIME_TRACE to check for headers to include in PCH
# Note: See additional notes about MSVC issues at 'source/pch/CMakeLists.txt'
option(IBIS_ENABLE_CXXSTD_PCH
    "Enable pre-compiled headers support for standard C++, Boost.Org and 3rd party headers."
    ON)
mark_as_advanced(IBIS_ENABLE_CXXSTD_PCH)


# Clang option to find headers which consumes compile time, best effort to optimize
# PCH support.
# [time-trace: timeline / flame chart profiler for Clang](
#  https://aras-p.info/blog/2019/01/16/time-trace-timeline-flame-chart-profiler-for-Clang/)
option(DEVELOPER_RUN_CLANG_TIME_TRACE
    "What and where in my code things are slow to compile? Generate flame chart Tracing JSON."
    OFF
)
mark_as_advanced(DEVELOPER_RUN_CLANG_TIME_TRACE)

if (DEVELOPER_RUN_CLANG_TIME_TRACE)
    add_compile_options(
        "$<$<CXX_COMPILER_ID:Clang>:-ftime-trace>"
    )
endif()


###############################################################################
# Project wide compiler options
#
# Note [Spaces in conditional output of generator expressions](
# http://cmake.3232098.n2.nabble.com/Spaces-in-conditional-output-of-generator-expressions-td7597652.html)
###############################################################################

add_compile_options(
    #  ---- common warnings ----
    # FixMe [CMake]: [-Wundefined-func-template], BUT see:
    #   https://www.reddit.com/r/cpp_questions/comments/8g5v3s/dealing_with_clang_warningerrors_re_static/
    # http://clang.llvm.org/docs/DiagnosticsReference.html
    "$<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Wpedantic;-Wno-c11-extensions;-Wconversion>"
    # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic;-Wconversion>"
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level
    "$<$<CXX_COMPILER_ID:MSVC>:/W3>"

    # ---- IDE support ----
    # [Full code paths in clang errors](https://stackoverflow.com/questions/31324457/full-code-paths-in-clang-errors)
    # for VS Code CodeMatcher
    "$<$<CXX_COMPILER_ID:Clang>:-fdiagnostics-absolute-paths>"
    # [/FC (Full path of source code file in diagnostics)](
    #  https://docs.microsoft.com/en-us/cpp/build/reference/fc-full-path-of-source-code-file-in-diagnostics?view=msvc-160)
    "$<$<CXX_COMPILER_ID:MSVC>:/FC>"

    # ---- Special treatment for Clang/Windows ----
    # hide warning: enumerator value is not representable in the underlying type 'int'
    # at <boost/spirit/home/support/char_encoding/standard_wide.hpp>
    "$<$<AND:$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:Windows>>:-Wno-microsoft-enum-value>"

    # ---- Big files on Win32 (Boost Spirit-X3, e.g. grammar.cpp) ----
    # Fix Fatal Error C1128: number of sections exceeded object file format limit
    "$<$<CXX_COMPILER_ID:MSVC>:/bigobj>"
    # [GCC equivalent of MS's /bigobj](https://stackoverflow.com/questions/16596876/gcc-equivalent-of-mss-bigobj)
    "$<$<AND:$<CXX_COMPILER_ID:GNU>,$<PLATFORM_ID:Windows>>:-Wa,-mbig-obj>"
)

# recursive template instance compiler tweaks
add_compile_options(
    # - limit gcc/clang template error depth printing
    # - increase limit especially for clang recursive template instantiation,
    #   otherwise exceeds maximum depth
    # Default settings:
    # [template-backtrace-limit](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html)
    #  = 10
    # [-ftemplate-depth](https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html)
    # = 900
    "$<$<CXX_COMPILER_ID:GNU>:-ftemplate-backtrace-limit=0;-ftemplate-depth=1024>"
    #"$<$<CXX_COMPILER_ID:Clang>:-ftemplate-backtrace-limit=0;-ftemplate-depth=1024>"
    # FixMe [CMake]: won't work on MSVC Clang frontend, hence won't compile with clang-cl
    # [cmake]   Error evaluating generator expression:
    # [cmake]   $<CMAKE_CXX_COMPILER_FRONTEND_VARIANT:MSVC>
    # [cmake]   Expression did not evaluate to a known generator expression
    #"$<$<AND:$<CXX_COMPILER_ID:Clang>,$<NOT:$<CMAKE_CXX_COMPILER_FRONTEND_VARIANT:MSVC>>>:-ftemplate-backtrace-limit=0;-ftemplate-depth=1024>"
)

## -----------------------------------------------------------------------------
# Sanitize support and compiler options
#
# FixMe [CMake]: Check and test flags, only added

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

# --- UndefinedBehavior ---
option(IBIS_ENABLE_UBSAN "Enable UndefinedBehavior builds." OFF)
mark_as_advanced(IBIS_ENABLE_UBSAN)

set(CMAKE_CXX_FLAGS_UBSAN "-fsanitize=undefined")
set(CMAKE_LINK_FLAGS_UBSAN "-fsanitize=undefined")

# FixMe [CMake]: Sanity checks
# Clang: [Controlling Code Generation](https://github.com/llvm/llvm-project/blob/d480f968ad8b56d3ee4a6b6df5532d485b0ad01e/clang/docs/UsersManual.rst#id108)
# It is not possible to combine more than one of the -fsanitize=address,
# -fsanitize=thread, and -fsanitize=memory checkers in the same program.

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
# Clang extra warnings, see
# - [Better Apps with Clang's Weverything or Wall is a Lie!](
#    https://amattn.com/p/better_apps_clang_weverything_or_wall_is_a_lie.html)
# - [Warnings: -Weverything and the Kitchen Sink](
#    https://embeddedartistry.com/blog/2017/3/7/clang-weverythings
#
# May require special treatment for Clang to prevent contamination with pragmas
# by using -Weverything
option(DEVELOPER_CLANG_WARN_EVERYTHING
    "Use Clang compiler's -Weverything option"
    OFF)
mark_as_advanced(DEVELOPER_CLANG_WARN_EVERYTHING)

if(DEVELOPER_CLANG_WARN_EVERYTHING)
    # no interest in compatibility to old standards
    set(_warn_compat -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c++98-c++11-c++14-compat)
    # misc
    set(_warn_misc -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors)
    # boost.test macros hell, ibis is using rarely macros
    # boost.test fires [-Wused-but-marked-unused]
    set(_warn_boost -Wno-disabled-macro-expansion -Wno-used-but-marked-unused)
    add_compile_options(
        "$<$<CXX_COMPILER_ID:Clang>:${_warn_compat};${_warn_boost};${_warn_misc}>"
    )
endif()


###############################################################################
# Project wide compile definitions
###############################################################################

## -----------------------------------------------------------------------------
# Common definitions
#
add_compile_definitions(
    # ---- Win32 ----
    # [What does #defining WIN32_LEAN_AND_MEAN exclude exactly?](
    #  https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly)
    "$<$<PLATFORM_ID:Windows>:WIN32_LEAN_AND_MEAN;VC_EXTRALEAN>"
    # Note: MSVC/Clang-Win etc. all have min/max macro problems, see
    # [Possible problem with min() and max()](https://github.com/bkaradzic/bx/issues/252)
    "$<$<PLATFORM_ID:Windows>:NOMINMAX;_CRT_SECURE_NO_WARNINGS>"
)


## -----------------------------------------------------------------------------
# Boost Spirit X3 BOOST_SPIRIT_X3_DEBUG; Note, this affects also PCH
#
option(DEVELOPER_BOOST_SPIRIT_X3_DEBUG
    "Compile the parser with BOOST_SPIRIT_X3_DEBUG."
    OFF)
mark_as_advanced(DEVELOPER_BOOST_SPIRIT_X3_DEBUG)
