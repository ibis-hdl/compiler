## -----------------------------------------------------------------------------
# developer configureable build options
## -----------------------------------------------------------------------------


##
# Developer Build Option: Use PCH
# Starting with cmake 3.16 projects can use precompiled headers
# ToDO: Study [Faster builds with PCH suggestions from C++ Build Insights](
#   https://devblogs.microsoft.com/cppblog/faster-builds-with-pch-suggestions-from-c-build-insights/)
option(EDA_ENABLE_PCH
  "Enable precompile headers support. \"
   This can speed up compilation time."
  OFF)
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
option(COMPILER_CLANG_WARN_EVERYTHING 
  "Use Clang compiler's -Weverything option"
  OFF)
mark_as_advanced(COMPILER_CLANG_WARN_EVERYTHING)


## -----------------------------------------------------------------------------
# Developer Build Option: run EDA under Valgrind.
option(EDA_RUN_ON_VALGRIND 
  "Configure EDA to be run on Valgrind." 
  OFF)
mark_as_advanced(EDA_RUN_ON_VALGRIND)

##------------------------------------------------------------------------------
# Developer Build Option: Boost.Org @BleedingEdge
option(EDA_EXTERNAL_BOOST_SPIRIT_X3 
  "Configure EDA to use external Boost.Org Spirit Parser X3 - LL(k) Parser Framework. \" 
  This is usefull for developers which has to work on more recent versions \"
  as the build host/system supplies."
  OFF)
mark_as_advanced(EDA_EXTERNAL_BOOST_SPIRIT_X3)

option(EDA_EXTERNAL_BOOST_UTF 
  "Configure EDA to use external Boost.Org Unit Test Framework (UTF). \"
  This is usefull for developers which has to work on more recent versions \"
  as the build host/system supplies."
  OFF)
mark_as_advanced(EDA_EXTERNAL_BOOST_UTF)


## -----------------------------------------------------------------------------
# evaluate options
## -----------------------------------------------------------------------------


## -----------------------------------------------------------------------------
# Common Compiler Options
#
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-c99-extensions)
  add_compile_definitions()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_definitions()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  add_compile_options(-Wall -Wextra -Wpedantic)
  add_compile_definitions()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_compile_options(/W4)
  add_compile_definitions()
endif()

if(COMPILER_CLANG_WARN_EVERYTHING)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(
      -Weverything
      #-Wno-c++98-compat -Wno-c++98-compat-pedantic
      #-Wno-padded
    )
  endif()
endif()


## -----------------------------------------------------------------------------
# Bleeding Edge external Boost dependencies
# FixMe: Won't work any more: ExternalProject.cmake:1679 (get_property):
#   get_property could not find TARGET boost-utf.  Perhaps it has not yet been
#   created.
if(EDA_EXTERNAL_BOOST_SPIRIT_X3)
    include(external_spirit_x3)
endif()
if(EDA_EXTERNAL_BOOST_UTF)
    include(external_boost_utf)
endif()



## -----------------------------------------------------------------------------
# CMake source code analysis support
## -----------------------------------------------------------------------------


## -----------------------------------------------------------------------------
# CMake Tidy
#
# $ clang-tidy --checks='modernize*,performance*' --header-filter=\*.hpp$ -dump-config 
# - https://github.com/Sarcasm/notes/blob/master/dev/clang-tidy.rst
option(EDA_RUN_CLANG_TIDY 
  "Run clang-tidy with the compiler." 
  OFF)

if(EDA_RUN_CLANG_TIDY)
  find_program(CLANG_TIDY_COMMAND NAMES clang-tidy
    HINTS /opt/clang/bin
  )
  if(NOT CLANG_TIDY_COMMAND)
    message(FATAL_ERROR "EDA_RUN_CLANG_TIDY is ON but clang-tidy is not found!")
  endif()
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

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
# https://github.com/ttroy50/cmake-examples/tree/master/04-static-analysis/clang-format
set(CLANG_FORMAT_BIN_NAME clang-format)
list(APPEND CLANG_FORMAT_EXCLUDE_PATTERNS  
	"playground/" 
	"external/"
	"testsuite/" 
	"sources/vhdl/include/eda/vhdl/ast/node/"  
	"build/" 
	${CMAKE_BINARY_DIR}
)
find_package(ClangFormat)


## -----------------------------------------------------------------------------
# Include What You Use (IWYU)
# https://github.com/include-what-you-use/include-what-you-use
# on Unix/Linux only
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

