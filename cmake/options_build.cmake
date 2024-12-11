## -----------------------------------------------------------------------------
## user configurable build options
## -----------------------------------------------------------------------------

##
# Build Option: Support Boost.stacktrace library
option(IBIS_WITH_BOOST_STACKTRACE "Enable support for the Boost::stacktrace library." OFF)


##
# Runtime Option: Use GDB to dump the stacktrace
if(UNIX)
    option(IBIS_WITH_GDB_STACKTRACE "Enable support for dumping the stacktrace using GNU/GDB on runtime." ON)
endif()

##
# Build option: enable testing.
option(IBIS_BUILD_TESTS "Build tests" ON)
option(IBIS_CTEST_OUTPUT_ON_FAILURE "controls if the output should be logged for failed tests." ON)

if (IBIS_BUILD_TESTS)
    enable_testing()
        if(IBIS_CTEST_OUTPUT_ON_FAILURE)
        # several ways to skin the cat to get more details on errors:
        # - ['--output-on-failure'](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))
        # - [CTEST_OUTPUT_ON_FAILURE](https://cmake.org/cmake/help/latest/envvar/CTEST_OUTPUT_ON_FAILURE.html)
        # - [CMAKE_CTEST_ARGUMENTS](https://cmake.org/cmake/help/latest/variable/CMAKE_CTEST_ARGUMENTS.html)
        #   used here which requires CMake >= 3.17
        list (APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
    endif()
endif()


###############################################################################
# Sanity Checks
#
if(IBIS_WITH_BOOST_STACKTRACE AND IBIS_WITH_GDB_STACKTRACE)
    message(FATAL_ERROR "Only one stacktrace option is useful and hence allowed.")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(IBIS_WITH_BOOST_STACKTRACE OFF CACHE BOOL "No stacktrace on Darwin" FORCE)
    set(IBIS_WITH_GDB_STACKTRACE OFF CACHE BOOL "No gdb stacktrace on Darwin" FORCE)
endif()
