cmake_minimum_required(VERSION 3.8)

## EDA/VHDL project
project(eda_vhdl_parser LANGUAGES CXX)


## Cotire (compile time reducer) https://github.com/sakra/cotire
include(cotire)


## C++ Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(LIB_SOURCES
    src/ast/bit_string_literal.cpp
    src/ast/decimal_literal.cpp
    src/ast/keyword_token.cpp
    src/ast/operator_token.cpp
    src/error_handler.cpp
    src/ast_printer.cpp

    #src/expression_parse.cpp # hot fix for playground vhdl_expression_eval
)

add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
add_library(eda::vhdl_parser ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)


target_compile_options(${PROJECT_NAME}
    PRIVATE -Wall -Wextra)


# limit gcc template error depth printing, aslo other options
target_compile_options(${PROJECT_NAME} PRIVATE
    -ftemplate-backtrace-limit=1
)


# increase limit for clang recursive template instantiation
# otherwise exceedes maximum depth of 256
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -ftemplate-depth=1024)
endif()


## Boost.Org 
# Spirit X3 is required for the parser - we are working on developer branch. 
# Nevertheless Spirit self depends on other headers, e..g boost.range
find_package(Boost)


# Spirit.X3 Parser debugging: show warnings about dereferencing type-punned 
# pointer will break strict-aliasing
# rules [-Wstrict-aliasing] (spirit.x3 1.64 e.g.)
set(EDA_VHDL_PARSER_DEBUG OFF CACHE BOOL "debug printer of spirit.x3 parser tree")

if("${EDA_VHDL_PARSER_DEBUG}")
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
include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${GSL_INCLUDE_DIR})

add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} eda)
#add_dependencies(${PROJECT_NAME} gsl)

#set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_d")


# FAILED with Boost.PP
#cotire(${PROJECT_NAME})


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


