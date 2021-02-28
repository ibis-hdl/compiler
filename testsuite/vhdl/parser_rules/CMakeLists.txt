################################################################################
## EDA/testsuite VHDL parser project
##
## file: testsuite/vhdl/parser/CMakeLists.txt
################################################################################

project(testrunner_vhdl_parser_rules LANGUAGES CXX)


add_executable(${PROJECT_NAME} "")


# The argument is the top level directory of the test directories of 'test_case'
add_test(NAME test_vhdl_parser_rule
    COMMAND 
        ${PROJECT_NAME} -- 
        --source-dir=${PROJECT_SOURCE_DIR}
        --destination-dir=${PROJECT_BINARY_DIR}
        --input-extension=.input
    #    --write-extension=.expected
        --write-extension=.result    
)


target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        eda::vhdl_parser
        testsuite::common
        testsuite::vhdl_rules
        Boost::system
        Boost::filesystem
        Boost::locale
        Boost::unit_test_framework 
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


if(DEVELOPER_EXTERNAL_BOOST_SPIRIT_X3)
    add_dependencies(${PROJECT_NAME} boost-spirit-x3)
endif()
if(DEVELOPER_EXTERNAL_BOOST_UTF)
    add_dependencies(${PROJECT_NAME} boost-utf)
endif()


target_sources(${PROJECT_NAME} 
    PRIVATE
        src/common/test_vhdl_parser.cpp
        # concrete test cases
        src/abstract_literal_test.cpp
        src/actual_part_test.cpp
        src/aggregate_test.cpp
        src/alias_declaration_test.cpp
        src/allocator_test.cpp
        src/architecture_body_test.cpp
        src/assertion_test.cpp
        src/association_list_test.cpp
        src/attribute_name_test.cpp
        src/attribute_specification_test.cpp
        src/based_literal_test.cpp
        src/binding_indication_test.cpp
        src/bit_string_literal_test.cpp
        src/block_configuration_test.cpp
        src/block_header_test.cpp
        src/block_statement_test.cpp
        src/case_statement_test.cpp
        src/character_literal_test.cpp
        src/choices_test.cpp
        src/component_configuration_test.cpp
        src/component_declaration_test.cpp
        src/component_instantiation_statement_test.cpp
        src/component_specification_test.cpp
        src/concurrent_assertion_statement_test.cpp
        src/conditional_signal_assignment_test.cpp
        src/configuration_declaration_test.cpp
        src/configuration_specification_test.cpp
        src/constant_declaration_test.cpp
        src/constrained_array_definition_test.cpp
        src/constraint_test.cpp
        src/context_clause_test.cpp
        src/decimal_literal_test.cpp
        src/disconnection_specification_test.cpp
        src/discrete_range_test.cpp
        src/element_declaration_test.cpp
        src/entity_aspect_test.cpp
        src/entity_declaration_test.cpp
        src/enumeration_type_definition_test.cpp
        src/exit_statement_test.cpp
        src/expression_test.cpp
        src/factor_test.cpp
        src/file_declaration_test.cpp
        src/file_open_information_test.cpp
        src/formal_part_test.cpp
        src/function_call_test.cpp
        src/generate_statement_test.cpp
        src/generic_clause_test.cpp
        src/generic_map_aspect_test.cpp
        src/group_declaration_test.cpp
        src/group_template_declaration_test.cpp
        src/identifier_test.cpp
        src/identifier_list_test.cpp
        src/if_statement_test.cpp
        src/index_constraint_test.cpp
        src/index_subtype_definition_test.cpp
        src/indexed_name_test.cpp
        src/integer_test.cpp
        src/interface_constant_declaration_test.cpp
        src/interface_file_declaration_test.cpp
        src/interface_signal_declaration_test.cpp
        src/interface_variable_declaration_test.cpp
        src/library_clause_test.cpp
        src/literal_test.cpp
        src/loop_statement_test.cpp
        src/name_test.cpp
        src/next_statement_test.cpp
        src/numeric_literal_test.cpp
        src/package_body_test.cpp
        src/package_declaration_test.cpp
        src/parameter_specification_test.cpp
        src/physical_literal_test.cpp
        src/physical_type_definition_test.cpp
        src/port_clause_test.cpp
        src/port_map_aspect_test.cpp
        src/primary_test.cpp
        src/primary_unit_declaration_test.cpp
        src/procedure_call_test.cpp
        src/process_statement_test.cpp
        src/qualified_expression_test.cpp
        src/range_constraint_test.cpp
        src/record_type_definition_test.cpp
        src/relation_test.cpp
        src/return_statement_test.cpp
        src/secondary_unit_declaration_test.cpp
        src/selected_signal_assignment_test.cpp
        src/sequential_statement_test.cpp
        src/shift_expression_test.cpp
        src/signal_assignment_statement_test.cpp
        src/signal_declaration_test.cpp
        src/signal_list_test.cpp
        src/simple_expression_test.cpp
        src/slice_name_test.cpp
        src/string_literal_test.cpp
        src/subprogram_body_test.cpp
        src/subprogram_specification_test.cpp
        src/subtype_declaration_test.cpp
        src/subtype_indication_test.cpp
        src/term_test.cpp
        src/type_conversion_test.cpp
        src/type_declaration_test.cpp
        src/type_definition_test.cpp
        src/unconstrained_array_definition_test.cpp
        src/use_clause_test.cpp
        src/variable_assignment_statement_test.cpp
        src/variable_declaration_test.cpp
        src/wait_statement_test.cpp
        src/waveform_test.cpp
)



set_source_files_properties(src/common/test_vhdl_parser.cpp
    APPEND PROPERTIES 
        COMPILE_DEFINITIONS "BOOST_TEST_DYN_LINK" 
)


if (EDA_ENABLE_PCH)
    target_precompile_headers(${PROJECT_NAME} 
        PRIVATE 
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl_parser/detail/pch.hpp>
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/testsuite/vhdl_parser/detail/pch_prj.hpp>
    )
endif()


target_include_directories(${PROJECT_NAME} 
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_UTF_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
)


target_compile_definitions(${PROJECT_NAME} 
    PRIVATE
        # don't allow automatically select which libraries to link against    
        $<$<CXX_COMPILER_ID:MSVC>:BOOST_ALL_NO_LIB>
)


##
# Generate the TestMatrix
# - python3 is required, also PrettyTable
find_package(PythonInterp 3 REQUIRED)
#find_package(PythonLibs 3 REQUIRED)

set(TEST_MATRIX_GENERATOR        ${PROJECT_SOURCE_DIR}/utils/gen_test_matrix.py)
set(TEST_MATRIX_GENERATOR_TARGET ${PROJECT_SOURCE_DIR}/parser_test_matrix.rst)
file(GLOB_RECURSE TEST_CASE_FILES_DEPENDENCY
    LIST_DIRECTORIES true
    "${PROJECT_SOURCE_DIR}/test_case/" "*.expected"
)
add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${PYTHON_EXECUTABLE} ${TEST_MATRIX_GENERATOR} ${PROJECT_SOURCE_DIR} > ${TEST_MATRIX_GENERATOR_TARGET}
    DEPENDS ${TEST_MATRIX_GENERATOR} ${TEST_CASE_FILES_DEPENDENCY}
    BYPRODUCT ${TEST_MATRIX_GENERATOR_TARGET}
    COMMENT "Generate VHDL Parser TestCase Matrix (RST)"
)

set_source_files_properties(
    ${TEST_MATRIX_GENERATOR_TARGET}
    PROPERTIES GENERATED TRUE
)

