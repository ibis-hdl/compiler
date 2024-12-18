message(STATUS "External Projects (required)")

## ----------------------------------------------------------------------------
# mandatory external dependencies

##
# [Boost.Org](www.boost.org)
#set(Boost_DEBUG 1)
find_package(Boost 1.86.0 EXACT
    CONFIG
    REQUIRED COMPONENTS
        headers
        system
        locale
        unit_test_framework
    OPTIONAL_COMPONENTS
        #none
)

set_target_properties(
    Boost::headers Boost::disable_autolinking
    PROPERTIES IMPORTED_GLOBAL TRUE )


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
# ToDo: use explicit version: find_package(strong_type 15 REQUIRED)