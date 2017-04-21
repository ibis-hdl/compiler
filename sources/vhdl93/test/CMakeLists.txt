cmake_minimum_required(VERSION 3.6)

## EDA/VHDL93 project TestBench
project(test_vhdl93 LANGUAGES CXX)

set(BIN_SOURCES
    app_mock.cpp
    data_set.cpp
    basic_production_rules.cpp
    production_rules.cpp
    test_vhdl93.cpp
)

add_executable(${PROJECT_NAME} ${BIN_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)


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
    eda::vhdl93_grammar
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl93_grammar?
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
)

add_test(NAME test_vhdl93_parser
    COMMAND ${PROJECT_NAME} -- ${CMAKE_CURRENT_SOURCE_DIR}
)


## Special target no used here, maybe later to test error messages
add_executable(x3_debug EXCLUDE_FROM_ALL x3_debug.cpp)
target_link_libraries(x3_debug
    PRIVATE
    eda::vhdl93_grammar
    ${Boost_SYSTEM_LIBRARY}
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
    COMMENT "Generate VHDL93 TestCase Matrix (RST)"
)

set_source_files_properties(
    ${TEST_MATRIX_GENERATOR_TARGET}
    PROPERTIES GENERATED TRUE
)
