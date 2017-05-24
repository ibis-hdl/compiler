cmake_minimum_required(VERSION 3.6)

## EDA/VHDL93 project
project(eda_vhdl93_parser LANGUAGES CXX)

## C++ Standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(LIB_SOURCES
    src/ast/bit_string_literal.cpp
    src/ast/decimal_literal.cpp
    src/ast/keyword_token.cpp
    src/ast/operator_token.cpp
    src/error_handler.cpp
    src/ast_printer.cpp
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
add_library(eda::vhdl93_parser ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE FOO)

target_compile_options(${PROJECT_NAME}
    PRIVATE -Wall -Wextra)

# limit gcc template error depth printing
target_compile_options(${PROJECT_NAME}
    PRIVATE -ftemplate-backtrace-limit=1)

# increase limit for clang recursive template instantiation
# otherwise exceedes maximum depth of 256
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -ftemplate-depth=1024)
endif()


## X3 Parser DEBUG
#  show warnings about dereferencing type-punned pointer will break strict-aliasing
#  rules [-Wstrict-aliasing] (spirit.x3 1.64 e.g.)
set(EDA_VHDL93_PARSER_DEBUG OFF CACHE BOOL "debug printer of spirit.x3 parser tree")

if("${EDA_VHDL93_PARSER_DEBUG}")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG=1)
endif()


## Depencies
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::common
)

include(external-spirit-x3)

## Project Depend Includes
include_directories(${SPIRIT_X3_INCLUDE_DIR})
#include_directories(${GSL_INCLUDE_DIR})

add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} eda)
#add_dependencies(${PROJECT_NAME} gsl)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")


## doc, test suite, etc.
add_subdirectory(doc)
add_subdirectory(test)


## Install targets
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${PROJECT_NAME}
    LIBRARY  DESTINATION ${PROJECT_NAME}
    RUNTIME  DESTINATION ${PROJECT_NAME})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config
    DESTINATION share/cmake/${PROJECT_NAME}Config)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)


