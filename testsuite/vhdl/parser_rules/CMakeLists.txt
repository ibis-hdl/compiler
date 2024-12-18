################################################################################
## IBIS/testsuite VHDL parser project
##
## file: testsuite/vhdl/parser/CMakeLists.txt
################################################################################

project(testrunner_vhdl_parser_rules
    VERSION "${ibis_version}"
    DESCRIPTION "${ibis_description}"
    HOMEPAGE_URL "${ibis_homepage}"
    LANGUAGES CXX
)
message(STATUS
    "project ${CMAKE_PROJECT_NAME}/${PROJECT_NAME} @v${ibis_version}: "
    "${ibis_description} [${ibis_homepage}]")


add_executable(${PROJECT_NAME})


# Variables used to configure ctest project, also compile time builtin settings
set(TESTSUITE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/test_data")
set(TESTSUITE_INPUT_EXTENSION ".input")
set(TESTSUITE_EXPECTED_EXTENSION ".expected")
set(TESTSUITE_DESTINATION_DIR "${CMAKE_BINARY_DIR}/testsuite_result/vhdl/parser_rules")
set(TESTSUITE_OUTPUT_EXTENSION ".result")

add_test(NAME test_vhdl_parser_rules
    COMMAND
        ${PROJECT_NAME} --log_level=error --
        --source-dir=${TESTSUITE_SOURCE_DIR}
        --input-extension=${TESTSUITE_INPUT_EXTENSION}
        --expected-extension=${TESTSUITE_EXPECTED_EXTENSION}
        --destination-dir=${TESTSUITE_DESTINATION_DIR}
        --output-extension=${TESTSUITE_OUTPUT_EXTENSION}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ibis::vhdl
    PRIVATE
        testsuite::util
        Boost::headers
        Boost::system
        Boost::locale
        Boost::unit_test_framework
        # cope with "fatal error LNK2011: precompiled object not linked in"
        #"$<$<CXX_COMPILER_ID:MSVC>:ibis_pch>"
)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-v")


configure_file(
    ${PROJECT_SOURCE_DIR}/src/dataset_builtin.cpp.in
    ${PROJECT_BINARY_DIR}/src/dataset_builtin.cpp
    @ONLY
)
configure_file(
    ${PROJECT_SOURCE_DIR}/src/failure_diagnostic_fixture_builtin.cpp.in
    ${PROJECT_BINARY_DIR}/src/failure_diagnostic_fixture_builtin.cpp
    @ONLY
)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/test_vhdl_parser.cpp
        src/failure_diagnostic_fixture.cpp ${PROJECT_BINARY_DIR}/src/failure_diagnostic_fixture_builtin.cpp
        src/dataset.cpp ${PROJECT_BINARY_DIR}/src/dataset_builtin.cpp
        src/rules.cpp
        # concrete test cases
        src/test/abstract_literal_test.cpp
        src/test/actual_part_test.cpp
        src/test/aggregate_test.cpp
        src/test/alias_declaration_test.cpp
        src/test/allocator_test.cpp
        src/test/architecture_body_test.cpp
        src/test/assertion_test.cpp
        src/test/association_list_test.cpp
        src/test/attribute_name_test.cpp
        src/test/attribute_specification_test.cpp # fatal error: in "parser_rule/attribute_specification/_1": std::length_error: basic_string::_M_create
        src/test/based_literal_test.cpp
        src/test/binding_indication_test.cpp
        src/test/bit_string_literal_test.cpp
        src/test/block_configuration_test.cpp
        src/test/block_header_test.cpp
        src/test/block_statement_test.cpp
        src/test/case_statement_test.cpp
        src/test/character_literal_test.cpp
        src/test/choices_test.cpp
        src/test/component_configuration_test.cpp
        src/test/component_declaration_test.cpp
        src/test/component_instantiation_statement_test.cpp
        src/test/component_specification_test.cpp
        src/test/concurrent_assertion_statement_test.cpp
        src/test/conditional_signal_assignment_test.cpp
        src/test/configuration_declaration_test.cpp
        src/test/configuration_specification_test.cpp
        src/test/constant_declaration_test.cpp
        src/test/constrained_array_definition_test.cpp
        src/test/constraint_test.cpp
        src/test/context_clause_test.cpp
        src/test/decimal_literal_test.cpp
        src/test/disconnection_specification_test.cpp
        src/test/discrete_range_test.cpp
        src/test/element_declaration_test.cpp
        src/test/entity_aspect_test.cpp
        src/test/entity_declaration_test.cpp
        src/test/enumeration_type_definition_test.cpp
        src/test/exit_statement_test.cpp
        src/test/expression_test.cpp
        src/test/factor_test.cpp
        src/test/file_declaration_test.cpp
        src/test/file_open_information_test.cpp
        src/test/formal_part_test.cpp
        src/test/function_call_test.cpp
        src/test/generate_statement_test.cpp
        src/test/generic_clause_test.cpp
        src/test/generic_map_aspect_test.cpp
        src/test/group_declaration_test.cpp
        src/test/group_template_declaration_test.cpp
        src/test/identifier_list_test.cpp
        src/test/identifier_test.cpp
        src/test/if_statement_test.cpp
        src/test/index_constraint_test.cpp
        src/test/index_subtype_definition_test.cpp
        src/test/indexed_name_test.cpp
        src/test/integer_test.cpp
        src/test/interface_constant_declaration_test.cpp
        src/test/interface_file_declaration_test.cpp
        src/test/interface_signal_declaration_test.cpp
        src/test/interface_variable_declaration_test.cpp
        src/test/library_clause_test.cpp
        src/test/literal_test.cpp
        src/test/loop_statement_test.cpp
        src/test/name_test.cpp
        src/test/next_statement_test.cpp
        src/test/numeric_literal_test.cpp
        src/test/package_body_test.cpp
        src/test/package_declaration_test.cpp
        src/test/parameter_specification_test.cpp
        src/test/physical_literal_test.cpp
        src/test/physical_type_definition_test.cpp
        src/test/port_clause_test.cpp
        src/test/port_map_aspect_test.cpp
        src/test/primary_test.cpp
        src/test/primary_unit_declaration_test.cpp
        src/test/procedure_call_test.cpp
        src/test/process_statement_test.cpp
        src/test/qualified_expression_test.cpp
        src/test/range_constraint_test.cpp
        src/test/record_type_definition_test.cpp
        src/test/relation_test.cpp
        src/test/return_statement_test.cpp
        src/test/secondary_unit_declaration_test.cpp
        src/test/selected_signal_assignment_test.cpp
        src/test/sequential_statement_test.cpp
        src/test/shift_expression_test.cpp
        src/test/signal_assignment_statement_test.cpp
        src/test/signal_declaration_test.cpp
        src/test/signal_list_test.cpp
        src/test/simple_expression_test.cpp
        src/test/slice_name_test.cpp
        src/test/string_literal_test.cpp
        src/test/subprogram_body_test.cpp
        src/test/subprogram_specification_test.cpp
        src/test/subtype_declaration_test.cpp
        src/test/subtype_indication_test.cpp
        src/test/term_test.cpp
        src/test/type_conversion_test.cpp
        src/test/type_declaration_test.cpp
        src/test/type_definition_test.cpp
        src/test/unconstrained_array_definition_test.cpp
        src/test/use_clause_test.cpp
        src/test/variable_assignment_statement_test.cpp
        src/test/variable_declaration_test.cpp
        src/test/wait_statement_test.cpp
        src/test/waveform_test.cpp
)


#set_source_files_properties(src/test_vhdl_parser.cpp
#    APPEND PROPERTIES
#        # Failed to link Boost UTF with Windows/Clang, Linux works
#        COMPILE_DEFINITIONS "$<$<NOT:$<PLATFORM_ID:Windows>>:BOOST_TEST_DYN_LINK>"
#)

# [Boost.Test linker error by use with precompiled headers (PCH)](
#  https://stackoverflow.com/questions/66535719/boost-test-linker-error-by-use-with-precompiled-headers-pch)
set_source_files_properties(src/test_vhdl_parser.cpp
    PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)


set_property(TARGET ${PROJECT_NAME}
    PROPERTY
        JOB_POOL_COMPILE NINJA_JOBS_CORE_3072MiB
)


if(IBIS_ENABLE_CXXSTD_PCH)
    target_precompile_headers(${PROJECT_NAME} REUSE_FROM ibis_pch)
endif()


target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    SYSTEM PUBLIC
        $<BUILD_INTERFACE:${EXTERNAL_BOOST_TEST_INCLUDE_DIR}>
)
