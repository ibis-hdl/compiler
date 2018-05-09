cmake_minimum_required(VERSION 3.8)

## EDA/VHDL project TestBench
project(testrunner_vhdl93_parser LANGUAGES CXX)


## Cotire (compile time reducer) https://github.com/sakra/cotire
include(cotire)


set(PARSERTEST_SOURCES_OLD
    test_vhdl93_parser.cpp
    data_set.cpp
    #parser_xxx.cpp parser_xxx_inst.cpp
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
)

set(PARSERTEST_SOURCES
    test_vhdl93_parser.cpp
    data_set.cpp
    parser_test/abstract_literal_parsertest.cpp parser_test/abstract_literal_grammar.cpp
    parser_test/aggregate_parsertest.cpp parser_test/aggregate_grammar.cpp
    parser_test/assertion_parsertest.cpp parser_test/assertion_grammar.cpp
    parser_test/association_list_parsertest.cpp parser_test/association_list_grammar.cpp
    parser_test/attribute_name_parsertest.cpp parser_test/attribute_name_grammar.cpp
    parser_test/attribute_specification_parsertest.cpp parser_test/attribute_specification_grammar.cpp
    parser_test/based_literal_parsertest.cpp parser_test/based_literal_grammar.cpp
    parser_test/binding_indication_parsertest.cpp parser_test/binding_indication_grammar.cpp
    parser_test/bit_string_literal_parsertest.cpp parser_test/bit_string_literal_grammar.cpp
    parser_test/case_statement_parsertest.cpp parser_test/case_statement_grammar.cpp
    parser_test/character_literal_parsertest.cpp parser_test/character_literal_grammar.cpp
    parser_test/choices_parsertest.cpp parser_test/choices_grammar.cpp
    parser_test/component_specification_parsertest.cpp parser_test/component_specification_grammar.cpp
    parser_test/concurrent_assertion_statement_parsertest.cpp parser_test/concurrent_assertion_statement_grammar.cpp
    parser_test/conditional_signal_assignment_parsertest.cpp parser_test/conditional_signal_assignment_grammar.cpp
    parser_test/constant_declaration_parsertest.cpp parser_test/constant_declaration_grammar.cpp
    parser_test/constrained_array_definition_parsertest.cpp parser_test/constrained_array_definition_grammar.cpp
    parser_test/constraint_parsertest.cpp parser_test/constraint_grammar.cpp
    parser_test/context_clause_parsertest.cpp parser_test/context_clause_grammar.cpp
    parser_test/decimal_literal_parsertest.cpp parser_test/decimal_literal_grammar.cpp
    parser_test/disconnection_specification_parsertest.cpp parser_test/disconnection_specification_grammar.cpp
    parser_test/discrete_range_parsertest.cpp parser_test/discrete_range_grammar.cpp
    parser_test/element_declaration_parsertest.cpp parser_test/element_declaration_grammar.cpp
    parser_test/entity_aspect_parsertest.cpp parser_test/entity_aspect_grammar.cpp
    parser_test/enumeration_type_definition_parsertest.cpp parser_test/enumeration_type_definition_grammar.cpp
    parser_test/exit_statement_parsertest.cpp parser_test/exit_statement_grammar.cpp
    parser_test/expression_parsertest.cpp parser_test/expression_grammar.cpp
    parser_test/expression_failure_parsertest.cpp
    parser_test/factor_parsertest.cpp parser_test/factor_grammar.cpp
    parser_test/file_declaration_parsertest.cpp parser_test/file_declaration_grammar.cpp
    parser_test/file_open_information_parsertest.cpp parser_test/file_open_information_grammar.cpp
    parser_test/floating_type_definition_parsertest.cpp parser_test/floating_type_definition_grammar.cpp
    parser_test/function_call_parsertest.cpp parser_test/function_call_grammar.cpp
    parser_test/generic_clause_parsertest.cpp parser_test/generic_clause_grammar.cpp
    parser_test/generic_map_aspect_parsertest.cpp parser_test/generic_map_aspect_grammar.cpp
    parser_test/group_declaration_parsertest.cpp parser_test/group_declaration_grammar.cpp
    parser_test/group_template_declaration_parsertest.cpp parser_test/group_template_declaration_grammar.cpp
    parser_test/identifier_parsertest.cpp parser_test/identifier_grammar.cpp
    parser_test/identifier_failure_parsertest.cpp
    parser_test/identifier_list_parsertest.cpp parser_test/identifier_list_grammar.cpp
    parser_test/if_statement_parsertest.cpp parser_test/if_statement_grammar.cpp
    parser_test/index_constraint_parsertest.cpp parser_test/index_constraint_grammar.cpp
    parser_test/index_subtype_definition_parsertest.cpp parser_test/index_subtype_definition_grammar.cpp
    parser_test/indexed_name_parsertest.cpp parser_test/indexed_name_grammar.cpp
    parser_test/integer_parsertest.cpp parser_test/integer_grammar.cpp
    parser_test/integer_failure_parsertest.cpp
    parser_test/integer_type_definition_parsertest.cpp parser_test/integer_type_definition_grammar.cpp
    parser_test/interface_constant_declaration_parsertest.cpp parser_test/interface_constant_declaration_grammar.cpp
    parser_test/interface_file_declaration_parsertest.cpp parser_test/interface_file_declaration_grammar.cpp
    parser_test/interface_signal_declaration_parsertest.cpp parser_test/interface_signal_declaration_grammar.cpp
    parser_test/interface_variable_declaration_parsertest.cpp parser_test/interface_variable_declaration_grammar.cpp
    parser_test/library_clause_parsertest.cpp parser_test/library_clause_grammar.cpp
    parser_test/literal_parsertest.cpp parser_test/literal_grammar.cpp
    parser_test/loop_statement_parsertest.cpp parser_test/loop_statement_grammar.cpp
    parser_test/name_parsertest.cpp parser_test/name_grammar.cpp
    parser_test/next_statement_parsertest.cpp parser_test/next_statement_grammar.cpp
    parser_test/numeric_literal_parsertest.cpp parser_test/numeric_literal_grammar.cpp
    parser_test/parameter_specification_parsertest.cpp parser_test/parameter_specification_grammar.cpp
    parser_test/physical_literal_parsertest.cpp parser_test/physical_literal_grammar.cpp
    parser_test/physical_literal_failure_parsertest.cpp
    parser_test/physical_type_definition_parsertest.cpp parser_test/physical_type_definition_grammar.cpp
    parser_test/port_clause_parsertest.cpp parser_test/port_clause_grammar.cpp
    parser_test/port_map_aspect_parsertest.cpp parser_test/port_map_aspect_grammar.cpp
    parser_test/primary_parsertest.cpp parser_test/primary_grammar.cpp
    parser_test/primary_unit_declaration_parsertest.cpp parser_test/primary_unit_declaration_grammar.cpp
    parser_test/range_parsertest.cpp parser_test/range_grammar.cpp
    parser_test/record_type_definition_parsertest.cpp parser_test/record_type_definition_grammar.cpp
    parser_test/relation_parsertest.cpp parser_test/relation_grammar.cpp
    parser_test/return_statement_parsertest.cpp parser_test/return_statement_grammar.cpp
    parser_test/secondary_unit_declaration_parsertest.cpp parser_test/secondary_unit_declaration_grammar.cpp
    parser_test/selected_signal_assignment_parsertest.cpp parser_test/selected_signal_assignment_grammar.cpp
    parser_test/sequential_statement_parsertest.cpp parser_test/sequential_statement_grammar.cpp
    parser_test/shift_expression_parsertest.cpp parser_test/shift_expression_grammar.cpp
    parser_test/signal_assignment_statement_parsertest.cpp parser_test/signal_assignment_statement_grammar.cpp
    parser_test/signal_declaration_parsertest.cpp parser_test/signal_declaration_grammar.cpp
    parser_test/signal_list_parsertest.cpp parser_test/signal_list_grammar.cpp
    parser_test/simple_expression_parsertest.cpp parser_test/simple_expression_grammar.cpp
    parser_test/slice_name_parsertest.cpp parser_test/slice_name_grammar.cpp
    parser_test/string_literal_parsertest.cpp parser_test/string_literal_grammar.cpp
    parser_test/subprogram_body_parsertest.cpp parser_test/subprogram_body_grammar.cpp
    parser_test/subprogram_specification_parsertest.cpp parser_test/subprogram_specification_grammar.cpp
    parser_test/subtype_declaration_parsertest.cpp parser_test/subtype_declaration_grammar.cpp
    parser_test/subtype_indication_parsertest.cpp parser_test/subtype_indication_grammar.cpp
    parser_test/term_parsertest.cpp parser_test/term_grammar.cpp
    parser_test/type_conversion_parsertest.cpp parser_test/type_conversion_grammar.cpp
    parser_test/type_declaration_parsertest.cpp parser_test/type_declaration_grammar.cpp
    parser_test/type_declaration_failure_parsertest.cpp
    parser_test/type_definition_parsertest.cpp parser_test/type_definition_grammar.cpp
    parser_test/unconstrained_array_definition_parsertest.cpp parser_test/unconstrained_array_definition_grammar.cpp
    parser_test/use_clause_parsertest.cpp parser_test/use_clause_grammar.cpp
    parser_test/variable_assignment_statement_parsertest.cpp parser_test/variable_assignment_statement_grammar.cpp
    parser_test/variable_declaration_parsertest.cpp parser_test/variable_declaration_grammar.cpp
    parser_test/wait_statement_parsertest.cpp parser_test/wait_statement_grammar.cpp
    parser_test/waveform_parsertest.cpp parser_test/waveform_grammar.cpp
    #parser_test/xxx_signature_parsertest.cpp parser_test/xxx_signature_grammar.cpp
)

