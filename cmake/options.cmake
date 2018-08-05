##
# Global project options

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
option(CLANG_WARN_EVERYTHING "Use Clang compiler's -Weverything option (to compile parts of the source)" OFF)


##
# Build Option: Support Boost.stacktrace library
option(EDA_WITH_BOOST_STACKTRACE "Enable support for the Boost::stacktrace library." OFF)

##
# Build Option: run EDA under Valgrind.
option(EDA_RUN_ON_VALGRIND "Configure EDA to be run on Valgrind." OFF)
mark_as_advanced(PIRANHA_RUN_ON_VALGRIND)



##
# Runtime Option: Use GDB to dump the stracktrace
option(EDA_WITH_GDB_STACKTRACE "Enable support for dumping the stacktrace using GNU/GDB on runtime." ON)




##
# Build option: enable testing.
option(EDA_BUILD_TESTS "Build tests" ON)

