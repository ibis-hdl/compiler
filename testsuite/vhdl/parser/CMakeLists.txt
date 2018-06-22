################################################################################
## testsuite/vhdl/parser/CMakeLists.txt
################################################################################

################################################################################
## VHDL C++ TestSuite for the parser 
################################################################################

project(testrunner_vhdl_parser LANGUAGES CXX)


set(TEST_COMMON_SOURCES
    rules.cpp
    data_set.cpp
    test_vhdl_parser.cpp
    testing_util.cpp
)

set(PARSERTEST_SOURCES#_DEV
    ${TEST_COMMON_SOURCES}
    parser_test/block_statement_test.cpp
    parser_test/generate_statement_test.cpp
    parser_test/association_list_test.cpp
)

set(PARSERTEST_SOURCES
    ${TEST_COMMON_SOURCES}
    parser_test/abstract_literal_test.cpp
    parser_test/actual_part_test.cpp
    parser_test/aggregate_test.cpp
    parser_test/alias_declaration_test.cpp
    parser_test/allocator_test.cpp
    parser_test/assertion_test.cpp
    parser_test/association_list_test.cpp
    parser_test/attribute_name_test.cpp
    parser_test/attribute_specification_test.cpp
    parser_test/based_literal_test.cpp
    parser_test/binding_indication_test.cpp
    parser_test/bit_string_literal_test.cpp
    parser_test/block_configuration_test.cpp
    parser_test/block_header_test.cpp
    parser_test/block_statement_test.cpp
    parser_test/case_statement_test.cpp
    parser_test/character_literal_test.cpp
    parser_test/choices_test.cpp
    parser_test/component_configuration_test.cpp
    parser_test/component_declaration_test.cpp
    parser_test/component_instantiation_statement_test.cpp
    parser_test/component_specification_test.cpp
    parser_test/concurrent_assertion_statement_test.cpp
    parser_test/conditional_signal_assignment_test.cpp
    parser_test/configuration_declaration_test.cpp
    parser_test/configuration_specification_test.cpp
    parser_test/constant_declaration_test.cpp
    parser_test/constrained_array_definition_test.cpp
    parser_test/constraint_test.cpp
    parser_test/context_clause_test.cpp
    parser_test/decimal_literal_test.cpp
    parser_test/disconnection_specification_test.cpp
    parser_test/discrete_range_test.cpp
    parser_test/element_declaration_test.cpp
    parser_test/entity_aspect_test.cpp
    parser_test/entity_declaration_test.cpp
    parser_test/enumeration_type_definition_test.cpp
    parser_test/exit_statement_test.cpp
    parser_test/expression_test.cpp
    parser_test/factor_test.cpp
    parser_test/file_declaration_test.cpp
    parser_test/file_open_information_test.cpp
    parser_test/formal_part_test.cpp
    parser_test/function_call_test.cpp
    parser_test/generate_statement_test.cpp
    parser_test/generic_clause_test.cpp
    parser_test/generic_map_aspect_test.cpp
    parser_test/group_declaration_test.cpp
    parser_test/group_template_declaration_test.cpp
    parser_test/identifier_test.cpp
    parser_test/identifier_list_test.cpp
    parser_test/if_statement_test.cpp
    parser_test/index_constraint_test.cpp
    parser_test/index_subtype_definition_test.cpp
    parser_test/indexed_name_test.cpp
    parser_test/integer_test.cpp
    parser_test/interface_constant_declaration_test.cpp
    parser_test/interface_file_declaration_test.cpp
    parser_test/interface_signal_declaration_test.cpp
    parser_test/interface_variable_declaration_test.cpp
    parser_test/library_clause_test.cpp
    parser_test/literal_test.cpp
    parser_test/loop_statement_test.cpp
    parser_test/name_test.cpp
    parser_test/next_statement_test.cpp
    parser_test/numeric_literal_test.cpp
    parser_test/package_body_test.cpp
    parser_test/package_declaration_test.cpp
    parser_test/parameter_specification_test.cpp
    parser_test/physical_literal_test.cpp
    parser_test/physical_type_definition_test.cpp
    parser_test/port_clause_test.cpp
    parser_test/port_map_aspect_test.cpp
    parser_test/primary_test.cpp
    parser_test/primary_unit_declaration_test.cpp
    parser_test/procedure_call_test.cpp
    parser_test/process_statement_test.cpp
    parser_test/qualified_expression_test.cpp
    parser_test/range_constraint_test.cpp
    parser_test/record_type_definition_test.cpp
    parser_test/relation_test.cpp
    parser_test/return_statement_test.cpp
    parser_test/secondary_unit_declaration_test.cpp
    parser_test/selected_signal_assignment_test.cpp
    parser_test/sequential_statement_test.cpp
    parser_test/shift_expression_test.cpp
    parser_test/signal_assignment_statement_test.cpp
    parser_test/signal_declaration_test.cpp
    parser_test/signal_list_test.cpp
    parser_test/simple_expression_test.cpp
    parser_test/slice_name_test.cpp
    parser_test/string_literal_test.cpp
    parser_test/subprogram_body_test.cpp
    parser_test/subprogram_specification_test.cpp
    parser_test/subtype_declaration_test.cpp
    parser_test/subtype_indication_test.cpp
    parser_test/term_test.cpp
    parser_test/type_conversion_test.cpp
    parser_test/type_declaration_test.cpp
    parser_test/type_definition_test.cpp
    parser_test/unconstrained_array_definition_test.cpp
    parser_test/use_clause_test.cpp
    parser_test/variable_assignment_statement_test.cpp
    parser_test/variable_declaration_test.cpp
    parser_test/wait_statement_test.cpp
    parser_test/waveform_test.cpp

)

add_executable(${PROJECT_NAME} ${PARSERTEST_SOURCES})


# adjust include path
target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)


target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

# limit gcc/clang template error depth printing
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -ftemplate-backtrace-limit=0
    )
endif()


# increase limit especially for clang recursive template instantiation,
# otherwise exceedes maximum depth of 512
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE 
        -ftemplate-depth=1024)
endif()


##
# Boost.Org's Spirit.X3 newer version is required from local clone
add_dependencies(${PROJECT_NAME} boost-spirit-x3)

# Boost.Org depend includes
include_directories(${SPIRIT_X3_INCLUDE_DIR})

# parser with Spirit.X3 DEBUG
set(EDA_VHDL_PARSER_DEBUG OFF CACHE BOOL "debug printer of spirit.x3 parser tree")
if("${EDA_VHDL_PARSER_DEBUG}")
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE BOOST_SPIRIT_X3_DEBUG=1)
endif()


##
# Boost.Org UTF
find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    eda::vhdl_parser
    eda::common # FixMe: shouldn't this depency propagated by eda::vhdl_grammar?
    Boost::system
    Boost::filesystem
)

# Since Boost.Test does not expose the argc/argv values outside of the
# test case we have to provide the path to the test case files manualy
configure_file(
    ${PROJECT_SOURCE_DIR}/include/testsuite/vhdl_parser/test_case_path.hpp.in
    ${PROJECT_BINARY_DIR}/include/testsuite/vhdl_parser/test_case_path.hpp
    @ONLY)


## 
# CMake/CTest
# The argument is the top level directory of the test directories of 'test_case'
add_test(NAME test_vhdl_parser
    COMMAND ${PROJECT_NAME} -- ${PROJECT_SOURCE_DIR}
)



##
# Generate the TestMatrix
# - python3 is required, also PrettyTable
find_package( PythonInterp 3 REQUIRED )
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
