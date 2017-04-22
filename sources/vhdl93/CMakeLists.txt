cmake_minimum_required(VERSION 3.6)

## EDA/VHDL93 project
project(eda_vhdl93_grammar LANGUAGES CXX)

## C++ Standards
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(LIB_SOURCES
    src/ast/bit_string_literal.cpp
    src/ast/decimal_literal.cpp
    src/ast/keyword_token.cpp
    src/ast/operator_token.cpp
    #src/new_operator.cpp
    src/grammar.cpp
    src/literal.cpp
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

# limit gcc template error depth printing
target_compile_options(${PROJECT_NAME}
    PRIVATE -ftemplate-backtrace-limit=1) # -ferror-limit=1)

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


## test suite
add_subdirectory(test)


## API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doc/doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()


## Install targets
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE  DESTINATION ${PROJECT_NAME}
    LIBRARY  DESTINATION ${PROJECT_NAME}
    RUNTIME  DESTINATION ${PROJECT_NAME})  # This is for Windows
install(DIRECTORY include/ DESTINATION include)

install(EXPORT ${PROJECT_NAME}Config
    DESTINATION share/cmake/${PROJECT_NAME}Config)

export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)


