/*
 * rules.hpp
 *
 *  Created on: 14.06.2018
 *      Author: olaf
 */

#ifndef TESTSUITE_VHDL_PARSER_INCLUDE_TESTSUITE_VHDL_PARSER_RULES_HPP_
#define TESTSUITE_VHDL_PARSER_INCLUDE_TESTSUITE_VHDL_PARSER_RULES_HPP_

#include <eda/vhdl/parser/grammar_decl.hpp>


namespace testsuite { namespace vhdl_parser {


namespace parser = eda::vhdl::parser;


parser::abstract_literal_type const& abstract_literal();
parser::actual_part_type const& actual_part();
parser::aggregate_type const& aggregate();
parser::alias_declaration_type const& alias_declaration();
parser::allocator_type const& allocator();
parser::architecture_body_type const& architecture_body();
parser::assertion_type const& assertion();
parser::association_list_type const& association_list();
parser::attribute_name_type const& attribute_name();
parser::attribute_specification_type const& attribute_specification();
parser::based_literal_type const& based_literal();
parser::binding_indication_type const& binding_indication();
parser::bit_string_literal_type const& bit_string_literal();
parser::block_configuration_type const& block_configuration();
parser::block_header_type const& block_header();
parser::block_statement_type const& block_statement();
parser::case_statement_type const& case_statement();
parser::character_literal_type const& character_literal();
parser::choices_type const& choices();
parser::component_configuration_type const& component_configuration();
parser::component_declaration_type const& component_declaration();
parser::component_instantiation_statement_type const& component_instantiation_statement();
parser::component_specification_type const& component_specification();
parser::concurrent_assertion_statement_type const& concurrent_assertion_statement();
parser::conditional_signal_assignment_type const& conditional_signal_assignment();
parser::configuration_declaration_type const& configuration_declaration();
parser::configuration_specification_type const& configuration_specification();
parser::constant_declaration_type const& constant_declaration();
parser::constrained_array_definition_type const& constrained_array_definition();
parser::constraint_type const& constraint();
parser::context_clause_type const& context_clause();
parser::decimal_literal_type const& decimal_literal();
parser::disconnection_specification_type const& disconnection_specification();
parser::discrete_range_type const& discrete_range();
parser::element_declaration_type const& element_declaration();
parser::entity_aspect_type const& entity_aspect();
parser::entity_declaration_type const& entity_declaration();
parser::enumeration_type_definition_type const& enumeration_type_definition();
parser::exit_statement_type const& exit_statement();
parser::expression_type const& expression();
parser::factor_type const& factor();
parser::file_declaration_type const& file_declaration();
parser::file_open_information_type const& file_open_information();
parser::formal_part_type const& formal_part();
parser::function_call_type const& function_call();
parser::generate_statement_type const& generate_statement();
parser::generic_clause_type const& generic_clause();
parser::generic_map_aspect_type const& generic_map_aspect();
parser::group_declaration_type const& group_declaration();
parser::group_template_declaration_type const& group_template_declaration();
parser::identifier_type const& identifier();
parser::identifier_list_type const& identifier_list();
parser::if_statement_type const& if_statement();
parser::index_constraint_type const& index_constraint();
parser::index_subtype_definition_type const& index_subtype_definition();
parser::indexed_name_type const& indexed_name();
parser::integer_type const& integer();
parser::interface_constant_declaration_type const& interface_constant_declaration();
parser::interface_file_declaration_type const& interface_file_declaration();
parser::interface_signal_declaration_type const& interface_signal_declaration();
parser::interface_variable_declaration_type const& interface_variable_declaration();
parser::library_clause_type const& library_clause();
parser::literal_type const& literal();
parser::loop_statement_type const& loop_statement();
parser::name_type const& name();
parser::next_statement_type const& next_statement();
parser::numeric_literal_type const& numeric_literal();
parser::package_body_type const& package_body();
parser::package_declaration_type const& package_declaration();
parser::parameter_specification_type const& parameter_specification();
parser::physical_literal_type const& physical_literal();
parser::physical_type_definition_type const& physical_type_definition();
parser::port_clause_type const& port_clause();
parser::port_map_aspect_type const& port_map_aspect();
parser::primary_type const& primary();
parser::primary_unit_declaration_type const& primary_unit_declaration();
parser::procedure_call_type const& procedure_call();
parser::process_statement_type const& process_statement();
parser::qualified_expression_type const& qualified_expression();
parser::range_constraint_type const& range_constraint();
parser::record_type_definition_type const& record_type_definition();
parser::relation_type const& relation();
parser::return_statement_type const& return_statement();
parser::secondary_unit_declaration_type const& secondary_unit_declaration();
parser::selected_signal_assignment_type const& selected_signal_assignment();
parser::sequential_statement_type const& sequential_statement();
parser::shift_expression_type const& shift_expression();
parser::signal_assignment_statement_type const& signal_assignment_statement();
parser::signal_declaration_type const& signal_declaration();
parser::signal_list_type const& signal_list();
parser::simple_expression_type const& simple_expression();
parser::slice_name_type const& slice_name();
parser::string_literal_type const& string_literal();
parser::subprogram_body_type const& subprogram_body();
parser::subprogram_specification_type const& subprogram_specification();
parser::subtype_declaration_type const& subtype_declaration();
parser::subtype_indication_type const& subtype_indication();
parser::term_type const& term();
parser::type_conversion_type const& type_conversion();
parser::type_declaration_type const& type_declaration();
parser::type_definition_type const& type_definition();
parser::unconstrained_array_definition_type const& unconstrained_array_definition();
parser::use_clause_type const& use_clause();
parser::variable_assignment_statement_type const& variable_assignment_statement();
parser::variable_declaration_type const& variable_declaration();
parser::wait_statement_type const& wait_statement();
parser::waveform_type const& waveform();


} } // namespace testsuite.vhdl_parser


#endif /* TESTSUITE_VHDL_PARSER_INCLUDE_TESTSUITE_VHDL_PARSER_RULES_HPP_ */
