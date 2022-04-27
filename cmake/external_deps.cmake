message(STATUS "External Projects (required)")

## ----------------------------------------------------------------------------
# mandatory external dependencies

##
# Boost.Org
# [CMake doesn't find Boost](https://stackoverflow.com/questions/3808775/cmake-doesnt-find-boost)
#set(Boost_DEBUG 1)
find_package(Boost 1.78.0
    REQUIRED COMPONENTS
        system
        locale
        filesystem   # Boost::process depends Boost::filesystem
        unit_test_framework
    OPTIONAL_COMPONENTS
        # FixMe: [https://github.com/conan-io/cmake-conan/issues/416]
        #stacktrace_basic
        #stacktrace_backtrace
        #stacktrace_addr2line
        #stacktrace_noop
        #stacktrace_windbg   # only @Windows
)
add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


##
# CLI11: Command line parser for C++11
# [https://github.com/CLIUtils/CLI11]
#
find_package(CLI11 2.2.0 REQUIRED)


##
# strong_type: strong typedef library for C++14/17/20
# [https://github.com/rollbear/strong_type]
CPMAddPackage("gh:rollbear/strong_type#main")
add_custom_target(external-strong_type)
set(STRONG_TYPE_INCLUDE_DIR ${strong_type_SOURCE_DIR}/include)
