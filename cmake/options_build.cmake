## -----------------------------------------------------------------------------
## user configureable build options
## -----------------------------------------------------------------------------

##
# Build Option: ANSI Color or Windows  Console I/O
if(WIN32)
    option(EDA_ON_WINDOWS_USE_ANSII_COLOR "Ignore Window's High-Level Console I/O API and use ANSII color codes." OFF)
endif()


##
# Build Option: Support Boost.stacktrace library
option(EDA_WITH_BOOST_STACKTRACE "Enable support for the Boost::stacktrace library." OFF)


##
# Runtime Option: Use GDB to dump the stracktrace
if(LINUX)
    option(EDA_WITH_GDB_STACKTRACE "Enable support for dumping the stacktrace using GNU/GDB on runtime." ON)
endif()

##
# Build option: enable testing.
option(EDA_BUILD_TESTS "Build tests" ON)
option(EDA_CTEST_OUTPUT_ON_FAILURE "controls if the output should be logged for failed tests." ON)

if (EDA_BUILD_TESTS)
    enable_testing()
        if(EDA_CTEST_OUTPUT_ON_FAILURE)
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
if(EDA_WITH_BOOST_STACKTRACE AND EDA_WITH_GDB_STACKTRACE)
    message(FATAL_ERROR "Only one stacktrace option is useful and hence allowed.")
endif()
