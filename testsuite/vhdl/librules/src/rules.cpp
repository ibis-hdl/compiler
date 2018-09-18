/*
 * rules.cpp
 *
 *  Created on: 14.06.2018
 *      Author: olaf
 */

#include <testsuite/vhdl/rules.hpp>

#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

namespace eda {
namespace vhdl {
namespace parser {

BOOST_SPIRIT_INSTANTIATE(abstract_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(actual_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(aggregate_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(alias_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(allocator_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(architecture_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(assertion_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(association_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(attribute_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(attribute_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(based_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(binding_indication_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(bit_string_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(block_configuration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(block_header_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(block_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(case_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(character_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(choices_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_configuration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_instantiation_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(component_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(concurrent_assertion_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(conditional_signal_assignment_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(configuration_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(configuration_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constant_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constrained_array_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(context_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(decimal_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(disconnection_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(discrete_range_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(element_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(entity_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(enumeration_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(exit_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(factor_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(file_open_information_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(formal_part_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(function_call_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generate_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generic_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(generic_map_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(group_template_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(identifier_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(identifier_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(if_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(index_constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(index_subtype_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(indexed_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(integer_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_constant_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_file_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_signal_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(interface_variable_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(library_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(loop_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(next_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(numeric_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(package_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(package_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(parameter_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(physical_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(physical_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(port_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(port_map_aspect_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(primary_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(primary_unit_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(procedure_call_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(process_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(qualified_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(range_constraint_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(record_type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(relation_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(return_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(secondary_unit_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(selected_signal_assignment_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(sequential_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(shift_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_assignment_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(signal_list_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(simple_expression_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(slice_name_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(string_literal_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subprogram_body_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subprogram_specification_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subtype_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(subtype_indication_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(term_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_conversion_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(type_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(unconstrained_array_definition_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(use_clause_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(variable_assignment_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(variable_declaration_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(wait_statement_type, iterator_type, context_type);
BOOST_SPIRIT_INSTANTIATE(waveform_type, iterator_type, context_type);

} // namespace parser
} // namespace vhdl
} // namespace eda

namespace testsuite {
namespace vhdl_parser {

// clang-format off
parser::abstract_literal_type const& abstract_literal() {
    return eda::vhdl::parser::abstract_literal;
}

parser::actual_part_type const& actual_part() {
    return eda::vhdl::parser::actual_part;
}

parser::aggregate_type const& aggregate() {
    return eda::vhdl::parser::aggregate;
}

parser::alias_declaration_type const& alias_declaration() {
    return eda::vhdl::parser::alias_declaration;
}

parser::allocator_type const& allocator() {
    return eda::vhdl::parser::allocator;
}

parser::architecture_body_type const& architecture_body() {
    return eda::vhdl::parser::architecture_body;
}

parser::assertion_type const& assertion() {
    return eda::vhdl::parser::assertion;
}

parser::association_list_type const& association_list() {
    return eda::vhdl::parser::association_list;
}

parser::attribute_name_type const& attribute_name() {
    return eda::vhdl::parser::attribute_name;
}

parser::attribute_specification_type const& attribute_specification() {
    return eda::vhdl::parser::attribute_specification;
}

parser::based_literal_type const& based_literal() {
    return eda::vhdl::parser::based_literal;
}

parser::binding_indication_type const& binding_indication() {
    return eda::vhdl::parser::binding_indication;
}

parser::bit_string_literal_type const& bit_string_literal() {
    return eda::vhdl::parser::bit_string_literal;
}

parser::block_configuration_type const& block_configuration() {
    return eda::vhdl::parser::block_configuration;
}

parser::block_header_type const& block_header() {
    return eda::vhdl::parser::block_header;
}

parser::block_statement_type const& block_statement() {
    return eda::vhdl::parser::block_statement;
}

parser::case_statement_type const& case_statement() {
    return eda::vhdl::parser::case_statement;
}

parser::character_literal_type const& character_literal() {
    return eda::vhdl::parser::character_literal;
}

parser::choices_type const& choices() {
    return eda::vhdl::parser::choices;
}

parser::component_configuration_type const& component_configuration() {
    return eda::vhdl::parser::component_configuration;
}

parser::component_declaration_type const& component_declaration() {
    return eda::vhdl::parser::component_declaration;
}

parser::component_instantiation_statement_type const& component_instantiation_statement() {
    return eda::vhdl::parser::component_instantiation_statement;
}

parser::component_specification_type const& component_specification() {
    return eda::vhdl::parser::component_specification;
}

parser::concurrent_assertion_statement_type const& concurrent_assertion_statement() {
    return eda::vhdl::parser::concurrent_assertion_statement;
}

parser::conditional_signal_assignment_type const& conditional_signal_assignment() {
    return eda::vhdl::parser::conditional_signal_assignment;
}

parser::configuration_declaration_type const& configuration_declaration() {
    return eda::vhdl::parser::configuration_declaration;
}

parser::configuration_specification_type const& configuration_specification() {
    return eda::vhdl::parser::configuration_specification;
}

parser::constant_declaration_type const& constant_declaration() {
    return eda::vhdl::parser::constant_declaration;
}

parser::constrained_array_definition_type const& constrained_array_definition() {
    return eda::vhdl::parser::constrained_array_definition;
}

parser::constraint_type const& constraint() {
    return eda::vhdl::parser::constraint;
}

parser::context_clause_type const& context_clause() {
    return eda::vhdl::parser::context_clause;
}

parser::decimal_literal_type const& decimal_literal() {
    return eda::vhdl::parser::decimal_literal;
}

parser::disconnection_specification_type const& disconnection_specification() {
    return eda::vhdl::parser::disconnection_specification;
}

parser::discrete_range_type const& discrete_range() {
    return eda::vhdl::parser::discrete_range;
}

parser::element_declaration_type const& element_declaration() {
    return eda::vhdl::parser::element_declaration;
}

parser::entity_aspect_type const& entity_aspect() {
    return eda::vhdl::parser::entity_aspect;
}

parser::entity_declaration_type const& entity_declaration() {
    return eda::vhdl::parser::entity_declaration;
}

parser::enumeration_type_definition_type const& enumeration_type_definition() {
    return eda::vhdl::parser::enumeration_type_definition;
}

parser::exit_statement_type const& exit_statement() {
    return eda::vhdl::parser::exit_statement;
}

parser::expression_type const& expression() {
    return eda::vhdl::parser::expression;
}

parser::factor_type const& factor() {
    return eda::vhdl::parser::factor;
}

parser::file_declaration_type const& file_declaration() {
    return eda::vhdl::parser::file_declaration;
}

parser::file_open_information_type const& file_open_information() {
    return eda::vhdl::parser::file_open_information;
}

parser::formal_part_type const& formal_part() {
    return eda::vhdl::parser::formal_part;
}

parser::function_call_type const& function_call() {
    return eda::vhdl::parser::function_call;
}

parser::generate_statement_type const& generate_statement() {
    return eda::vhdl::parser::generate_statement;
}

parser::generic_clause_type const& generic_clause() {
    return eda::vhdl::parser::generic_clause;
}

parser::generic_map_aspect_type const& generic_map_aspect() {
    return eda::vhdl::parser::generic_map_aspect;
}

parser::group_declaration_type const& group_declaration() {
    return eda::vhdl::parser::group_declaration;
}

parser::group_template_declaration_type const& group_template_declaration() {
    return eda::vhdl::parser::group_template_declaration;
}

parser::identifier_type const& identifier() {
    return eda::vhdl::parser::identifier;
}

parser::identifier_list_type const& identifier_list() {
    return eda::vhdl::parser::identifier_list;
}

parser::if_statement_type const& if_statement() {
    return eda::vhdl::parser::if_statement;
}

parser::index_constraint_type const& index_constraint() {
    return eda::vhdl::parser::index_constraint;
}

parser::index_subtype_definition_type const& index_subtype_definition() {
    return eda::vhdl::parser::index_subtype_definition;
}

parser::indexed_name_type const& indexed_name() {
    return eda::vhdl::parser::indexed_name;
}

parser::integer_type const& integer() {
    return eda::vhdl::parser::integer;
}

parser::interface_constant_declaration_type const& interface_constant_declaration() {
    return eda::vhdl::parser::interface_constant_declaration;
}

parser::interface_file_declaration_type const& interface_file_declaration() {
    return eda::vhdl::parser::interface_file_declaration;
}

parser::interface_signal_declaration_type const& interface_signal_declaration() {
    return eda::vhdl::parser::interface_signal_declaration;
}

parser::interface_variable_declaration_type const& interface_variable_declaration() {
    return eda::vhdl::parser::interface_variable_declaration;
}

parser::library_clause_type const& library_clause() {
    return eda::vhdl::parser::library_clause;
}

parser::literal_type const& literal() {
    return eda::vhdl::parser::literal;
}

parser::loop_statement_type const& loop_statement() {
    return eda::vhdl::parser::loop_statement;
}

parser::name_type const& name() {
    return eda::vhdl::parser::name;
}

parser::next_statement_type const& next_statement() {
    return eda::vhdl::parser::next_statement;
}

parser::numeric_literal_type const& numeric_literal() {
    return eda::vhdl::parser::numeric_literal;
}

parser::package_body_type const& package_body() {
    return eda::vhdl::parser::package_body;
}

parser::package_declaration_type const& package_declaration() {
    return eda::vhdl::parser::package_declaration;
}

parser::parameter_specification_type const& parameter_specification() {
    return eda::vhdl::parser::parameter_specification;
}

parser::physical_literal_type const& physical_literal() {
    return eda::vhdl::parser::physical_literal;
}

parser::physical_type_definition_type const& physical_type_definition() {
    return eda::vhdl::parser::physical_type_definition;
}

parser::port_clause_type const& port_clause() {
    return eda::vhdl::parser::port_clause;
}

parser::port_map_aspect_type const& port_map_aspect() {
    return eda::vhdl::parser::port_map_aspect;
}

parser::primary_type const& primary() {
    return eda::vhdl::parser::primary;
}

parser::primary_unit_declaration_type const& primary_unit_declaration() {
    return eda::vhdl::parser::primary_unit_declaration;
}

parser::procedure_call_type const& procedure_call() {
    return eda::vhdl::parser::procedure_call;
}

parser::process_statement_type const& process_statement() {
    return eda::vhdl::parser::process_statement;
}

parser::qualified_expression_type const& qualified_expression() {
    return eda::vhdl::parser::qualified_expression;
}

parser::range_constraint_type const& range_constraint() {
    return eda::vhdl::parser::range_constraint;
}

parser::record_type_definition_type const& record_type_definition() {
    return eda::vhdl::parser::record_type_definition;
}

parser::relation_type const& relation() {
    return eda::vhdl::parser::relation;
}

parser::return_statement_type const& return_statement() {
    return eda::vhdl::parser::return_statement;
}

parser::secondary_unit_declaration_type const& secondary_unit_declaration() {
    return eda::vhdl::parser::secondary_unit_declaration;
}

parser::selected_signal_assignment_type const& selected_signal_assignment() {
    return eda::vhdl::parser::selected_signal_assignment;
}

parser::sequential_statement_type const& sequential_statement() {
    return eda::vhdl::parser::sequential_statement;
}

parser::shift_expression_type const& shift_expression() {
    return eda::vhdl::parser::shift_expression;
}

parser::signal_assignment_statement_type const& signal_assignment_statement() {
    return eda::vhdl::parser::signal_assignment_statement;
}

parser::signal_declaration_type const& signal_declaration() {
    return eda::vhdl::parser::signal_declaration;
}

parser::signal_list_type const& signal_list() {
    return eda::vhdl::parser::signal_list;
}

parser::simple_expression_type const& simple_expression() {
    return eda::vhdl::parser::simple_expression;
}

parser::slice_name_type const& slice_name() {
    return eda::vhdl::parser::slice_name;
}

parser::string_literal_type const& string_literal() {
    return eda::vhdl::parser::string_literal;
}

parser::subprogram_body_type const& subprogram_body() {
    return eda::vhdl::parser::subprogram_body;
}

parser::subprogram_specification_type const& subprogram_specification() {
    return eda::vhdl::parser::subprogram_specification;
}

parser::subtype_declaration_type const& subtype_declaration() {
    return eda::vhdl::parser::subtype_declaration;
}

parser::subtype_indication_type const& subtype_indication() {
    return eda::vhdl::parser::subtype_indication;
}

parser::term_type const& term() {
    return eda::vhdl::parser::term;
}

parser::type_conversion_type const& type_conversion() {
    return eda::vhdl::parser::type_conversion;
}

parser::type_declaration_type const& type_declaration() {
    return eda::vhdl::parser::type_declaration;
}

parser::type_definition_type const& type_definition() {
    return eda::vhdl::parser::type_definition;
}

parser::unconstrained_array_definition_type const& unconstrained_array_definition() {
    return eda::vhdl::parser::unconstrained_array_definition;
}

parser::use_clause_type const& use_clause() {
    return eda::vhdl::parser::use_clause;
}

parser::variable_assignment_statement_type const& variable_assignment_statement() {
    return eda::vhdl::parser::variable_assignment_statement;
}

parser::variable_declaration_type const& variable_declaration() {
    return eda::vhdl::parser::variable_declaration;
}

parser::wait_statement_type const& wait_statement() {
    return eda::vhdl::parser::wait_statement;
}

parser::waveform_type const& waveform() {
    return eda::vhdl::parser::waveform;
}
// clang-format on

} // namespace vhdl_parser
} // namespace testsuite
