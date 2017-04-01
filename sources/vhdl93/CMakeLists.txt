cmake_minimum_required(VERSION 3.6)

## EDA/VHDL93 project
project(eda_vhdl93_grammar LANGUAGES CXX)

set(LIB_SOURCES
    src/ast/bit_string_literal.cpp
    src/ast/decimal_literal.cpp
    src/grammar.cpp
    src/error_handler.cpp
    src/ast_printer.cpp
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
add_library(eda::vhdl93_grammar ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE FOO)

target_compile_options(${PROJECT_NAME}
    PRIVATE -Wall -Wextra)

## Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
)


## Project Depend Includes
#include_directories(${SPIRIT_X3_INCLUDE_DIR})
#include_directories(${GSL_INCLUDE_DIR})

#add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} eda)
#add_dependencies(${PROJECT_NAME} gsl)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")


## Install targets
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${PROJECT_NAME}
    LIBRARY  DESTINATION ${PROJECT_NAME}
    RUNTIME  DESTINATION ${PROJECT_NAME})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config
    DESTINATION share/cmake/${PROJECT_NAME}Config)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)


# test suite
add_subdirectory(test)
