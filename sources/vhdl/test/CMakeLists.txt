cmake_minimum_required(VERSION 3.8)

## EDA/VHDL project TestBench
project(testrunner_vhdl93_parser LANGUAGES CXX)


## Cotire (compile time reducer) https://github.com/sakra/cotire
include(cotire)


set(BIN_SOURCES
    data_set.cpp
    #parser_xxx.cpp
    parser_aspect.cpp
    parser_clause.cpp
    parser_concurrent_statements.cpp
    parser_declaration.cpp
    parser_design_unit.cpp
    parser_entities.cpp
    parser_expression.cpp
    parser_file.cpp
    parser_interface.cpp
    parser_literals.cpp
    parser_names.cpp
    parser_production.cpp
    parser_specifications.cpp
    parser_statement.cpp
    parser_subprogram.cpp
    parser_type.cpp
    test_vhdl93_parser.cpp
)

add_executable(${PROJECT_NAME} ${BIN_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)
target_compile_options(${PROJECT_NAME} PRIVATE
    -ftemplate-backtrace-limit=1
)

# increase limit for clang recursive template instantiation
# otherwise exceedes maximum depth of 256
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -ftemplate-depth=1024)
endif()


## X3 Parser DEBUG
#  show warnings about dereferencing type-punned pointer will break strict-aliasing
#  rules [-Wstrict-aliasing] (spirit.x3 1.64 e.g.)
if("${EDA_VHDL_PARSER_DEBUG}")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG=1)
endif()


## since boost.test does not expose the argc/argv values outside of the
## test case we have to provide the path to the test case files manualy
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/test_case_path.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/test_case_path.hpp
    @ONLY)

# and adjust include path
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)


#add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} gsl)


## Boost Requirements
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})

add_library(boost-filesystem SHARED IMPORTED)
set_property(TARGET boost-filesystem PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost-filesystem PROPERTY IMPORTED_LOCATION ${Boost_FILESYSTEM_LIBRARY})

add_library(boost-system SHARED IMPORTED)
set_property(TARGET boost-system PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS})
set_property(TARGET boost-system PROPERTY IMPORTED_LOCATION ${Boost_SYSTEM_LIBRARY})


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl_grammar?
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)


#cotire(${PROJECT_NAME})


add_test(NAME test_vhdl_parser
    COMMAND ${PROJECT_NAME} -- ${CMAKE_CURRENT_SOURCE_DIR}
)


## Generate the TestMatrix
set(TEST_MATRIX_GENERATOR        ${CMAKE_CURRENT_SOURCE_DIR}/../utils/gen_test_matrix.py)
set(TEST_MATRIX_GENERATOR_TARGET ${CMAKE_CURRENT_SOURCE_DIR}/test_matrix.rst)
file(GLOB_RECURSE TEST_CASE_FILES
    LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/test_case/" "*.expected"
)
add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${TEST_MATRIX_GENERATOR} ${CMAKE_CURRENT_SOURCE_DIR} > ${TEST_MATRIX_GENERATOR_TARGET}
    DEPENDS ${TEST_MATRIX_GENERATOR} ${TEST_CASE_FILES}
    BYPRODUCT ${TEST_MATRIX_GENERATOR_TARGET}
    COMMENT "Generate VHDL TestCase Matrix (RST)"
)

set_source_files_properties(
    ${TEST_MATRIX_GENERATOR_TARGET}
    PROPERTIES GENERATED TRUE
)


add_executable(make_gold EXCLUDE_FROM_ALL make_gold.cpp)
set_target_properties(make_gold PROPERTIES CXX_STANDARD 17)
set_target_properties(make_gold PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(make_gold PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
target_link_libraries(make_gold
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl_grammar?
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

