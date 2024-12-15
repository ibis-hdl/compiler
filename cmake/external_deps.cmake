message(STATUS "External Projects (required)")

## ----------------------------------------------------------------------------
# mandatory external dependencies

##
# [Boost.Org](www.boost.org)
# See [Why is "BOOST_ALL_NO_LIB" set automatically? #54](https://github.com/boostorg/boost_install/issues/54)
# Boost::headers defines BOOST_ALL_NO_LIB, since there is no reason to use autolinking when using
# CMake
#
#set(Boost_DEBUG 1)
find_package(Boost 1.86.0 EXACT
    CONFIG
    REQUIRED COMPONENTS
        headers
        system
        locale
        filesystem   # Boost::process depends Boost::filesystem
        unit_test_framework
    OPTIONAL_COMPONENTS
        stacktrace_basic
        stacktrace_backtrace
        stacktrace_addr2line
        stacktrace_noop
        stacktrace_windbg   # only @Windows
)

# Make found Boost's targets globally available.
if(Boost_FOUND)
    message(STATUS "Using Boost libraries v${Boost_VERSION_STRING}")
    set_target_properties(
        Boost::headers
        PROPERTIES IMPORTED_GLOBAL TRUE )
endif ()


##
# [CLI11](https://github.com/CLIUtils/CLI11)
# Command line parser for C++11
#
find_package(CLI11 2.4.2 REQUIRED)


##
# [{fmt} lib](https://github.com/fmtlib/fmt)
# modern formatting library, until full C++20 support is there
#
find_package(fmt 11.0.2 REQUIRED)


##
# [range-v3](https://github.com/ericniebler/range-v3)
# Range library for C++14/17/20, until full C++20/23 support is there
#
find_package(range-v3 0.12.0 REQUIRED)


##
# [strong_type](https://github.com/rollbear/strong_type)
# strong typedef library for C++14/17/20
#
find_package(strong_type REQUIRED)
# ToDo: use explicit version: find_package(strong_type v15 REQUIRED)