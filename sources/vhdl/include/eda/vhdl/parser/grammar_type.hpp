/*
 * grammar_type.hpp
 *
 *  Created on: 13.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_TYPE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_TYPE_HPP_

#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/parser/grammar_id.hpp>

#include <boost/spirit/home/x3/core.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp> // Note, alone doesn't compile

namespace eda {
namespace vhdl {
namespace parser {

// clang-format off
using abstract_literal_type = x3::rule<abstract_literal_class, ast::abstract_literal>;
using access_type_definition_type = x3::rule<access_type_definition_class, ast::access_type_definition>;
using actual_designator_type = x3::rule<actual_designator_class, ast::actual_designator>;
using actual_parameter_part_type = x3::rule<actual_parameter_part_class, ast::actual_parameter_part>;
using actual_part_type = x3::rule<actual_part_class, ast::actual_part>;
using aggregate_type = x3::rule<aggregate_class, ast::aggregate>;
using alias_declaration_type = x3::rule<alias_declaration_class, ast::alias_declaration>;
using alias_designator_type = x3::rule<alias_designator_class, ast::alias_designator>;
using allocator_type = x3::rule<allocator_class, ast::allocator>;
using architecture_body_type = x3::rule<architecture_body_class, ast::architecture_body>;
using architecture_declarative_part_type = x3::rule<architecture_declarative_part_class, ast::architecture_declarative_part>;
using architecture_statement_part_type = x3::rule<architecture_statement_part_class, ast::architecture_statement_part>;
using array_type_definition_type = x3::rule<array_type_definition_class, ast::array_type_definition>;
using assertion_type = x3::rule<assertion_class, ast::assertion>;
using assertion_statement_type = x3::rule<assertion_statement_class, ast::assertion_statement>;
using association_element_type = x3::rule<association_element_class, ast::association_element>;
using association_list_type = x3::rule<association_list_class, ast::association_list>;
using attribute_declaration_type = x3::rule<attribute_declaration_class, ast::attribute_declaration>;
using attribute_designator_type = x3::rule<attribute_designator_class, ast::simple_name>;
using attribute_name_type = x3::rule<attribute_name_class, ast::attribute_name>;
using attribute_specification_type = x3::rule<attribute_specification_class, ast::attribute_specification>;
using base_type = x3::rule<base_class, ast::string_span>;
using based_integer_type = x3::rule<based_integer_class, ast::string_span>;
using based_literal_type = x3::rule<based_literal_class, ast::based_literal>;
using basic_graphic_character_type = x3::rule<basic_graphic_character_class, char>;
using basic_identifier_type = x3::rule<basic_identifier_class, ast::string_span>;
using binding_indication_type = x3::rule<binding_indication_class, ast::binding_indication>;
using bit_string_literal_type = x3::rule<bit_string_literal_class, ast::bit_string_literal>;
using block_configuration_type = x3::rule<block_configuration_class, ast::block_configuration>;
using block_declarative_item_type = x3::rule<block_declarative_item_class, ast::block_declarative_item>;
using block_declarative_part_type = x3::rule<block_declarative_part_class, ast::block_declarative_part>;
using block_header_type = x3::rule<block_header_class, ast::block_header>;
using block_specification_type = x3::rule<block_specification_class, ast::block_specification>;
using block_statement_type = x3::rule<block_statement_class, ast::block_statement>;
using block_statement_part_type = x3::rule<block_statement_part_class, ast::block_statement_part>;
using case_statement_type = x3::rule<case_statement_class, ast::case_statement>;
using case_statement_alternative_type = x3::rule<case_statement_alternative_class, ast::case_statement_alternative>;
using character_literal_type = x3::rule<character_literal_class, ast::character_literal>;
using choice_type = x3::rule<choice_class, ast::choice>;
using choices_type = x3::rule<choices_class, ast::choices>;
using component_configuration_type = x3::rule<component_configuration_class, ast::component_configuration>;
using component_declaration_type = x3::rule<component_declaration_class, ast::component_declaration>;
using component_instantiation_statement_type = x3::rule<component_instantiation_statement_class, ast::component_instantiation_statement>;
using component_specification_type = x3::rule<component_specification_class, ast::component_specification>;
using composite_type_definition_type = x3::rule<composite_type_definition_class, ast::composite_type_definition>;
using concurrent_assertion_statement_type = x3::rule<concurrent_assertion_statement_class, ast::concurrent_assertion_statement>;
using concurrent_procedure_call_statement_type = x3::rule<concurrent_procedure_call_statement_class, ast::concurrent_procedure_call_statement>;
using concurrent_signal_assignment_statement_type = x3::rule<concurrent_signal_assignment_statement_class, ast::concurrent_signal_assignment_statement>;
using concurrent_statement_type = x3::rule<concurrent_statement_class, ast::concurrent_statement>;
using condition_type = x3::rule<condition_class, ast::condition>;
using condition_clause_type = x3::rule<condition_clause_class, ast::condition_clause>;
using conditional_signal_assignment_type = x3::rule<conditional_signal_assignment_class, ast::conditional_signal_assignment>;
using conditional_waveforms_type = x3::rule<conditional_waveforms_class, ast::conditional_waveforms>;
using configuration_declaration_type = x3::rule<configuration_declaration_class, ast::configuration_declaration>;
using configuration_declarative_item_type = x3::rule<configuration_declarative_item_class, ast::configuration_declarative_item>;
using configuration_declarative_part_type = x3::rule<configuration_declarative_part_class, ast::configuration_declarative_part>;
using configuration_item_type = x3::rule<configuration_item_class, ast::configuration_item>;
using configuration_specification_type = x3::rule<configuration_specification_class, ast::configuration_specification>;
using constant_declaration_type = x3::rule<constant_declaration_class, ast::constant_declaration>;
using constrained_array_definition_type = x3::rule<constrained_array_definition_class, ast::constrained_array_definition>;
using constraint_type = x3::rule<constraint_class, ast::constraint>;
using context_clause_type = x3::rule<context_clause_class, ast::context_clause>;
using context_item_type = x3::rule<context_item_class, ast::context_item>;
using decimal_literal_type = x3::rule<decimal_literal_class, ast::decimal_literal>;
using delay_mechanism_type = x3::rule<delay_mechanism_class, ast::delay_mechanism>;
//using design_file_type = x3::rule<design_file_class, ast::design_file>;
using design_unit_type = x3::rule<design_unit_class, ast::design_unit>;
using designator_type = x3::rule<designator_class, ast::designator>;
using direction_type = x3::rule<direction_class, ast::keyword_token>;
using disconnection_specification_type = x3::rule<disconnection_specification_class, ast::disconnection_specification>;
using discrete_range_type = x3::rule<discrete_range_class, ast::discrete_range>;
using element_association_type = x3::rule<element_association_class, ast::element_association>;
using element_declaration_type = x3::rule<element_declaration_class, ast::element_declaration>;
using element_subtype_definition_type = x3::rule<element_subtype_definition_class, ast::subtype_indication>;
using entity_aspect_type = x3::rule<entity_aspect_class, ast::entity_aspect>;
using entity_class_type = x3::rule<entity_class_class, ast::keyword_token>;
using entity_class_entry_type = x3::rule<entity_class_entry_class, ast::keyword_token>;
using entity_class_entry_list_type = x3::rule<entity_class_entry_list_class, ast::entity_class_entry_list>;
using entity_declaration_type = x3::rule<entity_declaration_class, ast::entity_declaration>;
using entity_declarative_item_type = x3::rule<entity_declarative_item_class, ast::entity_declarative_item>;
using entity_declarative_part_type = x3::rule<entity_declarative_part_class, ast::entity_declarative_part>;
using entity_designator_type = x3::rule<entity_designator_class, ast::entity_designator>;
using entity_header_type = x3::rule<entity_header_class, ast::entity_header>;
using entity_name_list_type = x3::rule<entity_name_list_class, ast::entity_name_list>;
using entity_specification_type = x3::rule<entity_specification_class, ast::entity_specification>;
using entity_statement_type = x3::rule<entity_statement_class, ast::entity_statement>;
using entity_statement_part_type = x3::rule<entity_statement_part_class, ast::entity_statement_part>;
using entity_tag_type = x3::rule<entity_tag_class, ast::entity_tag>;
using enumeration_literal_type = x3::rule<enumeration_literal_class, ast::enumeration_literal>;
using enumeration_type_definition_type = x3::rule<enumeration_type_definition_class, ast::enumeration_type_definition>;
using exit_statement_type = x3::rule<exit_statement_class, ast::exit_statement>;
using exponent_type = x3::rule<exponent_class, ast::string_span>;
using expression_type = x3::rule<expression_class, ast::expression>;
using extended_identifier_type = x3::rule<extended_identifier_class, ast::string_span>;
using factor_type = x3::rule<factor_class, ast::factor>;
using file_declaration_type = x3::rule<file_declaration_class, ast::file_declaration>;
using file_logical_name_type = x3::rule<file_logical_name_class, ast::file_logical_name>;
using file_open_information_type = x3::rule<file_open_information_class, ast::file_open_information>;
using file_type_definition_type = x3::rule<file_type_definition_class, ast::file_type_definition>;
//using floating_type_definition_type = x3::rule<floating_type_definition_class, ast::floating_type_definition>;
using formal_designator_type = x3::rule<formal_designator_class, ast::name>;
using formal_parameter_list_type = x3::rule<formal_parameter_list_class, ast::formal_parameter_list>;
using formal_part_type = x3::rule<formal_part_class, ast::formal_part>;
//using full_type_declaration_type = x3::rule<full_type_declaration_class, ast::full_type_declaration>;
using function_call_type = x3::rule<function_call_class, ast::function_call>;
using generate_statement_type = x3::rule<generate_statement_class, ast::generate_statement>;
using generation_scheme_type = x3::rule<generation_scheme_class, ast::generation_scheme>;
using generic_clause_type = x3::rule<generic_clause_class, ast::generic_clause>;
//using generic_list_type = x3::rule<generic_list_class, ast::generic_list>;
using generic_map_aspect_type = x3::rule<generic_map_aspect_class, ast::generic_map_aspect>;
using graphic_character_type = x3::rule<graphic_character_class, char>;
using group_constituent_type = x3::rule<group_constituent_class, ast::group_constituent>;
using group_constituent_list_type = x3::rule<group_constituent_list_class, ast::group_constituent_list>;
using group_template_declaration_type = x3::rule<group_template_declaration_class, ast::group_template_declaration>;
using group_declaration_type = x3::rule<group_declaration_class, ast::group_declaration>;
using guarded_signal_specification_type = x3::rule<guarded_signal_specification_class, ast::guarded_signal_specification>;
using identifier_type = x3::rule<identifier_class, ast::identifier>;
using identifier_list_type = x3::rule<identifier_list_class, ast::identifier_list>;
using if_statement_type = x3::rule<if_statement_class, ast::if_statement>;
//using incomplete_type_declaration_type = x3::rule<incomplete_type_declaration_class, ast::incomplete_type_declaration>;
using index_constraint_type = x3::rule<index_constraint_class, ast::index_constraint>;
using index_specification_type = x3::rule<index_specification_class, ast::index_specification>;
using index_subtype_definition_type = x3::rule<index_subtype_definition_class, ast::index_subtype_definition>;
using indexed_name_type = x3::rule<indexed_name_class, ast::indexed_name>;
using instantiated_unit_type = x3::rule<instantiated_unit_class, ast::instantiated_unit>;
using instantiation_list_type = x3::rule<instantiation_list_class, ast::instantiation_list>;
using integer_type = x3::rule<integer_class, ast::string_span>;
//using integer_type_definition_type = x3::rule<integer_type_definition_class, ast::integer_type_definition>;
using interface_constant_declaration_type = x3::rule<interface_constant_declaration_class, ast::interface_constant_declaration>;
using interface_declaration_type = x3::rule<interface_declaration_class, ast::interface_declaration>;
using interface_element_type = x3::rule<interface_element_class, ast::interface_declaration>;
using interface_file_declaration_type = x3::rule<interface_file_declaration_class, ast::interface_file_declaration>;
using interface_list_type = x3::rule<interface_list_class, ast::interface_list>;
using interface_signal_declaration_type = x3::rule<interface_signal_declaration_class, ast::interface_signal_declaration>;
using interface_variable_declaration_type = x3::rule<interface_variable_declaration_class, ast::interface_variable_declaration>;
using iteration_scheme_type = x3::rule<iteration_scheme_class, ast::iteration_scheme>;
using label_type = x3::rule<label_class, ast::label>;
using letter_type = x3::rule<letter_class, char>;
using letter_or_digit_type = x3::rule<letter_or_digit_class, char>;
using library_clause_type = x3::rule<library_clause_class, ast::library_clause>;
using library_unit_type = x3::rule<library_unit_class, ast::library_unit>;
using literal_type = x3::rule<literal_class, ast::literal>;
using logical_name_type = x3::rule<logical_name_class, ast::logical_name>;
using logical_name_list_type = x3::rule<logical_name_list_class, std::vector<ast::logical_name>>;
using loop_statement_type = x3::rule<loop_statement_class, ast::loop_statement>;
using mode_type = x3::rule<mode_class, ast::keyword_token>;
using name_type = x3::rule<name_class, ast::name>;
using next_statement_type = x3::rule<next_statement_class, ast::next_statement>;
using null_statement_type = x3::rule<null_statement_class, ast::null_statement>;
using numeric_literal_type = x3::rule<numeric_literal_class, ast::numeric_literal>;
using operator_symbol_type = x3::rule<operator_symbol_class, ast::operator_symbol>;
using options_type = x3::rule<options_class, ast::options>;
using package_body_type = x3::rule<package_body_class, ast::package_body>;
using package_body_declarative_item_type = x3::rule<package_body_declarative_item_class, ast::package_body_declarative_item>;
using package_body_declarative_part_type = x3::rule<package_body_declarative_part_class, ast::package_body_declarative_part>;
using package_declaration_type = x3::rule<package_declaration_class, ast::package_declaration>;
using package_declarative_item_type = x3::rule<package_declarative_item_class, ast::package_declarative_item>;
using package_declarative_part_type = x3::rule<package_declarative_part_class, ast::package_declarative_part>;
using parameter_specification_type = x3::rule<parameter_specification_class, ast::parameter_specification>;
using physical_literal_type = x3::rule<physical_literal_class, ast::physical_literal>;
using physical_type_definition_type = x3::rule<physical_type_definition_class, ast::physical_type_definition>;
using port_clause_type = x3::rule<port_clause_class, ast::port_clause>;
//using port_list_type = x3::rule<port_list_class, ast::port_list>;
using port_map_aspect_type = x3::rule<port_map_aspect_class, ast::port_map_aspect>;
using prefix_type = x3::rule<prefix_class, ast::prefix>;
using primary_type = x3::rule<primary_class, ast::primary>;
using primary_unit_type = x3::rule<primary_unit_class, ast::primary_unit>;
using primary_unit_declaration_type = x3::rule<primary_unit_declaration_class, ast::primary_unit_declaration>;
using procedure_call_type = x3::rule<procedure_call_class, ast::procedure_call>;
using procedure_call_statement_type = x3::rule<procedure_call_statement_class, ast::procedure_call>;
using process_declarative_item_type = x3::rule<process_declarative_item_class, ast::process_declarative_item>;
using process_declarative_part_type = x3::rule<process_declarative_part_class, ast::process_declarative_part>;
using process_statement_type = x3::rule<process_statement_class, ast::process_statement>;
using process_statement_part_type = x3::rule<process_statement_part_class, ast::process_statement_part>;
using qualified_expression_type = x3::rule<qualified_expression_class, ast::qualified_expression>;
using range_type = x3::rule<range_class, ast::range>;
using range_constraint_type = x3::rule<range_constraint_class, ast::range>;
using record_type_definition_type = x3::rule<record_type_definition_class, ast::record_type_definition>;
using relation_type = x3::rule<relation_class, ast::relation>;
using report_statement_type = x3::rule<report_statement_class, ast::report_statement>;
using return_statement_type = x3::rule<return_statement_class, ast::return_statement>;
using scalar_type_definition_type = x3::rule<scalar_type_definition_class, ast::scalar_type_definition>;
using secondary_unit_type = x3::rule<secondary_unit_class, ast::secondary_unit>;
using secondary_unit_declaration_type = x3::rule<secondary_unit_declaration_class, ast::secondary_unit_declaration>;
using selected_name_type = x3::rule<selected_name_class, ast::selected_name>;
using selected_signal_assignment_type = x3::rule<selected_signal_assignment_class, ast::selected_signal_assignment>;
using selected_waveforms_type = x3::rule<selected_waveforms_class, ast::selected_waveforms>;
using sensitivity_clause_type = x3::rule<sensitivity_clause_class, ast::sensitivity_clause>;
using sensitivity_list_type = x3::rule<sensitivity_list_class, ast::sensitivity_list>;
using sequence_of_statements_type = x3::rule<sequence_of_statements_class, ast::sequence_of_statements>;
using sequential_statement_type = x3::rule<sequential_statement_class, ast::sequential_statement>;
using shift_expression_type = x3::rule<shift_expression_class, ast::shift_expression>;
using sign_type = x3::rule<sign_class, ast::operator_token>;
using signal_assignment_statement_type = x3::rule<signal_assignment_statement_class, ast::signal_assignment_statement>;
using signal_declaration_type = x3::rule<signal_declaration_class, ast::signal_declaration>;
using signal_kind_type = x3::rule<signal_kind_class, ast::keyword_token>;
using signal_list_type = x3::rule<signal_list_class, ast::signal_list>;
using signature_type = x3::rule<signature_class, ast::signature>;
using simple_expression_type = x3::rule<simple_expression_class, ast::simple_expression>;
using simple_name_type = x3::rule<simple_name_class, ast::simple_name>;
using slice_name_type = x3::rule<slice_name_class, ast::slice_name>;
using string_literal_type = x3::rule<string_literal_class, ast::string_literal>;
using subprogram_body_type = x3::rule<subprogram_body_class, ast::subprogram_body>;
using subprogram_declaration_type = x3::rule<subprogram_declaration_class, ast::subprogram_declaration>;
using subprogram_declarative_item_type = x3::rule<subprogram_declarative_item_class,ast::subprogram_declarative_item>;
using subprogram_declarative_part_type = x3::rule<subprogram_declarative_part_class, ast::subprogram_declarative_part>;
using subprogram_kind_type = x3::rule<subprogram_kind_class, ast::keyword_token>;
using subprogram_specification_type = x3::rule<subprogram_specification_class, ast::subprogram_specification>;
using subprogram_statement_part_type = x3::rule<subprogram_statement_part_class, ast::subprogram_statement_part>;
using subtype_declaration_type = x3::rule<subtype_declaration_class, ast::subtype_declaration>;
using subtype_indication_type = x3::rule<subtype_indication_class, ast::subtype_indication>;
using suffix_type = x3::rule<suffix_class, ast::suffix>;
using target_type = x3::rule<target_class, ast::target>;
using term_type = x3::rule<term_class, ast::term>;
using timeout_clause_type = x3::rule<timeout_clause_class, ast::timeout_clause>;
using type_conversion_type = x3::rule<type_conversion_class, ast::type_conversion>;
using type_declaration_type = x3::rule<type_declaration_class, ast::type_declaration>;
using type_definition_type = x3::rule<type_definition_class, ast::type_definition>;
using type_mark_type = x3::rule<type_mark_class, ast::name>;
using unconstrained_array_definition_type = x3::rule<unconstrained_array_definition_class, ast::unconstrained_array_definition>;
using use_clause_type = x3::rule<use_clause_class, ast::use_clause>;
using variable_assignment_statement_type = x3::rule<variable_assignment_statement_class, ast::variable_assignment_statement>;
using variable_declaration_type = x3::rule<variable_declaration_class, ast::variable_declaration>;
using wait_statement_type = x3::rule<wait_statement_class, ast::wait_statement>;
using waveform_type = x3::rule<waveform_class, ast::waveform>;
using waveform_element_type = x3::rule<waveform_element_class, ast::waveform_element>;
// clang-format on

} // namespace parser
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_TYPE_HPP_ */