add_executable(${PROJECT_NAME} ${PARSERTEST_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -ftemplate-backtrace-limit=0
)

# adjust include path
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

#add_dependencies(${PROJECT_NAME} boost-spirit-x3)
#add_dependencies(${PROJECT_NAME} gsl)


# increase limit for clang recursive template instantiation
# otherwise exceedes maximum depth of 256
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PRIVATE -ftemplate-depth=512)
endif()


## 
# X3 Parser DEBUG
# - show warnings about dereferencing type-punned pointer will break strict-aliasing
#   rules [-Wstrict-aliasing] (spirit.x3 1.64 e.g.)
if("${EDA_VHDL_PARSER_DEBUG}")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG=1)
endif()


##
# Boost Requirements
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


##
# COTIRE

# disable PCH date-time check, Boost.Spirit uses __DATE__ and __TIME__ 
# [Can cotire be made to work properly with Boost?](
#  https://stackoverflow.com/questions/44350219/can-cotire-be-made-to-work-properly-with-boost)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wno-pch-date-time
)

# FixMe: FAILED with Boost.PP and others
set_target_properties(${PROJECT_NAME} PROPERTIES
    COTIRE_PREFIX_HEADER_IGNORE_PATH "${Boost_INCLUDE_DIRS}/boost;${SPIRIT_X3_INCLUDE_DIR}"
    #COTIRE_PREFIX_HEADER_IGNORE_PATH "${Boost_INCLUDE_DIRS}/boost"
    #COTIRE_PREFIX_HEADER_INCLUDE_PATH eda::vhdl_parser
)

