//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <testsuite/vhdl/rules.hpp>

#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl::parser {

// clang-format off
BOOST_SPIRIT_INSTANTIATE(abstract_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(actual_part_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(aggregate_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(alias_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(allocator_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(architecture_body_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(assertion_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(association_list_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(attribute_name_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(attribute_specification_type, iterator_type, context_type)
//BOOST_SPIRIT_INSTANTIATE(based_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(binding_indication_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(bit_string_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(block_configuration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(block_header_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(block_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(case_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(character_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(choices_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(component_configuration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(component_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(component_instantiation_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(component_specification_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(concurrent_assertion_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(conditional_signal_assignment_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(configuration_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(configuration_specification_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(constant_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(constrained_array_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(constraint_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(context_clause_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(decimal_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(disconnection_specification_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(discrete_range_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(element_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(entity_aspect_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(entity_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(enumeration_type_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(exit_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(expression_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(factor_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(file_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(file_open_information_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(formal_part_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(function_call_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(generate_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(generic_clause_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(generic_map_aspect_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(group_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(group_template_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(identifier_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(identifier_list_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(if_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(index_constraint_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(index_subtype_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(indexed_name_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(integer_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(interface_constant_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(interface_file_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(interface_signal_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(interface_variable_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(library_clause_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(loop_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(name_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(next_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(numeric_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(package_body_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(package_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(parameter_specification_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(physical_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(physical_type_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(port_clause_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(port_map_aspect_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(primary_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(primary_unit_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(procedure_call_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(process_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(qualified_expression_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(range_constraint_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(record_type_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(relation_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(return_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(secondary_unit_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(selected_signal_assignment_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(sequential_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(shift_expression_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(signal_assignment_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(signal_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(signal_list_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(simple_expression_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(slice_name_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(string_literal_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(subprogram_body_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(subprogram_specification_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(subtype_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(subtype_indication_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(term_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(type_conversion_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(type_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(type_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(unconstrained_array_definition_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(use_clause_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(variable_assignment_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(variable_declaration_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(wait_statement_type, iterator_type, context_type)
BOOST_SPIRIT_INSTANTIATE(waveform_type, iterator_type, context_type)
// clang-format on
}  // namespace ibis::vhdl::parser

namespace testsuite::vhdl::parser {

// clang-format off
parser::abstract_literal_type abstract_literal() {
    return ibis::vhdl::parser::abstract_literal;
}

parser::actual_part_type actual_part() {
    return ibis::vhdl::parser::actual_part;
}

parser::aggregate_type aggregate() {
    return ibis::vhdl::parser::aggregate;
}

parser::alias_declaration_type alias_declaration() {
    return ibis::vhdl::parser::alias_declaration;
}

parser::allocator_type allocator() {
    return ibis::vhdl::parser::allocator;
}

parser::architecture_body_type architecture_body() {
    return ibis::vhdl::parser::architecture_body;
}

parser::assertion_type assertion() {
    return ibis::vhdl::parser::assertion;
}

parser::association_list_type association_list() {
    return ibis::vhdl::parser::association_list;
}

parser::attribute_name_type attribute_name() {
    return ibis::vhdl::parser::attribute_name;
}

parser::attribute_specification_type attribute_specification() {
    return ibis::vhdl::parser::attribute_specification;
}

parser::based_literal_type based_literal() {
    return ibis::vhdl::parser::based_literal;
}

parser::binding_indication_type binding_indication() {
    return ibis::vhdl::parser::binding_indication;
}

parser::bit_string_literal_type bit_string_literal() {
    return ibis::vhdl::parser::bit_string_literal;
}

parser::block_configuration_type block_configuration() {
    return ibis::vhdl::parser::block_configuration;
}

parser::block_header_type block_header() {
    return ibis::vhdl::parser::block_header;
}

parser::block_statement_type block_statement() {
    return ibis::vhdl::parser::block_statement;
}

parser::case_statement_type case_statement() {
    return ibis::vhdl::parser::case_statement;
}

parser::character_literal_type character_literal() {
    return ibis::vhdl::parser::character_literal;
}

parser::choices_type choices() {
    return ibis::vhdl::parser::choices;
}

parser::component_configuration_type component_configuration() {
    return ibis::vhdl::parser::component_configuration;
}

parser::component_declaration_type component_declaration() {
    return ibis::vhdl::parser::component_declaration;
}

parser::component_instantiation_statement_type component_instantiation_statement() {
    return ibis::vhdl::parser::component_instantiation_statement;
}

parser::component_specification_type component_specification() {
    return ibis::vhdl::parser::component_specification;
}

parser::concurrent_assertion_statement_type concurrent_assertion_statement() {
    return ibis::vhdl::parser::concurrent_assertion_statement;
}

parser::conditional_signal_assignment_type conditional_signal_assignment() {
    return ibis::vhdl::parser::conditional_signal_assignment;
}

parser::configuration_declaration_type configuration_declaration() {
    return ibis::vhdl::parser::configuration_declaration;
}

parser::configuration_specification_type configuration_specification() {
    return ibis::vhdl::parser::configuration_specification;
}

parser::constant_declaration_type constant_declaration() {
    return ibis::vhdl::parser::constant_declaration;
}

parser::constrained_array_definition_type constrained_array_definition() {
    return ibis::vhdl::parser::constrained_array_definition;
}

parser::constraint_type constraint() {
    return ibis::vhdl::parser::constraint;
}

parser::context_clause_type context_clause() {
    return ibis::vhdl::parser::context_clause;
}

parser::decimal_literal_type decimal_literal() {
    return ibis::vhdl::parser::decimal_literal;
}

parser::disconnection_specification_type disconnection_specification() {
    return ibis::vhdl::parser::disconnection_specification;
}

parser::discrete_range_type discrete_range() {
    return ibis::vhdl::parser::discrete_range;
}

parser::element_declaration_type element_declaration() {
    return ibis::vhdl::parser::element_declaration;
}

parser::entity_aspect_type entity_aspect() {
    return ibis::vhdl::parser::entity_aspect;
}

parser::entity_declaration_type entity_declaration() {
    return ibis::vhdl::parser::entity_declaration;
}

parser::enumeration_type_definition_type enumeration_type_definition() {
    return ibis::vhdl::parser::enumeration_type_definition;
}

parser::exit_statement_type exit_statement() {
    return ibis::vhdl::parser::exit_statement;
}

parser::expression_type expression() {
    return ibis::vhdl::parser::expression;
}

parser::factor_type factor() {
    return ibis::vhdl::parser::factor;
}

parser::file_declaration_type file_declaration() {
    return ibis::vhdl::parser::file_declaration;
}

parser::file_open_information_type file_open_information() {
    return ibis::vhdl::parser::file_open_information;
}

parser::formal_part_type formal_part() {
    return ibis::vhdl::parser::formal_part;
}

parser::function_call_type function_call() {
    return ibis::vhdl::parser::function_call;
}

parser::generate_statement_type generate_statement() {
    return ibis::vhdl::parser::generate_statement;
}

parser::generic_clause_type generic_clause() {
    return ibis::vhdl::parser::generic_clause;
}

parser::generic_map_aspect_type generic_map_aspect() {
    return ibis::vhdl::parser::generic_map_aspect;
}

parser::group_declaration_type group_declaration() {
    return ibis::vhdl::parser::group_declaration;
}

parser::group_template_declaration_type group_template_declaration() {
    return ibis::vhdl::parser::group_template_declaration;
}

parser::identifier_type identifier() {
    return ibis::vhdl::parser::identifier;
}

parser::identifier_list_type identifier_list() {
    return ibis::vhdl::parser::identifier_list;
}

parser::if_statement_type if_statement() {
    return ibis::vhdl::parser::if_statement;
}

parser::index_constraint_type index_constraint() {
    return ibis::vhdl::parser::index_constraint;
}

parser::index_subtype_definition_type index_subtype_definition() {
    return ibis::vhdl::parser::index_subtype_definition;
}

parser::indexed_name_type indexed_name() {
    return ibis::vhdl::parser::indexed_name;
}

parser::integer_type integer() {
    return ibis::vhdl::parser::integer;
}

parser::interface_constant_declaration_type interface_constant_declaration() {
    return ibis::vhdl::parser::interface_constant_declaration;
}

parser::interface_file_declaration_type interface_file_declaration() {
    return ibis::vhdl::parser::interface_file_declaration;
}

parser::interface_signal_declaration_type interface_signal_declaration() {
    return ibis::vhdl::parser::interface_signal_declaration;
}

parser::interface_variable_declaration_type interface_variable_declaration() {
    return ibis::vhdl::parser::interface_variable_declaration;
}

parser::library_clause_type library_clause() {
    return ibis::vhdl::parser::library_clause;
}

parser::literal_type literal() {
    return ibis::vhdl::parser::literal;
}

parser::loop_statement_type loop_statement() {
    return ibis::vhdl::parser::loop_statement;
}

parser::name_type name() {
    return ibis::vhdl::parser::name;
}

parser::next_statement_type next_statement() {
    return ibis::vhdl::parser::next_statement;
}

parser::numeric_literal_type numeric_literal() {
    return ibis::vhdl::parser::numeric_literal;
}

parser::package_body_type package_body() {
    return ibis::vhdl::parser::package_body;
}

parser::package_declaration_type package_declaration() {
    return ibis::vhdl::parser::package_declaration;
}

parser::parameter_specification_type parameter_specification() {
    return ibis::vhdl::parser::parameter_specification;
}

parser::physical_literal_type physical_literal() {
    return ibis::vhdl::parser::physical_literal;
}

parser::physical_type_definition_type physical_type_definition() {
    return ibis::vhdl::parser::physical_type_definition;
}

parser::port_clause_type port_clause() {
    return ibis::vhdl::parser::port_clause;
}

parser::port_map_aspect_type port_map_aspect() {
    return ibis::vhdl::parser::port_map_aspect;
}

parser::primary_type primary() {
    return ibis::vhdl::parser::primary;
}

parser::primary_unit_declaration_type primary_unit_declaration() {
    return ibis::vhdl::parser::primary_unit_declaration;
}

parser::procedure_call_type procedure_call() {
    return ibis::vhdl::parser::procedure_call;
}

parser::process_statement_type process_statement() {
    return ibis::vhdl::parser::process_statement;
}

parser::qualified_expression_type qualified_expression() {
    return ibis::vhdl::parser::qualified_expression;
}

parser::range_constraint_type range_constraint() {
    return ibis::vhdl::parser::range_constraint;
}

parser::record_type_definition_type record_type_definition() {
    return ibis::vhdl::parser::record_type_definition;
}

parser::relation_type relation() {
    return ibis::vhdl::parser::relation;
}

parser::return_statement_type return_statement() {
    return ibis::vhdl::parser::return_statement;
}

parser::secondary_unit_declaration_type secondary_unit_declaration() {
    return ibis::vhdl::parser::secondary_unit_declaration;
}

parser::selected_signal_assignment_type selected_signal_assignment() {
    return ibis::vhdl::parser::selected_signal_assignment;
}

parser::sequential_statement_type sequential_statement() {
    return ibis::vhdl::parser::sequential_statement;
}

parser::shift_expression_type shift_expression() {
    return ibis::vhdl::parser::shift_expression;
}

parser::signal_assignment_statement_type signal_assignment_statement() {
    return ibis::vhdl::parser::signal_assignment_statement;
}

parser::signal_declaration_type signal_declaration() {
    return ibis::vhdl::parser::signal_declaration;
}

parser::signal_list_type signal_list() {
    return ibis::vhdl::parser::signal_list;
}

parser::simple_expression_type simple_expression() {
    return ibis::vhdl::parser::simple_expression;
}

parser::slice_name_type slice_name() {
    return ibis::vhdl::parser::slice_name;
}

parser::string_literal_type string_literal() {
    return ibis::vhdl::parser::string_literal;
}

parser::subprogram_body_type subprogram_body() {
    return ibis::vhdl::parser::subprogram_body;
}

parser::subprogram_specification_type subprogram_specification() {
    return ibis::vhdl::parser::subprogram_specification;
}

parser::subtype_declaration_type subtype_declaration() {
    return ibis::vhdl::parser::subtype_declaration;
}

parser::subtype_indication_type subtype_indication() {
    return ibis::vhdl::parser::subtype_indication;
}

parser::term_type term() {
    return ibis::vhdl::parser::term;
}

parser::type_conversion_type type_conversion() {
    return ibis::vhdl::parser::type_conversion;
}

parser::type_declaration_type type_declaration() {
    return ibis::vhdl::parser::type_declaration;
}

parser::type_definition_type type_definition() {
    return ibis::vhdl::parser::type_definition;
}

parser::unconstrained_array_definition_type unconstrained_array_definition() {
    return ibis::vhdl::parser::unconstrained_array_definition;
}

parser::use_clause_type use_clause() {
    return ibis::vhdl::parser::use_clause;
}

parser::variable_assignment_statement_type variable_assignment_statement() {
    return ibis::vhdl::parser::variable_assignment_statement;
}

parser::variable_declaration_type variable_declaration() {
    return ibis::vhdl::parser::variable_declaration;
}

parser::wait_statement_type wait_statement() {
    return ibis::vhdl::parser::wait_statement;
}

parser::waveform_type waveform() {
    return ibis::vhdl::parser::waveform;
}
// clang-format on

}  // namespace testsuite::vhdl::parser
