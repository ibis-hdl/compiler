/*
 * grammar_type.hpp
 *
 *  Created on: 13.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_TYPE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_TYPE_HPP_


#include <eda/vhdl/ast.hpp>
#include <eda/vhdl/parser/namespace_alias.hpp>
#include <eda/vhdl/parser/grammar_id.hpp>
#include <eda/vhdl/parser/common_types.hpp> // iterator_type

#include <eda/support/boost/spirit_x3.hpp>


namespace eda { namespace vhdl { namespace parser {


/*
 * Rule Types
 */

/*
 * Hot Fixes
 *
 * This is required to work with string_view, later version of Spirit.X3
 * as 1.64. Note the hard coded iterator type!!, \see
 * [Spirit.X3 using string_view and member named 'insert' compiler error](
 *  https://stackoverflow.com/questions/50310015/spirit-x3-using-string-view-and-member-named-insert-compiler-error?answertab=active#tab-top) */
using string_view_attribute = boost::iterator_range<parser::iterator_type>;


typedef x3::rule<abstract_literal_class, ast::abstract_literal> abstract_literal_type;
typedef x3::rule<access_type_definition_class, ast::access_type_definition> access_type_definition_type;
typedef x3::rule<actual_designator_class, ast::actual_designator> actual_designator_type;
typedef x3::rule<actual_parameter_part_class, ast::actual_parameter_part> actual_parameter_part_type;
typedef x3::rule<actual_part_class, ast::actual_part> actual_part_type;
typedef x3::rule<aggregate_class, ast::aggregate> aggregate_type;
typedef x3::rule<alias_declaration_class, ast::alias_declaration> alias_declaration_type;
typedef x3::rule<alias_designator_class, ast::alias_designator> alias_designator_type;
typedef x3::rule<allocator_class, ast::allocator> allocator_type;
typedef x3::rule<architecture_body_class, ast::architecture_body> architecture_body_type;
typedef x3::rule<architecture_declarative_part_class, ast::architecture_declarative_part> architecture_declarative_part_type;
typedef x3::rule<architecture_statement_part_class, ast::architecture_statement_part> architecture_statement_part_type;
typedef x3::rule<array_type_definition_class, ast::array_type_definition> array_type_definition_type;
typedef x3::rule<assertion_class, ast::assertion> assertion_type;
typedef x3::rule<assertion_statement_class, ast::assertion_statement> assertion_statement_type;
typedef x3::rule<association_element_class, ast::association_element> association_element_type;
typedef x3::rule<association_list_class, ast::association_list> association_list_type;
typedef x3::rule<attribute_declaration_class, ast::attribute_declaration> attribute_declaration_type;
typedef x3::rule<attribute_designator_class, ast::simple_name> attribute_designator_type;
typedef x3::rule<attribute_name_class, ast::attribute_name> attribute_name_type;
typedef x3::rule<attribute_specification_class, ast::attribute_specification> attribute_specification_type;
typedef x3::rule<base_class, string_view_attribute> base_type;
typedef x3::rule<based_integer_class, string_view_attribute> based_integer_type;
typedef x3::rule<based_literal_class, ast::based_literal> based_literal_type;
typedef x3::rule<basic_graphic_character_class, char> basic_graphic_character_type;
typedef x3::rule<basic_identifier_class, string_view_attribute> basic_identifier_type;
typedef x3::rule<binding_indication_class, ast::binding_indication> binding_indication_type;
typedef x3::rule<bit_string_literal_class, ast::bit_string_literal> bit_string_literal_type;
typedef x3::rule<block_configuration_class, ast::block_configuration> block_configuration_type;
typedef x3::rule<block_declarative_item_class, ast::block_declarative_item> block_declarative_item_type;
typedef x3::rule<block_declarative_part_class, ast::block_declarative_part> block_declarative_part_type;
typedef x3::rule<block_header_class, ast::block_header> block_header_type;
typedef x3::rule<block_specification_class, ast::block_specification> block_specification_type;
typedef x3::rule<block_statement_class, ast::block_statement> block_statement_type;
typedef x3::rule<block_statement_part_class, ast::block_statement_part> block_statement_part_type;
typedef x3::rule<case_statement_class, ast::case_statement> case_statement_type;
typedef x3::rule<case_statement_alternative_class, ast::case_statement_alternative> case_statement_alternative_type;
typedef x3::rule<character_literal_class, ast::character_literal> character_literal_type;
typedef x3::rule<choice_class, ast::choice> choice_type;
typedef x3::rule<choices_class, ast::choices> choices_type;
typedef x3::rule<component_configuration_class, ast::component_configuration> component_configuration_type;
typedef x3::rule<component_declaration_class, ast::component_declaration> component_declaration_type;
typedef x3::rule<component_instantiation_statement_class, ast::component_instantiation_statement> component_instantiation_statement_type;
typedef x3::rule<component_specification_class, ast::component_specification> component_specification_type;
typedef x3::rule<composite_type_definition_class, ast::composite_type_definition> composite_type_definition_type;
typedef x3::rule<concurrent_assertion_statement_class, ast::concurrent_assertion_statement> concurrent_assertion_statement_type;
typedef x3::rule<concurrent_procedure_call_statement_class, ast::concurrent_procedure_call_statement> concurrent_procedure_call_statement_type;
typedef x3::rule<concurrent_signal_assignment_statement_class, ast::concurrent_signal_assignment_statement> concurrent_signal_assignment_statement_type;
typedef x3::rule<concurrent_statement_class, ast::concurrent_statement> concurrent_statement_type;
typedef x3::rule<condition_class, ast::condition> condition_type;
typedef x3::rule<condition_clause_class, ast::condition_clause> condition_clause_type;
typedef x3::rule<conditional_signal_assignment_class, ast::conditional_signal_assignment> conditional_signal_assignment_type;
typedef x3::rule<conditional_waveforms_class, ast::conditional_waveforms> conditional_waveforms_type;
typedef x3::rule<configuration_declaration_class, ast::configuration_declaration> configuration_declaration_type;
typedef x3::rule<configuration_declarative_item_class, ast::configuration_declarative_item> configuration_declarative_item_type;
typedef x3::rule<configuration_declarative_part_class, ast::configuration_declarative_part> configuration_declarative_part_type;
typedef x3::rule<configuration_item_class, ast::configuration_item> configuration_item_type;
typedef x3::rule<configuration_specification_class, ast::configuration_specification> configuration_specification_type;
typedef x3::rule<constant_declaration_class, ast::constant_declaration> constant_declaration_type;
typedef x3::rule<constrained_array_definition_class, ast::constrained_array_definition> constrained_array_definition_type;
typedef x3::rule<constraint_class, ast::constraint> constraint_type;
typedef x3::rule<context_clause_class, ast::context_clause> context_clause_type;
typedef x3::rule<context_item_class, ast::context_item> context_item_type;
typedef x3::rule<decimal_literal_class, ast::decimal_literal> decimal_literal_type;
typedef x3::rule<delay_mechanism_class, ast::delay_mechanism> delay_mechanism_type;
typedef x3::rule<design_file_class, ast::design_file> design_file_type;
typedef x3::rule<design_unit_class, ast::design_unit> design_unit_type;
typedef x3::rule<designator_class, ast::designator> designator_type;
typedef x3::rule<direction_class, ast::keyword_token> direction_type;
typedef x3::rule<disconnection_specification_class, ast::disconnection_specification> disconnection_specification_type;
typedef x3::rule<discrete_range_class, ast::discrete_range> discrete_range_type;
typedef x3::rule<element_association_class, ast::element_association> element_association_type;
typedef x3::rule<element_declaration_class, ast::element_declaration> element_declaration_type;
typedef x3::rule<element_subtype_definition_class, ast::subtype_indication> element_subtype_definition_type;
typedef x3::rule<entity_aspect_class, ast::entity_aspect> entity_aspect_type;
typedef x3::rule<entity_class_class, ast::keyword_token> entity_class_type;
typedef x3::rule<entity_class_entry_class, ast::keyword_token> entity_class_entry_type;
typedef x3::rule<entity_class_entry_list_class, ast::entity_class_entry_list> entity_class_entry_list_type;
typedef x3::rule<entity_declaration_class, ast::entity_declaration> entity_declaration_type;
typedef x3::rule<entity_declarative_item_class, ast::entity_declarative_item> entity_declarative_item_type;
typedef x3::rule<entity_declarative_part_class, ast::entity_declarative_part> entity_declarative_part_type;
typedef x3::rule<entity_designator_class, ast::entity_designator> entity_designator_type;
typedef x3::rule<entity_header_class, ast::entity_header> entity_header_type;
typedef x3::rule<entity_name_list_class, ast::entity_name_list> entity_name_list_type;
typedef x3::rule<entity_specification_class, ast::entity_specification> entity_specification_type;
typedef x3::rule<entity_statement_class, ast::entity_statement> entity_statement_type;
typedef x3::rule<entity_statement_part_class, ast::entity_statement_part> entity_statement_part_type;
typedef x3::rule<entity_tag_class, ast::entity_tag> entity_tag_type;
typedef x3::rule<enumeration_literal_class, ast::enumeration_literal> enumeration_literal_type;
typedef x3::rule<enumeration_type_definition_class, ast::enumeration_type_definition> enumeration_type_definition_type;
typedef x3::rule<exit_statement_class, ast::exit_statement> exit_statement_type;
typedef x3::rule<exponent_class, string_view_attribute> exponent_type;
typedef x3::rule<expression_class, ast::expression> expression_type;
typedef x3::rule<extended_identifier_class, string_view_attribute> extended_identifier_type;
typedef x3::rule<factor_class, ast::factor> factor_type;
typedef x3::rule<file_declaration_class, ast::file_declaration> file_declaration_type;
typedef x3::rule<file_logical_name_class, ast::file_logical_name> file_logical_name_type;
typedef x3::rule<file_open_information_class, ast::file_open_information> file_open_information_type;
typedef x3::rule<file_type_definition_class, ast::file_type_definition> file_type_definition_type;
//typedef x3::rule<floating_type_definition_class, ast::floating_type_definition> floating_type_definition_type;
typedef x3::rule<formal_designator_class, ast::name> formal_designator_type;
typedef x3::rule<formal_parameter_list_class, ast::formal_parameter_list> formal_parameter_list_type;
typedef x3::rule<formal_part_class, ast::formal_part> formal_part_type;
//typedef x3::rule<full_type_declaration_class, ast::full_type_declaration> full_type_declaration_type;
typedef x3::rule<function_call_class, ast::function_call> function_call_type;
typedef x3::rule<generate_statement_class, ast::generate_statement> generate_statement_type;
typedef x3::rule<generation_scheme_class, ast::generation_scheme> generation_scheme_type;
typedef x3::rule<generic_clause_class, ast::generic_clause> generic_clause_type;
//typedef x3::rule<generic_list_class, ast::generic_list> generic_list_type;
typedef x3::rule<generic_map_aspect_class, ast::generic_map_aspect> generic_map_aspect_type;
typedef x3::rule<graphic_character_class, char> graphic_character_type;
typedef x3::rule<group_constituent_class, ast::group_constituent> group_constituent_type;
typedef x3::rule<group_constituent_list_class, ast::group_constituent_list> group_constituent_list_type;
typedef x3::rule<group_template_declaration_class, ast::group_template_declaration> group_template_declaration_type;
typedef x3::rule<group_declaration_class, ast::group_declaration> group_declaration_type;
typedef x3::rule<guarded_signal_specification_class, ast::guarded_signal_specification> guarded_signal_specification_type;
typedef x3::rule<identifier_class, ast::identifier> identifier_type;
typedef x3::rule<identifier_list_class, ast::identifier_list> identifier_list_type;
typedef x3::rule<if_statement_class, ast::if_statement> if_statement_type;
//typedef x3::rule<incomplete_type_declaration_class, ast::incomplete_type_declaration> incomplete_type_declaration_type;
typedef x3::rule<index_constraint_class, ast::index_constraint> index_constraint_type;
typedef x3::rule<index_specification_class, ast::index_specification> index_specification_type;
typedef x3::rule<index_subtype_definition_class, ast::index_subtype_definition> index_subtype_definition_type;
typedef x3::rule<indexed_name_class, ast::indexed_name> indexed_name_type;
typedef x3::rule<instantiated_unit_class, ast::instantiated_unit> instantiated_unit_type;
typedef x3::rule<instantiation_list_class, ast::instantiation_list> instantiation_list_type;
typedef x3::rule<integer_class, string_view_attribute> integer_type;
//typedef x3::rule<integer_type_definition_class, ast::integer_type_definition> integer_type_definition_type;
typedef x3::rule<interface_constant_declaration_class, ast::interface_constant_declaration> interface_constant_declaration_type;
typedef x3::rule<interface_declaration_class, ast::interface_declaration> interface_declaration_type;
typedef x3::rule<interface_element_class, ast::interface_declaration> interface_element_type;
typedef x3::rule<interface_file_declaration_class, ast::interface_file_declaration> interface_file_declaration_type;
typedef x3::rule<interface_list_class, ast::interface_list> interface_list_type;
typedef x3::rule<interface_signal_declaration_class, ast::interface_signal_declaration> interface_signal_declaration_type;
typedef x3::rule<interface_variable_declaration_class, ast::interface_variable_declaration> interface_variable_declaration_type;
typedef x3::rule<iteration_scheme_class, ast::iteration_scheme> iteration_scheme_type;
typedef x3::rule<label_class, ast::label> label_type;
typedef x3::rule<letter_class, char> letter_type;
typedef x3::rule<letter_or_digit_class, char> letter_or_digit_type;
typedef x3::rule<library_clause_class, ast::library_clause> library_clause_type;
typedef x3::rule<library_unit_class, ast::library_unit> library_unit_type;
typedef x3::rule<literal_class, ast::literal> literal_type;
typedef x3::rule<logical_name_class, ast::logical_name> logical_name_type;
typedef x3::rule<logical_name_list_class, std::vector<ast::logical_name>> logical_name_list_type;
typedef x3::rule<loop_statement_class, ast::loop_statement> loop_statement_type;
typedef x3::rule<mode_class, ast::keyword_token> mode_type;
typedef x3::rule<name_class, ast::name> name_type;
typedef x3::rule<next_statement_class, ast::next_statement> next_statement_type;
typedef x3::rule<null_statement_class, ast::null_statement> null_statement_type;
typedef x3::rule<numeric_literal_class, ast::numeric_literal> numeric_literal_type;
typedef x3::rule<operator_symbol_class, ast::operator_symbol> operator_symbol_type;
typedef x3::rule<options_class, ast::options> options_type;
typedef x3::rule<package_body_class, ast::package_body> package_body_type;
typedef x3::rule<package_body_declarative_item_class, ast::package_body_declarative_item> package_body_declarative_item_type;
typedef x3::rule<package_body_declarative_part_class, ast::package_body_declarative_part> package_body_declarative_part_type;
typedef x3::rule<package_declaration_class, ast::package_declaration> package_declaration_type;
typedef x3::rule<package_declarative_item_class, ast::package_declarative_item> package_declarative_item_type;
typedef x3::rule<package_declarative_part_class, ast::package_declarative_part> package_declarative_part_type;
typedef x3::rule<parameter_specification_class, ast::parameter_specification> parameter_specification_type;
typedef x3::rule<physical_literal_class, ast::physical_literal> physical_literal_type;
typedef x3::rule<physical_type_definition_class, ast::physical_type_definition> physical_type_definition_type;
typedef x3::rule<port_clause_class, ast::port_clause> port_clause_type;
//typedef x3::rule<port_list_class, ast::port_list> port_list_type;
typedef x3::rule<port_map_aspect_class, ast::port_map_aspect> port_map_aspect_type;
typedef x3::rule<prefix_class, ast::prefix> prefix_type;
typedef x3::rule<primary_class, ast::primary> primary_type;
typedef x3::rule<primary_unit_class, ast::primary_unit> primary_unit_type;
typedef x3::rule<primary_unit_declaration_class, ast::primary_unit_declaration> primary_unit_declaration_type;
typedef x3::rule<procedure_call_class, ast::procedure_call> procedure_call_type;
typedef x3::rule<procedure_call_statement_class, ast::procedure_call> procedure_call_statement_type;
typedef x3::rule<process_declarative_item_class, ast::process_declarative_item> process_declarative_item_type;
typedef x3::rule<process_declarative_part_class, ast::process_declarative_part> process_declarative_part_type;
typedef x3::rule<process_statement_class, ast::process_statement> process_statement_type;
typedef x3::rule<process_statement_part_class, ast::process_statement_part> process_statement_part_type;
typedef x3::rule<qualified_expression_class, ast::qualified_expression> qualified_expression_type;
typedef x3::rule<range_class, ast::range> range_type;
typedef x3::rule<range_constraint_class, ast::range> range_constraint_type;
typedef x3::rule<record_type_definition_class, ast::record_type_definition> record_type_definition_type;
typedef x3::rule<relation_class, ast::relation> relation_type;
typedef x3::rule<report_statement_class, ast::report_statement> report_statement_type;
typedef x3::rule<return_statement_class, ast::return_statement> return_statement_type;
typedef x3::rule<scalar_type_definition_class, ast::scalar_type_definition> scalar_type_definition_type;
typedef x3::rule<secondary_unit_class, ast::secondary_unit> secondary_unit_type;
typedef x3::rule<secondary_unit_declaration_class, ast::secondary_unit_declaration> secondary_unit_declaration_type;
typedef x3::rule<selected_name_class, ast::selected_name> selected_name_type;
typedef x3::rule<selected_signal_assignment_class, ast::selected_signal_assignment> selected_signal_assignment_type;
typedef x3::rule<selected_waveforms_class, ast::selected_waveforms> selected_waveforms_type;
typedef x3::rule<sensitivity_clause_class, ast::sensitivity_clause> sensitivity_clause_type;
typedef x3::rule<sensitivity_list_class, ast::sensitivity_list> sensitivity_list_type;
typedef x3::rule<sequence_of_statements_class, ast::sequence_of_statements> sequence_of_statements_type;
typedef x3::rule<sequential_statement_class, ast::sequential_statement> sequential_statement_type;
typedef x3::rule<shift_expression_class, ast::shift_expression> shift_expression_type;
typedef x3::rule<sign_class, ast::operator_token> sign_type;
typedef x3::rule<signal_assignment_statement_class, ast::signal_assignment_statement> signal_assignment_statement_type;
typedef x3::rule<signal_declaration_class, ast::signal_declaration> signal_declaration_type;
typedef x3::rule<signal_kind_class, ast::keyword_token> signal_kind_type;
typedef x3::rule<signal_list_class, ast::signal_list> signal_list_type;
typedef x3::rule<signature_class, ast::signature> signature_type;
typedef x3::rule<simple_expression_class, ast::simple_expression> simple_expression_type;
typedef x3::rule<simple_name_class, ast::simple_name> simple_name_type;
typedef x3::rule<slice_name_class, ast::slice_name> slice_name_type;
typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;
typedef x3::rule<subprogram_body_class, ast::subprogram_body> subprogram_body_type;
typedef x3::rule<subprogram_declaration_class, ast::subprogram_declaration> subprogram_declaration_type;
typedef x3::rule<subprogram_declarative_item_class,ast::subprogram_declarative_item> subprogram_declarative_item_type;
typedef x3::rule<subprogram_declarative_part_class, ast::subprogram_declarative_part> subprogram_declarative_part_type;
typedef x3::rule<subprogram_kind_class, ast::keyword_token> subprogram_kind_type;
typedef x3::rule<subprogram_specification_class, ast::subprogram_specification> subprogram_specification_type;
typedef x3::rule<subprogram_statement_part_class, ast::subprogram_statement_part> subprogram_statement_part_type;
typedef x3::rule<subtype_declaration_class, ast::subtype_declaration> subtype_declaration_type;
typedef x3::rule<subtype_indication_class, ast::subtype_indication> subtype_indication_type;
typedef x3::rule<suffix_class, ast::suffix> suffix_type;
typedef x3::rule<target_class, ast::target> target_type;
typedef x3::rule<term_class, ast::term> term_type;
typedef x3::rule<timeout_clause_class, ast::timeout_clause> timeout_clause_type;
typedef x3::rule<type_conversion_class, ast::type_conversion> type_conversion_type;
typedef x3::rule<type_declaration_class, ast::type_declaration> type_declaration_type;
typedef x3::rule<type_definition_class, ast::type_definition> type_definition_type;
typedef x3::rule<type_mark_class, ast::name> type_mark_type;
typedef x3::rule<unconstrained_array_definition_class, ast::unconstrained_array_definition> unconstrained_array_definition_type;
typedef x3::rule<use_clause_class, ast::use_clause> use_clause_type;
typedef x3::rule<variable_assignment_statement_class, ast::variable_assignment_statement> variable_assignment_statement_type;
typedef x3::rule<variable_declaration_class, ast::variable_declaration> variable_declaration_type;
typedef x3::rule<wait_statement_class, ast::wait_statement> wait_statement_type;
typedef x3::rule<waveform_class, ast::waveform> waveform_type;
typedef x3::rule<waveform_element_class, ast::waveform_element> waveform_element_type;


/*
 * Skipper
 */
typedef x3::rule<skipper_class> skipper_type;


} } } // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_GRAMMAR_TYPE_HPP_ */
