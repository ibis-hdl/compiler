#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_type.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>
//#include <eda/vhdl/parser/parser_config.hpp>

namespace testsuite::vhdl::parser {

// clang-format off
parser::abstract_literal_type abstract_literal() {
    return eda::vhdl::parser::abstract_literal;
}

parser::actual_part_type actual_part() {
    return eda::vhdl::parser::actual_part;
}

parser::aggregate_type aggregate() {
    return eda::vhdl::parser::aggregate;
}

parser::alias_declaration_type alias_declaration() {
    return eda::vhdl::parser::alias_declaration;
}

parser::allocator_type allocator() {
    return eda::vhdl::parser::allocator;
}

parser::architecture_body_type architecture_body() {
    return eda::vhdl::parser::architecture_body;
}

parser::assertion_type assertion() {
    return eda::vhdl::parser::assertion;
}

parser::association_list_type association_list() {
    return eda::vhdl::parser::association_list;
}

parser::attribute_name_type attribute_name() {
    return eda::vhdl::parser::attribute_name;
}

parser::attribute_specification_type attribute_specification() {
    return eda::vhdl::parser::attribute_specification;
}

parser::based_literal_type based_literal() {
    return eda::vhdl::parser::based_literal;
}

parser::binding_indication_type binding_indication() {
    return eda::vhdl::parser::binding_indication;
}

parser::bit_string_literal_type bit_string_literal() {
    return eda::vhdl::parser::bit_string_literal;
}

parser::block_configuration_type block_configuration() {
    return eda::vhdl::parser::block_configuration;
}

parser::block_header_type block_header() {
    return eda::vhdl::parser::block_header;
}

parser::block_statement_type block_statement() {
    return eda::vhdl::parser::block_statement;
}

parser::case_statement_type case_statement() {
    return eda::vhdl::parser::case_statement;
}

parser::character_literal_type character_literal() {
    return eda::vhdl::parser::character_literal;
}

parser::choices_type choices() {
    return eda::vhdl::parser::choices;
}

parser::component_configuration_type component_configuration() {
    return eda::vhdl::parser::component_configuration;
}

parser::component_declaration_type component_declaration() {
    return eda::vhdl::parser::component_declaration;
}

parser::component_instantiation_statement_type component_instantiation_statement() {
    return eda::vhdl::parser::component_instantiation_statement;
}

parser::component_specification_type component_specification() {
    return eda::vhdl::parser::component_specification;
}

parser::concurrent_assertion_statement_type concurrent_assertion_statement() {
    return eda::vhdl::parser::concurrent_assertion_statement;
}

parser::conditional_signal_assignment_type conditional_signal_assignment() {
    return eda::vhdl::parser::conditional_signal_assignment;
}

parser::configuration_declaration_type configuration_declaration() {
    return eda::vhdl::parser::configuration_declaration;
}

parser::configuration_specification_type configuration_specification() {
    return eda::vhdl::parser::configuration_specification;
}

parser::constant_declaration_type constant_declaration() {
    return eda::vhdl::parser::constant_declaration;
}

parser::constrained_array_definition_type constrained_array_definition() {
    return eda::vhdl::parser::constrained_array_definition;
}

parser::constraint_type constraint() {
    return eda::vhdl::parser::constraint;
}

parser::context_clause_type context_clause() {
    return eda::vhdl::parser::context_clause;
}

parser::decimal_literal_type decimal_literal() {
    return eda::vhdl::parser::decimal_literal;
}

parser::disconnection_specification_type disconnection_specification() {
    return eda::vhdl::parser::disconnection_specification;
}

parser::discrete_range_type discrete_range() {
    return eda::vhdl::parser::discrete_range;
}

parser::element_declaration_type element_declaration() {
    return eda::vhdl::parser::element_declaration;
}

parser::entity_aspect_type entity_aspect() {
    return eda::vhdl::parser::entity_aspect;
}

parser::entity_declaration_type entity_declaration() {
    return eda::vhdl::parser::entity_declaration;
}

parser::enumeration_type_definition_type enumeration_type_definition() {
    return eda::vhdl::parser::enumeration_type_definition;
}

parser::exit_statement_type exit_statement() {
    return eda::vhdl::parser::exit_statement;
}

parser::expression_type expression() {
    return eda::vhdl::parser::expression;
}

parser::factor_type factor() {
    return eda::vhdl::parser::factor;
}

parser::file_declaration_type file_declaration() {
    return eda::vhdl::parser::file_declaration;
}

parser::file_open_information_type file_open_information() {
    return eda::vhdl::parser::file_open_information;
}

parser::formal_part_type formal_part() {
    return eda::vhdl::parser::formal_part;
}

parser::function_call_type function_call() {
    return eda::vhdl::parser::function_call;
}

parser::generate_statement_type generate_statement() {
    return eda::vhdl::parser::generate_statement;
}

parser::generic_clause_type generic_clause() {
    return eda::vhdl::parser::generic_clause;
}

parser::generic_map_aspect_type generic_map_aspect() {
    return eda::vhdl::parser::generic_map_aspect;
}

parser::group_declaration_type group_declaration() {
    return eda::vhdl::parser::group_declaration;
}

parser::group_template_declaration_type group_template_declaration() {
    return eda::vhdl::parser::group_template_declaration;
}

parser::identifier_type identifier() {
    return eda::vhdl::parser::identifier;
}

parser::identifier_list_type identifier_list() {
    return eda::vhdl::parser::identifier_list;
}

parser::if_statement_type if_statement() {
    return eda::vhdl::parser::if_statement;
}

parser::index_constraint_type index_constraint() {
    return eda::vhdl::parser::index_constraint;
}

parser::index_subtype_definition_type index_subtype_definition() {
    return eda::vhdl::parser::index_subtype_definition;
}

parser::indexed_name_type indexed_name() {
    return eda::vhdl::parser::indexed_name;
}

parser::integer_type integer() {
    return eda::vhdl::parser::integer;
}

parser::interface_constant_declaration_type interface_constant_declaration() {
    return eda::vhdl::parser::interface_constant_declaration;
}

parser::interface_file_declaration_type interface_file_declaration() {
    return eda::vhdl::parser::interface_file_declaration;
}

parser::interface_signal_declaration_type interface_signal_declaration() {
    return eda::vhdl::parser::interface_signal_declaration;
}

parser::interface_variable_declaration_type interface_variable_declaration() {
    return eda::vhdl::parser::interface_variable_declaration;
}

parser::library_clause_type library_clause() {
    return eda::vhdl::parser::library_clause;
}

parser::literal_type literal() {
    return eda::vhdl::parser::literal;
}

parser::loop_statement_type loop_statement() {
    return eda::vhdl::parser::loop_statement;
}

parser::name_type name() {
    return eda::vhdl::parser::name;
}

parser::next_statement_type next_statement() {
    return eda::vhdl::parser::next_statement;
}

parser::numeric_literal_type numeric_literal() {
    return eda::vhdl::parser::numeric_literal;
}

parser::package_body_type package_body() {
    return eda::vhdl::parser::package_body;
}

parser::package_declaration_type package_declaration() {
    return eda::vhdl::parser::package_declaration;
}

parser::parameter_specification_type parameter_specification() {
    return eda::vhdl::parser::parameter_specification;
}

parser::physical_literal_type physical_literal() {
    return eda::vhdl::parser::physical_literal;
}

parser::physical_type_definition_type physical_type_definition() {
    return eda::vhdl::parser::physical_type_definition;
}

parser::port_clause_type port_clause() {
    return eda::vhdl::parser::port_clause;
}

parser::port_map_aspect_type port_map_aspect() {
    return eda::vhdl::parser::port_map_aspect;
}

parser::primary_type primary() {
    return eda::vhdl::parser::primary;
}

parser::primary_unit_declaration_type primary_unit_declaration() {
    return eda::vhdl::parser::primary_unit_declaration;
}

parser::procedure_call_type procedure_call() {
    return eda::vhdl::parser::procedure_call;
}

parser::process_statement_type process_statement() {
    return eda::vhdl::parser::process_statement;
}

parser::qualified_expression_type qualified_expression() {
    return eda::vhdl::parser::qualified_expression;
}

parser::range_constraint_type range_constraint() {
    return eda::vhdl::parser::range_constraint;
}

parser::record_type_definition_type record_type_definition() {
    return eda::vhdl::parser::record_type_definition;
}

parser::relation_type relation() {
    return eda::vhdl::parser::relation;
}

parser::return_statement_type return_statement() {
    return eda::vhdl::parser::return_statement;
}

parser::secondary_unit_declaration_type secondary_unit_declaration() {
    return eda::vhdl::parser::secondary_unit_declaration;
}

parser::selected_signal_assignment_type selected_signal_assignment() {
    return eda::vhdl::parser::selected_signal_assignment;
}

parser::sequential_statement_type sequential_statement() {
    return eda::vhdl::parser::sequential_statement;
}

parser::shift_expression_type shift_expression() {
    return eda::vhdl::parser::shift_expression;
}

parser::signal_assignment_statement_type signal_assignment_statement() {
    return eda::vhdl::parser::signal_assignment_statement;
}

parser::signal_declaration_type signal_declaration() {
    return eda::vhdl::parser::signal_declaration;
}

parser::signal_list_type signal_list() {
    return eda::vhdl::parser::signal_list;
}

parser::simple_expression_type simple_expression() {
    return eda::vhdl::parser::simple_expression;
}

parser::slice_name_type slice_name() {
    return eda::vhdl::parser::slice_name;
}

parser::string_literal_type string_literal() {
    return eda::vhdl::parser::string_literal;
}

parser::subprogram_body_type subprogram_body() {
    return eda::vhdl::parser::subprogram_body;
}

parser::subprogram_specification_type subprogram_specification() {
    return eda::vhdl::parser::subprogram_specification;
}

parser::subtype_declaration_type subtype_declaration() {
    return eda::vhdl::parser::subtype_declaration;
}

parser::subtype_indication_type subtype_indication() {
    return eda::vhdl::parser::subtype_indication;
}

parser::term_type term() {
    return eda::vhdl::parser::term;
}

parser::type_conversion_type type_conversion() {
    return eda::vhdl::parser::type_conversion;
}

parser::type_declaration_type type_declaration() {
    return eda::vhdl::parser::type_declaration;
}

parser::type_definition_type type_definition() {
    return eda::vhdl::parser::type_definition;
}

parser::unconstrained_array_definition_type unconstrained_array_definition() {
    return eda::vhdl::parser::unconstrained_array_definition;
}

parser::use_clause_type use_clause() {
    return eda::vhdl::parser::use_clause;
}

parser::variable_assignment_statement_type variable_assignment_statement() {
    return eda::vhdl::parser::variable_assignment_statement;
}

parser::variable_declaration_type variable_declaration() {
    return eda::vhdl::parser::variable_declaration;
}

parser::wait_statement_type wait_statement() {
    return eda::vhdl::parser::wait_statement;
}

parser::waveform_type waveform() {
    return eda::vhdl::parser::waveform;
}
// clang-format on

}  // namespace testsuite::vhdl::parser
