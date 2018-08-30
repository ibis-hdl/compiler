##
# Global project options

##
# Build Option: ANSI Color or Windows  Console I/O
if(WIN32)
    option(EDA_ON_WINDOWS_USE_ANSII_COLOR "Ignore Window's High-Level Console I/O API and use ANSII color codes." ON)
endif()


##
# Build Option: Support Boost.stacktrace library
option(EDA_WITH_BOOST_STACKTRACE "Enable support for the Boost::stacktrace library." OFF)


##
# Runtime Option: Use GDB to dump the stracktrace
option(EDA_WITH_GDB_STACKTRACE "Enable support for dumping the stacktrace using GNU/GDB on runtime." ON)




##
# Build option: enable testing.
option(EDA_BUILD_TESTS "Build tests" ON)



##
# Sanity Checks
#
if(EDA_WITH_BOOST_STACKTRACE AND EDA_WITH_GDB_STACKTRACE)
    message(FATAL_ERROR "Only one stacktrace option is useful and hence allowed.")
endif()


if(EDA_WITH_BOOST_STACKTRACE)
    message(FATAL_ERROR "Sorry, my Fedora box has only boost 1.64; boost.stacktrace is since 1.65 ...")
endif()
