## EDA/VHDL93 project
project(vhdl93_grammar LANGUAGES CXX)

set(LIB_SOURCES
    src/ast/abstract_literal.cpp
    src/ast/based_literal.cpp
    src/ast/bit_string_literal.cpp
    src/ast/decimal_literal.cpp
    src/ast/numeric_literal.cpp
    src/ast/physical_literal.cpp
    src/grammar.cpp
    src/error_handler.cpp
    src/ast_printer.cpp
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
add_library(eda::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE FOO)
    
target_compile_options(${PROJECT_NAME} 
    PRIVATE -Wall -Wextra)

## FixMe: temporary for interface target of cmake getting working
include_directories(../../include)
#add_dependencies(${PROJECT_NAME} eda)  # FixMe: cmake_check_build_system error

## Project Depend Includes
#include_directories(${SPIRIT_X3_INCLUDE_DIR})
include_directories(${GSL_INCLUDE_DIR})

#add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} eda)
#add_dependencies(${PROJECT_NAME} gsl)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")

# 'make install' to the correct location
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${PROJECT_NAME}
    LIBRARY  DESTINATION ${PROJECT_NAME}
    RUNTIME  DESTINATION ${PROJECT_NAME})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into <prefix>/cmake.
install(EXPORT ${PROJECT_NAME}Config 
    DESTINATION share/cmake/${PROJECT_NAME}Config)

# This makes the project importable from the build directory
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)


# test suite
add_subdirectory(test)
