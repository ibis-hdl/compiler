## EDA/VHDL93 project
project(vhdl93 LANGUAGES CXX)

set(PROJECT_LIB vhdl93_grammar)

set(LIB_SOURCES
    src/ast/based_literal.cpp
    src/ast/bit_string_literal.cpp
    src/ast/decimal_literal.cpp
    src/ast/physical_literal.cpp
    src/grammar.cpp
    src/error_handler.cpp
    src/ast_printer.cpp
)

## FixMe: temporary for interface target of cmake getting working
include_directories(../../include)


include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${GSL_INCLUDE_DIR})

add_library(${PROJECT_LIB} STATIC ${LIB_SOURCES})

target_include_directories(${PROJECT_LIB} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_compile_options(${PROJECT_LIB} 
    PRIVATE -Wall -Wextra)

#add_dependencies(${PROJECT_LIB} boost-spirit-x3)
add_dependencies(${PROJECT_LIB} gsl)

set_target_properties(${PROJECT_LIB} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_LIB} PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_LIB} PROPERTIES DEBUG_POSTFIX "_d")

# 'make install' to the correct location
install(TARGETS ${PROJECT_LIB} EXPORT Vhdl93LibraryConfig
    ARCHIVE  DESTINATION ${PROJECT_LIB}
    LIBRARY  DESTINATION ${PROJECT_LIB}
    RUNTIME  DESTINATION ${PROJECT_LIB})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.
install(EXPORT Vhdl93LibraryConfig DESTINATION share/Vhdl93LibraryConfig/cmake)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_LIB} FILE Vhdl93LibraryConfig.cmake)


# test suite
add_subdirectory(test)