#cotire(${PROJECT_NAME})


## 
# CMake/CTest
# The argument is the top level directory of the test directories of 'test_case'
add_test(NAME test_vhdl_parser
    COMMAND ${PROJECT_NAME} -- ${CMAKE_CURRENT_SOURCE_DIR}
)

# Since Boost.Test does not expose the argc/argv values outside of the
# test case we have to provide the path to the test case files manualy
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/test_case_path.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/test_case_path.hpp
    @ONLY)


##
# Generate the TestMatrix
# - python3 is required, also PrettyTable
find_package( PythonInterp 3 REQUIRED )
#find_package(PythonLibs 3 REQUIRED)

set(TEST_MATRIX_GENERATOR        ${CMAKE_CURRENT_SOURCE_DIR}/../utils/gen_test_matrix.py)
set(TEST_MATRIX_GENERATOR_TARGET ${CMAKE_CURRENT_SOURCE_DIR}/test_matrix.rst)
file(GLOB_RECURSE TEST_CASE_FILES
    LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/test_case/" "*.expected"
)
add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${PYTHON_EXECUTABLE} ${TEST_MATRIX_GENERATOR} ${CMAKE_CURRENT_SOURCE_DIR} > ${TEST_MATRIX_GENERATOR_TARGET}
    DEPENDS ${TEST_MATRIX_GENERATOR} ${TEST_CASE_FILES}
    BYPRODUCT ${TEST_MATRIX_GENERATOR_TARGET}
    COMMENT "Generate VHDL TestCase Matrix (RST)"
)

set_source_files_properties(
    ${TEST_MATRIX_GENERATOR_TARGET}
    PROPERTIES GENERATED TRUE
)


## 
# Misc
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

