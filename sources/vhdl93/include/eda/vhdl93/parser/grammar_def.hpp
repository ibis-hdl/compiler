/*
 * grammar_def.h
 *
 *  Created on: 28.02.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_GRAMMAR_DEF_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_GRAMMAR_DEF_HPP_


#include <eda/vhdl93/ast_adapted.hpp>
#include <eda/vhdl93/parser/grammar.hpp>

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>


/*
 * http://www.amos.eguru-il.com/vhdl_info/vhdl87_syntax.html
 * http://www.amos.eguru-il.com/vhdl_info/vhdl93_syntax.html
 *
 * IEEE Standard VHDL Language Reference Manual
 * (IEEE Std. 1076-1993)
 * http://rti.etf.bg.ac.rs/rti/ri5rvl/tutorial/TUTORIAL/IEEE/HTML/1076_TOC.HTM
 */


namespace eda { namespace vhdl93 { namespace parser {

// VHDL char set is iso8859:1

namespace x3 = boost::spirit::x3;
namespace iso8859_1 = boost::spirit::x3::iso8859_1;
namespace fu = boost::fusion;

/*
 * Rule IDs
 */
struct abstract_literal_class;
struct access_type_definition_class;
struct actual_designator_class;
struct actual_parameter_part_class;
struct actual_part_class;
struct aggregate_class;
struct alias_declaration_class;
struct alias_designator_class;
struct allocator_class;
struct architecture_body_class;
struct architecture_declarative_part_class;
struct architecture_statement_part_class;
struct array_type_definition_class;
struct assertion_class;
struct assertion_statement_class;
struct association_element_class;
struct association_list_class;
struct attribute_declaration_class;
struct attribute_designator_class;
struct attribute_name_class;
struct attribute_specification_class;
struct base_class;
struct base_unit_declaration_class;
struct based_integer_class;
struct based_literal_class;
struct basic_character_class;
struct basic_graphic_character_class;
struct basic_identifier_class;
struct binding_indication_class;
struct bit_string_literal_class;
struct block_configuration_class;
struct block_declarative_item_class;
struct block_declarative_part_class;
struct block_header_class;
struct block_specification_class;
struct block_statement_class;
struct block_statement_part_class;
struct case_statement_class;
struct case_statement_alternative_class;
struct character_literal_class;
struct choice_class;
struct choices_class;
struct component_configuration_class;
struct component_declaration_class;
struct component_instantiation_statement_class;
struct component_specification_class;
struct composite_type_definition_class;
struct concurrent_assertion_statement_class;
struct concurrent_procedure_call_statement_class;
struct concurrent_signal_assignment_statement_class;
struct concurrent_statement_class;
struct condition_class;
struct condition_clause_class;
struct conditional_signal_assignment_class;
struct conditional_waveforms_class;
struct configuration_declaration_class;
struct configuration_declarative_item_class;
struct configuration_declarative_part_class;
struct configuration_item_class;
struct configuration_specification_class;
struct constant_declaration_class;
struct constrained_array_definition_class;
struct constraint_class;
struct context_clause_class;
struct context_item_class;
struct decimal_literal_class;
struct declaration_class;
struct delay_mechanism_class;
struct design_file_class;
struct design_unit_class;
struct designator_class;
struct direction_class;
struct disconnection_specification_class;
struct discrete_range_class;
struct element_association_class;
struct element_declaration_class;
struct element_subtype_definition_class;
struct entity_aspect_class;
struct entity_class_class;
struct entity_class_entry_class;
struct entity_class_entry_list_class;
struct entity_declaration_class;
struct entity_declarative_item_class;
struct entity_declarative_part_class;
struct entity_designator_class;
struct entity_header_class;
struct entity_name_list_class;
struct entity_specification_class;
struct entity_statement_class;
struct entity_statement_part_class;
struct entity_tag_class;
struct enumeration_literal_class;
struct enumeration_type_definition_class;
struct exit_statement_class;
struct exponent_class;
struct expression_class;
struct extended_digit_class;
struct extended_identifier_class;
struct factor_class;
struct file_declaration_class;
struct file_logical_name_class;
struct file_open_information_class;
struct file_type_definition_class;
struct formal_designator_class;
struct formal_parameter_list_class;
struct formal_part_class;
struct full_type_declaration_class;
struct function_call_class;
struct generate_statement_class;
struct generation_scheme_class;
struct generic_clause_class;
struct generic_list_class;
struct generic_map_aspect_class;
struct graphic_character_class;
struct group_constituent_class;
struct group_constituent_list_class;
struct group_template_declaration_class;
struct group_declaration_class;
struct guarded_signal_specification_class;
struct identifier_class;
struct identifier_list_class;
struct if_statement_class;
struct incomplete_type_declaration_class;
struct index_constraint_class;
struct index_specification_class;
struct index_subtype_definition_class;
struct indexed_name_class;
struct instantiated_unit_class;
struct instantiation_list_class;
struct integer_class;
struct integer_type_definition_class;
struct interface_constant_declaration_class;
struct interface_declaration_class;
struct interface_element_class;
struct interface_file_declaration_class;
struct interface_list_class;
struct interface_signal_declaration_class;
struct interface_variable_declaration_class;
struct iteration_scheme_class;
struct label_class;
struct letter_class;
struct letter_or_digit_class;
struct library_clause_class;
struct library_unit_class;
struct literal_class;
struct logical_name_class;
struct logical_name_list_class;
struct loop_statement_class;
struct mode_class;
struct name_class;
struct next_statement_class;
struct null_statement_class;
struct numeric_literal_class;
struct object_declaration_class;
struct operator_symbol_class;
struct options_class;
struct package_body_class;
struct package_body_declarative_item_class;
struct package_body_declarative_part_class;
struct package_declaration_class;
struct package_declarative_item_class;
struct package_declarative_part_class;
struct parameter_specification_class;
struct physical_literal_class;
struct physical_type_definition_class;
struct port_clause_class;
struct port_list_class;
struct port_map_aspect_class;
struct prefix_class;
struct primary_class;
struct primary_unit_class;
struct procedure_call_class;
struct procedure_call_statement_class;
struct process_declarative_item_class;
struct process_declarative_part_class;
struct process_statement_class;
struct process_statement_part_class;
struct qualified_expression_class;
struct range_class;
struct range_constraint_class;
struct record_type_definition_class;
struct relation_class;
struct report_statement_class;
struct return_statement_class;
struct scalar_type_definition_class;
struct secondary_unit_class;
struct secondary_unit_declaration_class;
struct selected_name_class;
struct selected_signal_assignment_class;
struct selected_waveforms_class;
struct sensitivity_clause_class;
struct sensitivity_list_class;
struct sequence_of_statements_class;
struct sequential_statement_class;
struct shift_expression_class;
struct sign_class;
struct signal_assignment_statement_class;
struct signal_declaration_class;
struct signal_kind_class;
struct signal_list_class;
struct signature_class;
struct simple_expression_class;
struct simple_name_class;
struct slice_name_class;
struct string_literal_class;
struct subprogram_body_class;
struct subprogram_declaration_class;
struct subprogram_declarative_item_class;
struct subprogram_declarative_part_class;
struct subprogram_kind_class;
struct subprogram_specification_class;
struct subprogram_statement_part_class;
struct subtype_declaration_class;
struct subtype_indication_class;
struct suffix_class;
struct target_class;
struct term_class;
struct timeout_clause_class;
struct type_conversion_class;
struct type_declaration_class;
struct type_definition_class;
struct type_mark_class;
struct unconstrained_array_definition_class;
struct use_clause_class;
struct variable_assignment_statement_class;
struct variable_declaration_class;
struct wait_statement_class;
struct waveform_class;
struct waveform_element_class;

/*
 * Rule Types
 */
typedef x3::rule<abstract_literal_class, ast::abstract_literal> abstract_literal_type;
typedef x3::rule<access_type_definition_class> access_type_definition_type;
typedef x3::rule<actual_designator_class> actual_designator_type;
typedef x3::rule<actual_parameter_part_class> actual_parameter_part_type;
typedef x3::rule<actual_part_class> actual_part_type;
typedef x3::rule<aggregate_class> aggregate_type;
typedef x3::rule<alias_declaration_class> alias_declaration_type;
typedef x3::rule<alias_designator_class> alias_designator_type;
typedef x3::rule<allocator_class> allocator_type;
typedef x3::rule<architecture_body_class> architecture_body_type;
typedef x3::rule<architecture_declarative_part_class> architecture_declarative_part_type;
typedef x3::rule<architecture_statement_part_class> architecture_statement_part_type;
typedef x3::rule<array_type_definition_class> array_type_definition_type;
typedef x3::rule<assertion_class> assertion_type;
typedef x3::rule<assertion_statement_class> assertion_statement_type;
typedef x3::rule<association_element_class> association_element_type;
typedef x3::rule<association_list_class> association_list_type;
typedef x3::rule<attribute_declaration_class> attribute_declaration_type;
typedef x3::rule<attribute_designator_class> attribute_designator_type;
typedef x3::rule<attribute_name_class> attribute_name_type;
typedef x3::rule<attribute_specification_class> attribute_specification_type;
typedef x3::rule<base_class, std::string> base_type;
typedef x3::rule<base_unit_declaration_class> base_unit_declaration_type;
typedef x3::rule<based_integer_class, std::string> based_integer_type;
typedef x3::rule<based_literal_class, ast::based_literal> based_literal_type;
typedef x3::rule<basic_character_class> basic_character_type;
typedef x3::rule<basic_graphic_character_class, char> basic_graphic_character_type;
typedef x3::rule<basic_identifier_class, std::string> basic_identifier_type;
typedef x3::rule<binding_indication_class> binding_indication_type;
typedef x3::rule<bit_string_literal_class, ast::bit_string_literal> bit_string_literal_type;
typedef x3::rule<block_configuration_class> block_configuration_type;
typedef x3::rule<block_declarative_item_class> block_declarative_item_type;
typedef x3::rule<block_declarative_part_class> block_declarative_part_type;
typedef x3::rule<block_header_class> block_header_type;
typedef x3::rule<block_specification_class> block_specification_type;
typedef x3::rule<block_statement_class> block_statement_type;
typedef x3::rule<block_statement_part_class> block_statement_part_type;
typedef x3::rule<case_statement_class> case_statement_type;
typedef x3::rule<case_statement_alternative_class> case_statement_alternative_type;
typedef x3::rule<character_literal_class, ast::character_literal> character_literal_type;
typedef x3::rule<choice_class> choice_type;
typedef x3::rule<choices_class> choices_type;
typedef x3::rule<component_configuration_class> component_configuration_type;
typedef x3::rule<component_declaration_class> component_declaration_type;
typedef x3::rule<component_instantiation_statement_class> component_instantiation_statement_type;
typedef x3::rule<component_specification_class> component_specification_type;
typedef x3::rule<composite_type_definition_class> composite_type_definition_type;
typedef x3::rule<concurrent_assertion_statement_class> concurrent_assertion_statement_type;
typedef x3::rule<concurrent_procedure_call_statement_class> concurrent_procedure_call_statement_type;
typedef x3::rule<concurrent_signal_assignment_statement_class> concurrent_signal_assignment_statement_type;
typedef x3::rule<concurrent_statement_class> concurrent_statement_type;
typedef x3::rule<condition_class> condition_type;
typedef x3::rule<condition_clause_class> condition_clause_type;
typedef x3::rule<conditional_signal_assignment_class> conditional_signal_assignment_type;
typedef x3::rule<conditional_waveforms_class> conditional_waveforms_type;
typedef x3::rule<configuration_declaration_class> configuration_declaration_type;
typedef x3::rule<configuration_declarative_item_class> configuration_declarative_item_type;
typedef x3::rule<configuration_declarative_part_class> configuration_declarative_part_type;
typedef x3::rule<configuration_item_class> configuration_item_type;
typedef x3::rule<configuration_specification_class> configuration_specification_type;
typedef x3::rule<constant_declaration_class> constant_declaration_type;
typedef x3::rule<constrained_array_definition_class> constrained_array_definition_type;
typedef x3::rule<constraint_class> constraint_type;
typedef x3::rule<context_clause_class> context_clause_type;
typedef x3::rule<context_item_class> context_item_type;
typedef x3::rule<decimal_literal_class, ast::decimal_literal> decimal_literal_type;
typedef x3::rule<declaration_class> declaration_type;
typedef x3::rule<delay_mechanism_class> delay_mechanism_type;
typedef x3::rule<design_file_class> design_file_type;
typedef x3::rule<design_unit_class> design_unit_type;
typedef x3::rule<designator_class> designator_type;
typedef x3::rule<direction_class, ast::direction> direction_type;
typedef x3::rule<disconnection_specification_class> disconnection_specification_type;
typedef x3::rule<discrete_range_class> discrete_range_type;
typedef x3::rule<element_association_class> element_association_type;
typedef x3::rule<element_declaration_class> element_declaration_type;
typedef x3::rule<element_subtype_definition_class> element_subtype_definition_type;
typedef x3::rule<entity_aspect_class> entity_aspect_type;
typedef x3::rule<entity_class_class> entity_class_type;
typedef x3::rule<entity_class_entry_class> entity_class_entry_type;
typedef x3::rule<entity_class_entry_list_class> entity_class_entry_list_type;
typedef x3::rule<entity_declaration_class> entity_declaration_type;
typedef x3::rule<entity_declarative_item_class> entity_declarative_item_type;
typedef x3::rule<entity_declarative_part_class> entity_declarative_part_type;
typedef x3::rule<entity_designator_class> entity_designator_type;
typedef x3::rule<entity_header_class> entity_header_type;
typedef x3::rule<entity_name_list_class> entity_name_list_type;
typedef x3::rule<entity_specification_class> entity_specification_type;
typedef x3::rule<entity_statement_class> entity_statement_type;
typedef x3::rule<entity_statement_part_class> entity_statement_part_type;
typedef x3::rule<entity_tag_class> entity_tag_type;
typedef x3::rule<enumeration_literal_class, ast::enumeration_literal> enumeration_literal_type;
typedef x3::rule<enumeration_type_definition_class, ast::enumeration_type_definition> enumeration_type_definition_type;
typedef x3::rule<exit_statement_class> exit_statement_type;
typedef x3::rule<exponent_class, std::string> exponent_type;
typedef x3::rule<expression_class> expression_type;
typedef x3::rule<extended_digit_class, char> extended_digit_type;
typedef x3::rule<extended_identifier_class, std::string> extended_identifier_type;
typedef x3::rule<factor_class> factor_type;
typedef x3::rule<file_declaration_class> file_declaration_type;
typedef x3::rule<file_logical_name_class> file_logical_name_type;
typedef x3::rule<file_open_information_class> file_open_information_type;
typedef x3::rule<file_type_definition_class> file_type_definition_type;
typedef x3::rule<formal_designator_class> formal_designator_type;
typedef x3::rule<formal_parameter_list_class> formal_parameter_list_type;
typedef x3::rule<formal_part_class> formal_part_type;
typedef x3::rule<full_type_declaration_class> full_type_declaration_type;
typedef x3::rule<function_call_class> function_call_type;
typedef x3::rule<generate_statement_class> generate_statement_type;
typedef x3::rule<generation_scheme_class> generation_scheme_type;
typedef x3::rule<generic_clause_class> generic_clause_type;
typedef x3::rule<generic_list_class> generic_list_type;
typedef x3::rule<generic_map_aspect_class> generic_map_aspect_type;
typedef x3::rule<graphic_character_class, char> graphic_character_type;
typedef x3::rule<group_constituent_class> group_constituent_type;
typedef x3::rule<group_constituent_list_class> group_constituent_list_type;
typedef x3::rule<group_template_declaration_class> group_template_declaration_type;
typedef x3::rule<group_declaration_class> group_declaration_type;
typedef x3::rule<guarded_signal_specification_class> guarded_signal_specification_type;
typedef x3::rule<identifier_class, ast::identifier> identifier_type;
typedef x3::rule<identifier_list_class, ast::identifier_list> identifier_list_type;
typedef x3::rule<if_statement_class> if_statement_type;
typedef x3::rule<incomplete_type_declaration_class> incomplete_type_declaration_type;
typedef x3::rule<index_constraint_class> index_constraint_type;
typedef x3::rule<index_specification_class> index_specification_type;
typedef x3::rule<index_subtype_definition_class> index_subtype_definition_type;
typedef x3::rule<indexed_name_class> indexed_name_type;
typedef x3::rule<instantiated_unit_class> instantiated_unit_type;
typedef x3::rule<instantiation_list_class> instantiation_list_type;
typedef x3::rule<integer_class, std::string> integer_type;
typedef x3::rule<integer_type_definition_class> integer_type_definition_type;
typedef x3::rule<interface_constant_declaration_class> interface_constant_declaration_type;
typedef x3::rule<interface_declaration_class> interface_declaration_type;
typedef x3::rule<interface_element_class> interface_element_type;
typedef x3::rule<interface_file_declaration_class> interface_file_declaration_type;
typedef x3::rule<interface_list_class> interface_list_type;
typedef x3::rule<interface_signal_declaration_class> interface_signal_declaration_type;
typedef x3::rule<interface_variable_declaration_class> interface_variable_declaration_type;
typedef x3::rule<iteration_scheme_class> iteration_scheme_type;
typedef x3::rule<label_class> label_type;
typedef x3::rule<letter_class, char> letter_type;
typedef x3::rule<letter_or_digit_class, char> letter_or_digit_type;
typedef x3::rule<library_clause_class> library_clause_type;
typedef x3::rule<library_unit_class> library_unit_type;
typedef x3::rule<literal_class, ast::literal> literal_type;
typedef x3::rule<logical_name_class> logical_name_type;
typedef x3::rule<logical_name_list_class> logical_name_list_type;
typedef x3::rule<loop_statement_class> loop_statement_type;
typedef x3::rule<mode_class> mode_type;
typedef x3::rule<name_class> name_type;
typedef x3::rule<next_statement_class> next_statement_type;
typedef x3::rule<null_statement_class> null_statement_type;
typedef x3::rule<numeric_literal_class, ast::numeric_literal> numeric_literal_type;
typedef x3::rule<object_declaration_class> object_declaration_type;
typedef x3::rule<operator_symbol_class> operator_symbol_type;
typedef x3::rule<options_class> options_type;
typedef x3::rule<package_body_class> package_body_type;
typedef x3::rule<package_body_declarative_item_class> package_body_declarative_item_type;
typedef x3::rule<package_body_declarative_part_class> package_body_declarative_part_type;
typedef x3::rule<package_declaration_class> package_declaration_type;
typedef x3::rule<package_declarative_item_class> package_declarative_item_type;
typedef x3::rule<package_declarative_part_class> package_declarative_part_type;
typedef x3::rule<parameter_specification_class> parameter_specification_type;
typedef x3::rule<physical_literal_class, ast::physical_literal> physical_literal_type;
typedef x3::rule<physical_type_definition_class> physical_type_definition_type;
typedef x3::rule<port_clause_class> port_clause_type;
typedef x3::rule<port_list_class> port_list_type;
typedef x3::rule<port_map_aspect_class> port_map_aspect_type;
typedef x3::rule<prefix_class> prefix_type;
typedef x3::rule<primary_class> primary_type;
typedef x3::rule<primary_unit_class> primary_unit_type;
typedef x3::rule<procedure_call_class> procedure_call_type;
typedef x3::rule<procedure_call_statement_class> procedure_call_statement_type;
typedef x3::rule<process_declarative_item_class> process_declarative_item_type;
typedef x3::rule<process_declarative_part_class> process_declarative_part_type;
typedef x3::rule<process_statement_class> process_statement_type;
typedef x3::rule<process_statement_part_class> process_statement_part_type;
typedef x3::rule<qualified_expression_class> qualified_expression_type;
typedef x3::rule<range_class> range_type;
typedef x3::rule<range_constraint_class> range_constraint_type;
typedef x3::rule<record_type_definition_class> record_type_definition_type;
typedef x3::rule<relation_class> relation_type;
typedef x3::rule<report_statement_class> report_statement_type;
typedef x3::rule<return_statement_class> return_statement_type;
typedef x3::rule<scalar_type_definition_class> scalar_type_definition_type;
typedef x3::rule<secondary_unit_class> secondary_unit_type;
typedef x3::rule<secondary_unit_declaration_class> secondary_unit_declaration_type;
typedef x3::rule<selected_name_class> selected_name_type;
typedef x3::rule<selected_signal_assignment_class> selected_signal_assignment_type;
typedef x3::rule<selected_waveforms_class> selected_waveforms_type;
typedef x3::rule<sensitivity_clause_class> sensitivity_clause_type;
typedef x3::rule<sensitivity_list_class> sensitivity_list_type;
typedef x3::rule<sequence_of_statements_class> sequence_of_statements_type;
typedef x3::rule<sequential_statement_class> sequential_statement_type;
typedef x3::rule<shift_expression_class> shift_expression_type;
typedef x3::rule<sign_class> sign_type;
typedef x3::rule<signal_assignment_statement_class> signal_assignment_statement_type;
typedef x3::rule<signal_declaration_class> signal_declaration_type;
typedef x3::rule<signal_kind_class> signal_kind_type;
typedef x3::rule<signal_list_class> signal_list_type;
typedef x3::rule<signature_class> signature_type;
typedef x3::rule<simple_expression_class> simple_expression_type;
typedef x3::rule<simple_name_class, ast::simple_name> simple_name_type;
typedef x3::rule<slice_name_class> slice_name_type;
typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;
typedef x3::rule<subprogram_body_class> subprogram_body_type;
typedef x3::rule<subprogram_declaration_class> subprogram_declaration_type;
typedef x3::rule<subprogram_declarative_item_class> subprogram_declarative_item_type;
typedef x3::rule<subprogram_declarative_part_class> subprogram_declarative_part_type;
typedef x3::rule<subprogram_kind_class> subprogram_kind_type;
typedef x3::rule<subprogram_specification_class> subprogram_specification_type;
typedef x3::rule<subprogram_statement_part_class> subprogram_statement_part_type;
typedef x3::rule<subtype_declaration_class> subtype_declaration_type;
typedef x3::rule<subtype_indication_class> subtype_indication_type;
typedef x3::rule<suffix_class> suffix_type;
typedef x3::rule<target_class> target_type;
typedef x3::rule<term_class> term_type;
typedef x3::rule<timeout_clause_class> timeout_clause_type;
typedef x3::rule<type_conversion_class> type_conversion_type;
typedef x3::rule<type_declaration_class> type_declaration_type;
typedef x3::rule<type_definition_class> type_definition_type;
typedef x3::rule<type_mark_class, std::string> type_mark_type;
typedef x3::rule<unconstrained_array_definition_class> unconstrained_array_definition_type;
typedef x3::rule<use_clause_class> use_clause_type;
typedef x3::rule<variable_assignment_statement_class> variable_assignment_statement_type;
typedef x3::rule<variable_declaration_class> variable_declaration_type;
typedef x3::rule<wait_statement_class> wait_statement_type;
typedef x3::rule<waveform_class> waveform_type;
typedef x3::rule<waveform_element_class> waveform_element_type;

/*
 * Rule Instances
 */
abstract_literal_type const abstract_literal { "abstract_literal" };
access_type_definition_type const access_type_definition { "access_type_definition" };
actual_designator_type const actual_designator { "actual_designator" };
actual_parameter_part_type const actual_parameter_part { "actual_parameter_part" };
actual_part_type const actual_part { "actual_part" };
aggregate_type const aggregate { "aggregate" };
alias_declaration_type const alias_declaration { "alias_declaration" };
alias_designator_type const alias_designator { "alias_designator" };
allocator_type const allocator { "allocator" };
architecture_body_type const architecture_body { "architecture_body" };
architecture_declarative_part_type const architecture_declarative_part { "architecture_declarative_part" };
architecture_statement_part_type const architecture_statement_part { "architecture_statement_part" };
array_type_definition_type const array_type_definition { "array_type_definition" };
assertion_type const assertion { "assertion" };
assertion_statement_type const assertion_statement { "assertion_statement" };
association_element_type const association_element { "association_element" };
association_list_type const association_list { "association_list" };
attribute_declaration_type const attribute_declaration { "attribute_declaration" };
attribute_designator_type const attribute_designator { "attribute_designator" };
attribute_name_type const attribute_name { "attribute_name" };
attribute_specification_type const attribute_specification { "attribute_specification" };
base_type const base { "base" };
base_unit_declaration_type const base_unit_declaration { "base_unit_declaration" };
based_integer_type const based_integer { "based_integer" };
based_literal_type const based_literal { "based_literal" };
basic_character_type const basic_character { "basic_character" };
basic_graphic_character_type const basic_graphic_character { "basic_graphic_character" };
basic_identifier_type const basic_identifier { "basic_identifier" };
binding_indication_type const binding_indication { "binding_indication" };
bit_string_literal_type const bit_string_literal { "bit_string_literal" };
block_configuration_type const block_configuration { "block_configuration" };
block_declarative_item_type const block_declarative_item { "block_declarative_item" };
block_declarative_part_type const block_declarative_part { "block_declarative_part" };
block_header_type const block_header { "block_header" };
block_specification_type const block_specification { "block_specification" };
block_statement_type const block_statement { "block_statement" };
block_statement_part_type const block_statement_part { "block_statement_part" };
case_statement_type const case_statement { "case_statement" };
case_statement_alternative_type const case_statement_alternative { "case_statement_alternative" };
character_literal_type const character_literal { "character_literal" };
choice_type const choice { "choice" };
choices_type const choices { "choices" };
component_configuration_type const component_configuration { "component_configuration" };
component_declaration_type const component_declaration { "component_declaration" };
component_instantiation_statement_type const component_instantiation_statement { "component_instantiation_statement" };
component_specification_type const component_specification { "component_specification" };
composite_type_definition_type const composite_type_definition { "composite_type_definition" };
concurrent_assertion_statement_type const concurrent_assertion_statement { "concurrent_assertion_statement" };
concurrent_procedure_call_statement_type const concurrent_procedure_call_statement { "concurrent_procedure_call_statement" };
concurrent_signal_assignment_statement_type const concurrent_signal_assignment_statement { "concurrent_signal_assignment_statement" };
concurrent_statement_type const concurrent_statement { "concurrent_statement" };
condition_type const condition { "condition" };
condition_clause_type const condition_clause { "condition_clause" };
conditional_signal_assignment_type const conditional_signal_assignment { "conditional_signal_assignment" };
conditional_waveforms_type const conditional_waveforms { "conditional_waveforms" };
configuration_declaration_type const configuration_declaration { "configuration_declaration" };
configuration_declarative_item_type const configuration_declarative_item { "configuration_declarative_item" };
configuration_declarative_part_type const configuration_declarative_part { "configuration_declarative_part" };
configuration_item_type const configuration_item { "configuration_item" };
configuration_specification_type const configuration_specification { "configuration_specification" };
constant_declaration_type const constant_declaration { "constant_declaration" };
constrained_array_definition_type const constrained_array_definition { "constrained_array_definition" };
constraint_type const constraint { "constraint" };
context_clause_type const context_clause { "context_clause" };
context_item_type const context_item { "context_item" };
decimal_literal_type const decimal_literal { "decimal_literal" };
declaration_type const declaration { "declaration" };
delay_mechanism_type const delay_mechanism { "delay_mechanism" };
design_file_type const design_file { "design_file" };
design_unit_type const design_unit { "design_unit" };
designator_type const designator { "designator" };
direction_type const direction { "direction" };
disconnection_specification_type const disconnection_specification { "disconnection_specification" };
discrete_range_type const discrete_range { "discrete_range" };
element_association_type const element_association { "element_association" };
element_declaration_type const element_declaration { "element_declaration" };
element_subtype_definition_type const element_subtype_definition { "element_subtype_definition" };
entity_aspect_type const entity_aspect { "entity_aspect" };
entity_class_type const entity_class { "entity_class" };
entity_class_entry_type const entity_class_entry { "entity_class_entry" };
entity_class_entry_list_type const entity_class_entry_list { "entity_class_entry_list" };
entity_declaration_type const entity_declaration { "entity_declaration" };
entity_declarative_item_type const entity_declarative_item { "entity_declarative_item" };
entity_declarative_part_type const entity_declarative_part { "entity_declarative_part" };
entity_designator_type const entity_designator { "entity_designator" };
entity_header_type const entity_header { "entity_header" };
entity_name_list_type const entity_name_list { "entity_name_list" };
entity_specification_type const entity_specification { "entity_specification" };
entity_statement_type const entity_statement { "entity_statement" };
entity_statement_part_type const entity_statement_part { "entity_statement_part" };
entity_tag_type const entity_tag { "entity_tag" };
enumeration_literal_type const enumeration_literal { "enumeration_literal" };
enumeration_type_definition_type const enumeration_type_definition { "enumeration_type_definition" };
exit_statement_type const exit_statement { "exit_statement" };
exponent_type const exponent { "exponent" };
expression_type const expression { "expression" };
extended_digit_type const extended_digit { "extended_digit" };
extended_identifier_type const extended_identifier { "extended_identifier" };
factor_type const factor { "factor" };
file_declaration_type const file_declaration { "file_declaration" };
file_logical_name_type const file_logical_name { "file_logical_name" };
file_open_information_type const file_open_information { "file_open_information" };
file_type_definition_type const file_type_definition { "file_type_definition" };
formal_designator_type const formal_designator { "formal_designator" };
formal_parameter_list_type const formal_parameter_list { "formal_parameter_list" };
formal_part_type const formal_part { "formal_part" };
full_type_declaration_type const full_type_declaration { "full_type_declaration" };
function_call_type const function_call { "function_call" };
generate_statement_type const generate_statement { "generate_statement" };
generation_scheme_type const generation_scheme { "generation_scheme" };
generic_clause_type const generic_clause { "generic_clause" };
generic_list_type const generic_list { "generic_list" };
generic_map_aspect_type const generic_map_aspect { "generic_map_aspect" };
graphic_character_type const graphic_character { "graphic_character" };
group_constituent_type const group_constituent { "group_constituent" };
group_constituent_list_type const group_constituent_list { "group_constituent_list" };
group_template_declaration_type const group_template_declaration { "group_template_declaration" };
group_declaration_type const group_declaration { "group_declaration" };
guarded_signal_specification_type const guarded_signal_specification { "guarded_signal_specification" };
identifier_type const identifier { "identifier" };
identifier_list_type const identifier_list { "identifier_list" };
if_statement_type const if_statement { "if_statement" };
incomplete_type_declaration_type const incomplete_type_declaration { "incomplete_type_declaration" };
index_constraint_type const index_constraint { "index_constraint" };
index_specification_type const index_specification { "index_specification" };
index_subtype_definition_type const index_subtype_definition { "index_subtype_definition" };
indexed_name_type const indexed_name { "indexed_name" };
instantiated_unit_type const instantiated_unit { "instantiated_unit" };
instantiation_list_type const instantiation_list { "instantiation_list" };
integer_type const integer { "integer" };
integer_type_definition_type const integer_type_definition { "integer_type_definition" };
interface_constant_declaration_type const interface_constant_declaration { "interface_constant_declaration" };
interface_declaration_type const interface_declaration { "interface_declaration" };
interface_element_type const interface_element { "interface_element" };
interface_file_declaration_type const interface_file_declaration { "interface_file_declaration" };
interface_list_type const interface_list { "interface_list" };
interface_signal_declaration_type const interface_signal_declaration { "interface_signal_declaration" };
interface_variable_declaration_type const interface_variable_declaration { "interface_variable_declaration" };
iteration_scheme_type const iteration_scheme { "iteration_scheme" };
label_type const label { "label" };
letter_type const letter { "letter" };
letter_or_digit_type const letter_or_digit { "letter_or_digit" };
library_clause_type const library_clause { "library_clause" };
library_unit_type const library_unit { "library_unit" };
literal_type const literal { "literal" };
logical_name_type const logical_name { "logical_name" };
logical_name_list_type const logical_name_list { "logical_name_list" };
loop_statement_type const loop_statement { "loop_statement" };
mode_type const mode { "mode" };
name_type const name { "name" };
next_statement_type const next_statement { "next_statement" };
null_statement_type const null_statement { "null_statement" };
numeric_literal_type const numeric_literal { "numeric_literal" };
object_declaration_type const object_declaration { "object_declaration" };
operator_symbol_type const operator_symbol { "operator_symbol" };
options_type const options { "options" };
package_body_type const package_body { "package_body" };
package_body_declarative_item_type const package_body_declarative_item { "package_body_declarative_item" };
package_body_declarative_part_type const package_body_declarative_part { "package_body_declarative_part" };
package_declaration_type const package_declaration { "package_declaration" };
package_declarative_item_type const package_declarative_item { "package_declarative_item" };
package_declarative_part_type const package_declarative_part { "package_declarative_part" };
parameter_specification_type const parameter_specification { "parameter_specification" };
physical_literal_type const physical_literal { "physical_literal" };
physical_type_definition_type const physical_type_definition { "physical_type_definition" };
port_clause_type const port_clause { "port_clause" };
port_list_type const port_list { "port_list" };
port_map_aspect_type const port_map_aspect { "port_map_aspect" };
prefix_type const prefix { "prefix" };
primary_type const primary { "primary" };
primary_unit_type const primary_unit { "primary_unit" };
procedure_call_type const procedure_call { "procedure_call" };
procedure_call_statement_type const procedure_call_statement { "procedure_call_statement" };
process_declarative_item_type const process_declarative_item { "process_declarative_item" };
process_declarative_part_type const process_declarative_part { "process_declarative_part" };
process_statement_type const process_statement { "process_statement" };
process_statement_part_type const process_statement_part { "process_statement_part" };
qualified_expression_type const qualified_expression { "qualified_expression" };
range_type const range { "range" };
range_constraint_type const range_constraint { "range_constraint" };
record_type_definition_type const record_type_definition { "record_type_definition" };
relation_type const relation { "relation" };
report_statement_type const report_statement { "report_statement" };
return_statement_type const return_statement { "return_statement" };
scalar_type_definition_type const scalar_type_definition { "scalar_type_definition" };
secondary_unit_type const secondary_unit { "secondary_unit" };
secondary_unit_declaration_type const secondary_unit_declaration { "secondary_unit_declaration" };
selected_name_type const selected_name { "selected_name" };
selected_signal_assignment_type const selected_signal_assignment { "selected_signal_assignment" };
selected_waveforms_type const selected_waveforms { "selected_waveforms" };
sensitivity_clause_type const sensitivity_clause { "sensitivity_clause" };
sensitivity_list_type const sensitivity_list { "sensitivity_list" };
sequence_of_statements_type const sequence_of_statements { "sequence_of_statements" };
sequential_statement_type const sequential_statement { "sequential_statement" };
shift_expression_type const shift_expression { "shift_expression" };
sign_type const sign { "sign" };
signal_assignment_statement_type const signal_assignment_statement { "signal_assignment_statement" };
signal_declaration_type const signal_declaration { "signal_declaration" };
signal_kind_type const signal_kind { "signal_kind" };
signal_list_type const signal_list { "signal_list" };
signature_type const signature { "signature" };
simple_expression_type const simple_expression { "simple_expression" };
simple_name_type const simple_name { "simple_name" };
slice_name_type const slice_name { "slice_name" };
string_literal_type const string_literal { "string_literal" };
subprogram_body_type const subprogram_body { "subprogram_body" };
subprogram_declaration_type const subprogram_declaration { "subprogram_declaration" };
subprogram_declarative_item_type const subprogram_declarative_item { "subprogram_declarative_item" };
subprogram_declarative_part_type const subprogram_declarative_part { "subprogram_declarative_part" };
subprogram_kind_type const subprogram_kind { "subprogram_kind" };
subprogram_specification_type const subprogram_specification { "subprogram_specification" };
subprogram_statement_part_type const subprogram_statement_part { "subprogram_statement_part" };
subtype_declaration_type const subtype_declaration { "subtype_declaration" };
subtype_indication_type const subtype_indication { "subtype_indication" };
suffix_type const suffix { "suffix" };
target_type const target { "target" };
term_type const term { "term" };
timeout_clause_type const timeout_clause { "timeout_clause" };
type_conversion_type const type_conversion { "type_conversion" };
type_declaration_type const type_declaration { "type_declaration" };
type_definition_type const type_definition { "type_definition" };
type_mark_type const type_mark { "type_mark" };
unconstrained_array_definition_type const unconstrained_array_definition { "unconstrained_array_definition" };
use_clause_type const use_clause { "use_clause" };
variable_assignment_statement_type const variable_assignment_statement { "variable_assignment_statement" };
variable_declaration_type const variable_declaration { "variable_declaration" };
wait_statement_type const wait_statement { "wait_statement" };
waveform_type const waveform { "waveform" };
waveform_element_type const waveform_element { "waveform_element" };

/*
 * Keywords
 */
#if defined(NULL)
#undef NULL
#endif

auto kw = [](auto xx) {
    return x3::lexeme [ x3::no_case[ xx ] >> !(iso8859_1::alnum | '_') ];
};

auto const ABS = kw("abs");
auto const ACCESS = kw("access");
auto const AFTER = kw("after");
auto const ALIAS = kw("alias");
auto const ALL = kw("all");
auto const AND = kw("and");
auto const ARCHITECTURE = kw("architecture");
auto const ARRAY = kw("array");
auto const ASSERT = kw("assert");
auto const ATTRIBUTE = kw("attribute");
auto const BEGIN = kw("begin");
auto const BLOCK = kw("block");
auto const BODY = kw("body");
auto const BUFFER = kw("buffer");
auto const BUS = kw("bus");
auto const CASE = kw("case");
auto const COMPONENT = kw("component");
auto const CONFIGURATION = kw("configuration");
auto const CONSTANT = kw("constant");
auto const DISCONNECT = kw("disconnect");
auto const DOWNTO = kw("downto");
auto const ELSE = kw("else");
auto const ELSIF = kw("elsif");
auto const END = kw("end");
auto const ENTITY = kw("entity");
auto const EXIT = kw("exit");
auto const FILE = kw("file");
auto const FOR = kw("for");
auto const FUNCTION = kw("function");
auto const GENERATE = kw("generate");
auto const GENERIC = kw("generic");
auto const GROUP = kw("group");
auto const GUARDED = kw("guarded");
auto const IF = kw("if");
auto const IMPURE = kw("impure");
auto const IN = kw("in");
auto const INERTIAL = kw("inertial");
auto const INOUT = kw("inout");
auto const IS = kw("is");
auto const LABEL = kw("label");
auto const LIBRARY = kw("library");
auto const LINKAGE = kw("linkage");
auto const LITERAL = kw("literal");
auto const LOOP = kw("loop");
auto const MAP = kw("map");
auto const MOD = kw("mod");
auto const NAND = kw("nand");
auto const NEW = kw("new");
auto const NEXT = kw("next");
auto const NOR = kw("nor");
auto const NOT = kw("not");
auto const NULL = kw("null");
auto const OF = kw("of");
auto const ON = kw("on");
auto const OPEN = kw("open");
auto const OR = kw("or");
auto const OTHERS = kw("others");
auto const OUT = kw("out");
auto const PACKAGE = kw("package");
auto const PORT = kw("port");
auto const POSTPONED = kw("postponed");
auto const PROCEDURE = kw("procedure");
auto const PROCESS = kw("process");
auto const PURE = kw("pure");
auto const RANGE = kw("range");
auto const RECORD = kw("record");
auto const REGISTER = kw("register");
auto const REJECT = kw("reject");
auto const REM = kw("rem");
auto const REPORT = kw("report");
auto const RETURN = kw("return");
auto const ROL = kw("rol");
auto const ROR = kw("ror");
auto const SELECT = kw("select");
auto const SEVERITY = kw("severity");
auto const SIGNAL = kw("signal");
auto const SHARED = kw("shared");
auto const SLA = kw("sla");
auto const SLL = kw("sll");
auto const SRA = kw("sra");
auto const SRL = kw("srl");
auto const SUBTYPE = kw("subtype");
auto const THEN = kw("then");
auto const TO = kw("to");
auto const TRANSPORT = kw("transport");
auto const TYPE = kw("type");
auto const UNAFFECTED = kw("unaffected");
auto const UNITS = kw("units");
auto const UNTIL = kw("until");
auto const USE = kw("use");
auto const VARIABLE = kw("variable");
auto const WAIT = kw("wait");
auto const WHEN = kw("when");
auto const WHILE = kw("while");
auto const WITH = kw("with");
auto const XNOR = kw("xnor");
auto const XOR = kw("xor");

struct keyword_symbols : x3::symbols<char> {

    keyword_symbols() {

        name("keyword");

        add("abs") ("access") ("after") ("alias") ("all") ("and")
           ("architecture") ("array") ("assert") ("attribute") ("begin")
           ("block") ("body") ("buffer") ("bus") ("case") ("component")
           ("configuration") ("constant") ("disconnect") ("downto") ("else")
           ("elsif") ("end") ("entity") ("exit") ("file") ("for")
           ("function") ("generate") ("generic") ("group") ("guarded")
           ("if") ("impure") ("in") ("inertial") ("inout") ("is") ("label")
           ("library") ("linkage") ("literal") ("loop") ("map") ("mod")
           ("nand") ("new") ("next") ("nor") ("not") ("null") ("of") ("on")
           ("open") ("or") ("others") ("out") ("package") ("port")
           ("postponed") ("procedure") ("process") ("pure") ("range")
           ("record") ("register") ("reject") ("rem") ("report") ("return")
           ("rol") ("ror") ("select") ("severity") ("signal") ("shared")
           ("sla") ("sll") ("sra") ("srl") ("subtype") ("then") ("to")
           ("transport") ("type") ("unaffected") ("units") ("until") ("use")
           ("variable") ("wait") ("when") ("while") ("with") ("xnor")
           ("xor")
           ;
    }
} const keywords;

auto const keyword = x3::rule<struct _> { "keyword" } =
    kw( keywords )
    ;

/*
 * Parser Operator Symbol Definition
 */

struct logical_operator_symbols : x3::symbols<ast::operator_> {

    logical_operator_symbols() {

        name("logical_operator");

        add("and", ast::operator_::and_)
           ("or", ast::operator_::or_)
           ("nand", ast::operator_::nand)
           ("nor", ast::operator_::nor)
           ("xor", ast::operator_::xor_)
           ("xnor", ast::operator_::xnor)
           ;
    }
} const logical_operator;


struct relational_operator_symbols : x3::symbols<ast::operator_> {

    relational_operator_symbols() {

        name("relational_operator");

        add("=", ast::operator_::equal)
           ("/=", ast::operator_::not_equals)
           ("<", ast::operator_::less)
           ("<=", ast::operator_::less_equals)
           (">", ast::operator_::greater)
           (">=", ast::operator_::greater_equals)
           ;
    }
} const relational_operator;


struct miscellaneous_operator_symbols : x3::symbols<ast::operator_> {

    miscellaneous_operator_symbols() {

        name("miscellaneous_operator");

        add("**", ast::operator_::exponent)
           ("abs", ast::operator_::abs)
           ("not", ast::operator_::not_)
           ;
    }
} const miscellaneous_operator;


struct adding_operator_symbols : x3::symbols<ast::operator_> {

    adding_operator_symbols() {

        name("adding_operator");

        add("+", ast::operator_::add)
           ("-", ast::operator_::sub)
           ("&", ast::operator_::concat)
           ;
    }
} const adding_operator;


struct multiplying_operator_symbols : x3::symbols<ast::operator_> {

    multiplying_operator_symbols() {

        name("multiplying_operator");

        add("*", ast::operator_::mul)
           ("/", ast::operator_::div)
           ("mod", ast::operator_::mod)
           ("rem", ast::operator_::rem)
           ;
    }
} const multiplying_operator;


struct shift_operator_symbols : x3::symbols<ast::operator_> {

    shift_operator_symbols() {

        name("shift_operator");

        add("sll", ast::operator_::sll)
           ("srl", ast::operator_::srl)
           ("sla", ast::operator_::sla)
           ("sra", ast::operator_::sra)
           ("rol", ast::operator_::rol)
           ("ror", ast::operator_::ror)
           ;
    }
} const shift_operator;




using iso8859_1::char_;
using iso8859_1::lit;
using x3::lexeme;


/*
 * Character Sets                                                       [§ 13.1]
 */

auto const upper_case_letter =
    x3::rule<struct upper_case_letter_class, char> { "upper_case_letter" } =
            char_("ABCDEFGHIJKLMNOPQRSTUVWXYZÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞ");
auto const lower_case_letter =
    x3::rule<struct lower_case_letter_class, char> { "lower_case_letter" } =
        char_("abcdefghijklmnopqrstuvwxyzßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ");
auto const digit =
    x3::rule<struct digit_class, char> { "digit" } =
        char_("0-9");
auto const special_character =
    x3::rule<struct special_character_class, char> { "special_character" } =
        char_("\"#&'()*+,-./:;<=>[]_|");
auto const other_special_character =
    x3::rule<struct other_special_character_class, char> { "other_special_character" } =
        char_("!$%?@\\^`{}~¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿×÷");

auto const space_character =
    x3::rule<struct space_character_class, char> { "space_character" } =
        iso8859_1::space;
auto const format_effector =
    x3::rule<struct format_effector_class> { "format_effector" } =
        char_("\t\n\v\r\f");
auto const end_of_line =
    x3::rule<struct end_of_line_class> { "end_of_line" } =
        x3::eol;


/*
 * Parser helper
 */
template<typename T>
auto as_rule = [](auto p) { return x3::rule<struct _, T>{ "as" } = x3::as_parser(p); };


/*
 * Parser Rule Definition
 */

// abstract_literal ::=
// decimal_literal | based_literal
auto const abstract_literal_def = /* Note, order changed since matters */
      based_literal
    | decimal_literal
    ;


#if 0
// access_type_definition ::=
// access subtype_indication
auto const access_type_definition_def =
ACCESS subtype_indication
;
#endif

#if 0
// actual_designator ::=
// expression
//     | signal_name
//     | variable_name
//     | file_name
//     | open
auto const actual_designator_def =
expression
| signal_name
| variable_name
| file_name
| OPEN
;
#endif

#if 0
// actual_parameter_part ::=
// parameter_association_list
auto const actual_parameter_part_def =
parameter_association_list
;
#endif

#if 0
// actual_part ::=
// actual_designator
//     | function_name ( actual_designator )
//     | type_mark ( actual_designator )
auto const actual_part_def =
actual_designator
| function_name '(' actual_designator ')'     | type_mark '(' actual_designator )
;
#endif

#if 0
// aggregate ::=
// ( element_association { , element_association } )
auto const aggregate_def =
        ( element_association >> ( element_association % ',' ) )
        ;
#endif

#if 0
// alias_declaration ::=
// alias alias_designator [ : subtype_indication ] is name [ signature ] ;
auto const alias_declaration_def =
        ALIAS alias_designator -( > ':' subtype_indication ) IS name -( signature ) > ';'
;
#endif

#if 0
// alias_designator ::=
// identifier | character_literal | operator_symbol
auto const alias_designator_def =
        identifier | character_literal | operator_symbol
        ;
#endif

#if 0
// allocator ::=
// new subtype_indication
//     | new qualified_expression
auto const allocator_def =
        NEW subtype_indication
        | NEW qualified_expression
        ;
#endif

#if 0
// architecture_body ::=
// architecture identifier of entity_name is
//     architecture_declarative_part
//     begin
//     architecture_statement_part
//     end [ architecture ] [ architecture_simple_name ] ;
auto const architecture_body_def =
        ARCHITECTURE identifier OF entity_name IS
        architecture_declarative_part
        BEGIN
        architecture_statement_part
        END -( ARCHITECTURE ) -( architecture_simple_name ) > ';'
;
#endif

#if 0
// architecture_declarative_part ::=
// { block_declarative_item }
auto const architecture_declarative_part_def =
{ block_declarative_item }
;
#endif

#if 0
// architecture_statement_part ::=
// { concurrent_statement }
auto const architecture_statement_part_def =
{ concurrent_statement }
;
#endif

#if 0
// array_type_definition ::=
// unconstrained_array_definition    |   constrained_array_definition
auto const array_type_definition_def =
        unconstrained_array_definition    |   constrained_array_definition
        ;
#endif

#if 0
// assertion ::=
// assert condition
//     [ report expression ]
//     [ severity expression ]
auto const assertion_def =
        ASSERT condition
        -( REPORT expression )
        -( SEVERITY expression )
        ;
#endif

#if 0
// assertion_statement ::=
// [ label : ] assertion ;
auto const assertion_statement_def =
        -( LABEL > ':' ) assertion > ';'
;
#endif

#if 0
// association_element ::=
// [ formal_part => ] actual_part
auto const association_element_def =
        -( formal_part => ) actual_part
        ;
#endif

#if 0
// association_list ::=
// association_element { , association_element }
auto const association_list_def =
        association_element >> ( association_element % ',' )
        ;
#endif

#if 0
// attribute_declaration ::=
// attribute identifier : type_mark ;
auto const attribute_declaration_def =
        ATTRIBUTE identifier > ':' type_mark > ';'
;
#endif

#if 0
// attribute_designator ::=
// attribute_simple_name
auto const attribute_designator_def =
        attribute_simple_name
        ;
#endif

#if 0
// attribute_name ::=
// prefix [ signature ] ' attribute_designator [ ( expression ) ]
auto const attribute_name_def =
        //prefix -( signature ) ' attribute_designator -( '(' expression ')' )
        ;
#endif

#if 0
// attribute_specification ::=
// attribute attribute_designator of entity_specification is expression ;
auto const attribute_specification_def =
        ATTRIBUTE attribute_designator OF entity_specification IS expression > ';'
;
#endif

#if 0
// base ::=                                                           [§ 13.4.2]
// integer
auto const base_def =
    integer
    ;
#endif

#if 0 /* Note: UNUSED, embedded directly into bit_string_literal rule */
// base_specifier ::=                                                   [§ 13.7]
// B | O | X
auto const base_specifier_def =
    'B' | 'O' | 'X'
    ;
#endif

#if 0
// base_unit_declaration ::=
// identifier ;
auto const base_unit_declaration_def =
        identifier > ';'
;
#endif


// based_integer ::=                                                  [§ 13.4.2]
// extended_digit { [ underline ] extended_digit }
auto const based_integer_def =
     lexeme[
         extended_digit >> *( -lit('_') >> extended_digit )
     ]
     ;



// based_literal ::=                                                  [§ 13.4.2]
// base # based_integer [ . based_integer ] # [ exponent ]
namespace detail {

    auto const based_literal_base = as_rule<std::string>(
            lexeme[ based_integer ]
        );

    auto const based_literal_int_exp = as_rule<std::string>(
         lexeme[
                 based_integer >> -(char_('.') >> based_integer)
              >> char_('#')
              >> -exponent
        ]);
}

auto const based_literal_def =
    lexeme [
           detail::based_literal_base
        >> '#'
        >> detail::based_literal_int_exp
    ]
    ;


#if 0
// basic_character ::=
// basic_graphic_character | format_effector
auto const basic_character_def =
        basic_graphic_character | format_effector
        ;
#endif


// basic_graphic_character ::=                                          [§ 13.1]
// upper_case_letter | digit | special_character| space_character
auto const basic_graphic_character_def =
        upper_case_letter
      | digit
      | special_character
      | space_character
      ;



// basic_identifier ::=                                                 [§ 13.3]
// letter { [ underline ] letter_or_digit }
namespace detail {
    auto const basic_identifier_feasible = x3::rule<struct _, std::string> { "basic_identifier" } =
        x3::lexeme [
               letter
            >> !char_('"') // reject bit_string_literal
            >> *( letter_or_digit | char_("_") )
        ]
        ;
}
auto const basic_identifier_def =
    detail::basic_identifier_feasible - keyword
    ;


#if 0
// binding_indication ::=
// [ use entity_aspect ]
//     [ generic_map_aspect ]
//     [ port_map_aspect ]
auto const binding_indication_def =
        -( USE entity_aspect )
        -( generic_map_aspect )
        -( port_map_aspect )
        ;
#endif


// bit_string_literal ::=                                               [§ 13.7]
// base_specifier " bit_value "
namespace detail {

    /* Note: The BNF rule captures too wide for a specific base. §13.7 explains the
     *       valid characters depending on it.
     *       Here it's clever to get an parse error if the rules are violated by
     *      splitting it into several sub rules. */

    auto const bit_value_bin = x3::rule<struct _, std::string> { "bit_value" } =
        lexeme[
            char_("01") >> *( -lit("_") >> char_("01") )
        ];

    auto const bit_value_oct = x3::rule<struct _, std::string> { "bit_value" } =
        lexeme[
            char_("0-7") >> *( -lit("_") >> char_("0-7") )
        ];

    auto const bit_value_hex = x3::rule<struct _, std::string> { "bit_value" } =
        lexeme[
            char_("0-9A-Fa-f") >> *( -lit("_") >> char_("0-9A-Fa-f") )
        ];
}

auto const bit_string_literal_def =
    lexeme[
          (lit("B") >> lit('"') >> detail::bit_value_bin >> lit('"')) >> x3::attr(ast::bit_string_literal::tag::bin)
        | (lit("X") >> lit('"') >> detail::bit_value_hex >> lit('"')) >> x3::attr(ast::bit_string_literal::tag::hex)
        | (lit("O") >> lit('"') >> detail::bit_value_oct >> lit('"')) >> x3::attr(ast::bit_string_literal::tag::oct)
    ];



#if 0
/* Note: unused, directly used by rule bit_string_literal */
// bit_value ::=
// extended_digit { [ underline ] extended_digit }
auto const bit_value_def =
        extended_digit { -( underline ) extended_digit }
;
#endif

#if 0
// block_configuration ::=
// for block_specification
//     { use_clause }
//     { configuration_item }
//     end for ;
auto const block_configuration_def =
        FOR block_specification
        { use_clause }
{ configuration_item }
END FOR > ';'
;
#endif

#if 0
// block_declarative_item ::=
// subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | signal_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | component_declaration
//     | attribute_declaration
//     | attribute_specification
//     | configuration_specification
//     | disconnection_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const block_declarative_item_def =
        subprogram_declaration
        | subprogram_body
        | type_declaration
        | subtype_declaration
        | constant_declaration
        | signal_declaration
        | shared_variable_declaration
        | file_declaration
        | alias_declaration
        | component_declaration
        | attribute_declaration
        | attribute_specification
        | configuration_specification
        | disconnection_specification
        | use_clause
        | group_template_declaration
        | group_declaration
        ;
#endif

#if 0
// block_declarative_part ::=
// { block_declarative_item }
auto const block_declarative_part_def =
{ block_declarative_item }
;
#endif

#if 0
// block_header ::=
// [ generic_clause
//     [ generic_map_aspect ; ] ]
//     [ port_clause
//     [ port_map_aspect ; ] ]
auto const block_header_def =
        -( generic_clause
                -( generic_map_aspect > ';' ) )
                -( port_clause
                        -( port_map_aspect > ';' ) )
                        ;
#endif

#if 0
// block_specification ::=
// architecture_name
//     | block_statement_label
//     | generate_statement_label [ ( index_specification ) ]
auto const block_specification_def =
        architecture_name
        | block_statement_label
        | generate_statement_label -( '(' index_specification ')' )
        ;
#endif

#if 0
// block_statement ::=
// block_label :
//     block [ ( guard_expression ) ] [ is ]
//     block_header
//     block_declarative_part
//     begin
//     block_statement_part
//     end block [ block_label ] ;
auto const block_statement_def =
        block_label > ':'     BLOCK -( '(' guard_expression ')' ) -( IS )
        block_header
        block_declarative_part
        BEGIN
        block_statement_part
        END BLOCK -( block_label ) > ';'
;
#endif

#if 0
// block_statement_part ::=
// { concurrent_statement }
auto const block_statement_part_def =
{ concurrent_statement }
;
#endif

#if 0
// case_statement ::=
// [ case_label : ]
//     case expression is
//     case_statement_alternative
//     { case_statement_alternative }
//     end case [ case_label ] ;
auto const case_statement_def =
        -( case_label > ':' )
        CASE expression IS
        case_statement_alternative
        { case_statement_alternative }
END CASE -( case_label ) > ';'
;
#endif

#if 0
// case_statement_alternative ::=
// when choices =>
//     sequence_of_statements
auto const case_statement_alternative_def =
        WHEN choices =>
sequence_of_statements
;
#endif


// character_literal ::=                                                [§ 13.5]
// ' graphic_character '
auto const character_literal_def =
    x3::lexeme [
           "\'"
        >> ( ( graphic_character - '\'' )
           | char_("\'")
           )
        >> "\'"
    ]
    ;


#if 0
// choice ::=
// simple_expression
//     | discrete_range
//     | element_simple_name
//     | others
auto const choice_def =
        simple_expression
        | discrete_range
        | element_simple_name
        | OTHERS
        ;
#endif

#if 0
// choices ::=
// choice { | choice }
auto const choices_def =
        choice { | choice }
;
#endif

#if 0
// component_configuration ::=
// for component_specification
//     [ binding_indication ; ]
//     [ block_configuration ]
//     end for ;
auto const component_configuration_def =
        FOR component_specification
        -( binding_indication > ';' )
        -( block_configuration )
        END FOR > ';'
;
#endif

#if 0
// component_declaration ::=
// component identifier [ is ]
//     [ local_generic_clause ]
//     [ local_port_clause ]
//     end component [ component_simple_name ] ;
auto const component_declaration_def =
        COMPONENT identifier -( IS )
        -( local_generic_clause )
        -( local_port_clause )
        END COMPONENT -( component_simple_name ) > ';'
;
#endif

#if 0
// component_instantiation_statement ::=
// instantiation_label :
//     instantiated_unit
//     [ generic_map_aspect ]
//     [ port_map_aspect ] ;
auto const component_instantiation_statement_def =
        instantiation_label > ':'     instantiated_unit
        -( generic_map_aspect )
        -( port_map_aspect ) > ';'
;
#endif

#if 0
// component_specification ::=
// instantiation_list : component_name
auto const component_specification_def =
        instantiation_list > ':' component_name
        ;
#endif

#if 0
// composite_type_definition ::=
// array_type_definition
//     | record_type_definition
auto const composite_type_definition_def =
        array_type_definition
        | record_type_definition
        ;
#endif

#if 0
// concurrent_assertion_statement ::=
// [ label : ] [ postponed ] assertion ;
auto const concurrent_assertion_statement_def =
        -( LABEL > ':' ) -( POSTPONED ) assertion > ';'
;
#endif

#if 0
// concurrent_procedure_call_statement ::=
// [ label : ] [ postponed ] procedure_call ;
auto const concurrent_procedure_call_statement_def =
        -( LABEL > ':' ) -( POSTPONED ) procedure_call > ';'
;
#endif

#if 0
// concurrent_signal_assignment_statement ::=
// [ label : ] [ postponed ] conditional_signal_assignment
//     | [ label : ] [ postponed ] selected_signal_assignment
auto const concurrent_signal_assignment_statement_def =
        -( LABEL > ':' ) -( POSTPONED ) conditional_signal_assignment
        | -( LABEL > ':' ) -( POSTPONED ) selected_signal_assignment
        ;
#endif

#if 0
// concurrent_statement ::=
// block_statement
//     | process_statement
//     | concurrent_procedure_call_statement
//     | concurrent_assertion_statement
//     | concurrent_signal_assignment_statement
//     | component_instantiation_statement
//     | generate_statement
auto const concurrent_statement_def =
        block_statement
        | process_statement
        | concurrent_procedure_call_statement
        | concurrent_assertion_statement
        | concurrent_signal_assignment_statement
        | component_instantiation_statement
        | generate_statement
        ;
#endif

#if 0
// condition ::=
// boolean_expression
auto const condition_def =
        boolean_expression
        ;
#endif

#if 0
// condition_clause ::=
// until condition
auto const condition_clause_def =
        UNTIL condition
        ;
#endif

#if 0
// conditional_signal_assignment ::=
// target    <= options conditional_waveforms ;
auto const conditional_signal_assignment_def =
        target    <= options conditional_waveforms > ';'
;
#endif

#if 0
// conditional_waveforms ::=
// { waveform when condition else }
//     waveform [ when condition ]
auto const conditional_waveforms_def =
{ waveform WHEN condition ELSE }
waveform -( WHEN condition )
    ;
#endif

#if 0
// configuration_declaration ::=
// configuration identifier of entity_name is
//     configuration_declarative_part
//     block_configuration
//     end [ configuration ] [ configuration_simple_name ] ;
auto const configuration_declaration_def =
        CONFIGURATION identifier OF entity_name IS
        configuration_declarative_part
        block_configuration
        END -( CONFIGURATION ) -( configuration_simple_name ) > ';'
;
#endif

#if 0
// configuration_declarative_item ::=
// use_clause
//     | attribute_specification
//     | group_declaration
auto const configuration_declarative_item_def =
        use_clause
        | attribute_specification
        | group_declaration
        ;
#endif

#if 0
// configuration_declarative_part ::=
// { configuration_declarative_item }
auto const configuration_declarative_part_def =
{ configuration_declarative_item }
;
#endif

#if 0
// configuration_item ::=
// block_configuration
//     | component_configuration
auto const configuration_item_def =
        block_configuration
        | component_configuration
        ;
#endif

#if 0
// configuration_specification ::=
// for component_specification binding_indication ;
auto const configuration_specification_def =
        FOR component_specification binding_indication > ';'
;
#endif

#if 0
// constant_declaration ::=
// constant identifier_list : subtype_indication [ := expression ] ;
auto const constant_declaration_def =
        CONSTANT identifier_list > ':' subtype_indication -(  ":=" >  expression ) > ';'
;
#endif

#if 0
// constrained_array_definition ::=
// array index_constraint of element_subtype_indication
auto const constrained_array_definition_def =
        ARRAY index_constraint OF element_subtype_indication
        ;
#endif

#if 0
// constraint ::=
// range_constraint
//     | index_constraint
auto const constraint_def =
        range_constraint
        | index_constraint
        ;
#endif

#if 0
// context_clause ::=
// { context_item }
auto const context_clause_def =
{ context_item }
;
#endif

#if 0
// context_item ::=
// library_clause
//     | use_clause
auto const context_item_def =
        library_clause
        | use_clause
        ;
#endif


// decimal_literal ::=                                                [§ 13.4.1]
// integer [ . integer ] [ exponent ]
namespace detail {

    auto const decimal_literal_real = as_rule<std::string>(
        lexeme[ (integer >> char_('.') >> integer >> -exponent) ]);

    auto const decimal_literal_int = as_rule<std::string>(
        lexeme[ (integer >> -exponent) ]);
}

auto const decimal_literal_def =
      detail::decimal_literal_real >> x3::attr(ast::decimal_literal::tag::real)
    | detail::decimal_literal_int  >> x3::attr(ast::decimal_literal::tag::integer)
    ;


#if 0
// declaration ::=
// type_declaration
//     | subtype_declaration
//     | object_declaration
//     | interface_declaration
//     | alias_declaration
//     | attribute_declaration
//     | component_declaration
//     | group_template_declaration
//     | group_declaration
//     | entity_declaration
//     | configuration_declaration
//     | subprogram_declaration
//     | package_declaration
auto const declaration_def =
        type_declaration
        | subtype_declaration
        | object_declaration
        | interface_declaration
        | alias_declaration
        | attribute_declaration
        | component_declaration
        | group_template_declaration
        | group_declaration
        | entity_declaration
        | configuration_declaration
        | subprogram_declaration
        | package_declaration
        ;
#endif

#if 0
// delay_mechanism ::=
// transport
//     | [ reject time_expression ] inertial
auto const delay_mechanism_def =
        TRANSPORT
        | -( REJECT time_expression ) INERTIAL
        ;
#endif

#if 0
// design_file ::=
// design_unit { design_unit }
auto const design_file_def =
        design_unit { design_unit }
;
#endif

#if 0
// design_unit ::=
// context_clause library_unit
auto const design_unit_def =
        context_clause library_unit
        ;
#endif

#if 0
// designator ::=
// identifier  |  operator_symbol
auto const designator_def =
        identifier  |  operator_symbol
        ;
#endif


// direction ::=                                                         [§ 3.1]
// to | downto
auto const direction_def =
    TO | DOWNTO
    ;


#if 0
// disconnection_specification ::=
// disconnect guarded_signal_specification after time_expression ;
auto const disconnection_specification_def =
        DISCONNECT guarded_signal_specification AFTER time_expression > ';'
;
#endif

#if 0
// discrete_range ::=
// discrete_subtype_indication | range
auto const discrete_range_def =
        discrete_subtype_indication | RANGE
        ;
#endif

#if 0
// element_association ::=
// [ choices => ] expression
auto const element_association_def =
        -( choices => ) expression
        ;
#endif

#if 0
// element_declaration ::=
// identifier_list : element_subtype_definition ;
auto const element_declaration_def =
        identifier_list > ':' element_subtype_definition > ';'
;
#endif

#if 0
// element_subtype_definition ::=
// subtype_indication
auto const element_subtype_definition_def =
        subtype_indication
        ;
#endif

#if 0
// entity_aspect ::=
// entity entity_name [ ( architecture_identifier) ]
//     | configuration configuration_name
//     | open
auto const entity_aspect_def =
        ENTITY entity_name -( '(' architecture_identifier) )
| CONFIGURATION configuration_name
| OPEN
;
#endif

#if 0
// entity_class ::=
//       entity        | architecture  | configuration
//     | procedure     | function      | package
//     | type          | subtype       | constant
//     | signal        | variable      | component
//     | label         | literal       | units
//     | group         | file
auto const entity_class_def =
        ENTITY         | ARCHITECTURE  | CONFIGURATION
        | PROCEDURE  | FUNCTION         | PACKAGE
        | TYPE         | SUBTYPE         | CONSTANT
        | SIGNAL     | VARIABLE         | COMPONENT
        | LABEL         | LITERAL         | UNITS
        | GROUP         | FILE
        ;
#endif

#if 0
// entity_class_entry ::=
// entity_class [ <> ]
auto const entity_class_entry_def =
        entity_class -( <> )
        ;
#endif

#if 0
// entity_class_entry_list ::=
// entity_class_entry { , entity_class_entry }
auto const entity_class_entry_list_def =
        entity_class_entry >> ( entity_class_entry % ',' )
        ;
#endif

#if 0
// entity_declaration ::=
// entity identifier is
//     entity_header
//     entity_declarative_part
//     [ begin
//     entity_statement_part ]
//     end [ entity ] [ entity_simple_name ] ;
auto const entity_declaration_def =
        ENTITY identifier IS
        entity_header
        entity_declarative_part
        -( BEGIN
                entity_statement_part )
                END -( ENTITY ) -( entity_simple_name ) > ';'
;
#endif

#if 0
// entity_declarative_item ::=
// subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | signal_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | attribute_declaration
//     | attribute_specification
//     | disconnection_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const entity_declarative_item_def =
        subprogram_declaration
        | subprogram_body
        | type_declaration
        | subtype_declaration
        | constant_declaration
        | signal_declaration
        | shared_variable_declaration
        | file_declaration
        | alias_declaration
        | attribute_declaration
        | attribute_specification
        | disconnection_specification
        | use_clause
        | group_template_declaration
        | group_declaration
        ;
#endif

#if 0
// entity_declarative_part ::=
// { entity_declarative_item }
auto const entity_declarative_part_def =
{ entity_declarative_item }
;
#endif

#if 0
// entity_designator ::=
// entity_tag [ signature ]
auto const entity_designator_def =
        entity_tag -( signature )
        ;
#endif

#if 0
// entity_header ::=
// [ formal_generic_clause ]
//     [ formal_port_clause ]
auto const entity_header_def =
        -( formal_generic_clause )
        -( formal_port_clause )
        ;
#endif

#if 0
// entity_name_list ::=
// entity_designator { , entity_designator }
//     | others
//     | all
auto const entity_name_list_def =
        entity_designator >> ( entity_designator % ',' )
        | OTHERS
        | ALL
        ;
#endif

#if 0
// entity_specification ::=
// entity_name_list : entity_class
auto const entity_specification_def =
        entity_name_list > ':' entity_class
        ;
#endif

#if 0
// entity_statement ::=
// concurrent_assertion_statement
//     | passive_concurrent_procedure_call_statement
//     | passive_process_statement
auto const entity_statement_def =
        concurrent_assertion_statement
        | passive_concurrent_procedure_call_statement
        | passive_process_statement
        ;
#endif

#if 0
// entity_statement_part ::=
// { entity_statement }
auto const entity_statement_part_def =
{ entity_statement }
;
#endif

#if 0
// entity_tag ::=
// simple_name | character_literal | operator_symbol
auto const entity_tag_def =
        simple_name | character_literal | operator_symbol
        ;
#endif


// enumeration_literal ::=                                             [§ 3.1.1]
// identifier | character_literal
auto const enumeration_literal_def =
      identifier
    | character_literal
    ;



// enumeration_type_definition ::=
// ( enumeration_literal { , enumeration_literal } )
auto const enumeration_type_definition_def =
    enumeration_literal % ','
    ;


#if 0
// exit_statement ::=
// [ label : ] exit [ loop_label ] [ when condition ] ;
auto const exit_statement_def =
        -( LABEL > ':' ) EXIT -( loop_label ) -( WHEN condition ) > ';'
;
#endif


// exponent ::=                                                       [§ 13.4.1]
// E [ + ] integer | E - integer
auto const exponent_def =
    lexeme [
        char_("Ee") >> -char_("-+") >> integer
    ]
    ;


#if 0
// expression ::=
// relation { and relation }
//     | relation { or relation }
//     | relation { xor relation }
//     | relation [ nand relation ]
//     | relation [ nor relation ]
//     | relation { xnor relation }
auto const expression_def =
        relation { AND relation }
| relation { OR relation }
| relation { XOR relation }
| relation -( NAND relation )
    | relation -( NOR relation )
    | relation { XNOR relation }
;
#endif


// extended_digit ::=                                                 [§ 13.4.2]
// digit | letter
auto const extended_digit_def =
    char_("0-9a-fA-F")
    ;



// extended_identifier ::=                                            [§ 13.3.2]
// \ graphic_character { graphic_character } <backslash>
namespace detail {

    auto const extended_identifier_chars = x3::rule<struct _, std::string> { "extended_identifier (chars)" } =
         +( graphic_character - char_('\\') )
         ;

    auto const extended_identifier_atom = x3::rule<struct _, std::string> { "extended_identifier (atom)" } =
        lexeme [
               char_('\\')
            >> extended_identifier_chars
            >> char_('\\')
        ]
        ;
}

auto const extended_identifier_def =
    lexeme [
            detail::extended_identifier_atom
        >> *(detail::extended_identifier_atom % (char_('\\') >> char_('\\')))
    ]
    ;


#if 0
// factor ::=
// primary [ ** primary ]
//     | abs primary
//     | not primary
auto const factor_def =
        primary -( ** primary )
        | ABS primary
        | NOT primary
        ;
#endif

#if 0
// file_declaration ::=
// file identifier_list : subtype_indication file_open_information ] ;
auto const file_declaration_def =
        FILE identifier_list > ':' subtype_indication file_open_information ) > ';'
        ;
#endif

#if 0
        // file_logical_name ::=
        // string_expression
        auto const file_logical_name_def =
                string_expression
                ;
#endif

#if 0
        // file_open_information ::=
        // [ open file_open_kind_expression ] is file_logical_name
        auto const file_open_information_def =
                -( OPEN file_open_kind_expression ) IS file_logical_name
                ;
#endif

#if 0
        // file_type_definition ::=
        // file  of type_mark
        //     floating_type_definition  :=  range_constraint
        auto const file_type_definition_def =
                FILE  OF type_mark
                floating_type_definition   ":=" >   range_constraint
                ;
#endif

#if 0
        // formal_designator ::=
        // generic_name
        //     | port_name
        //     | parameter_name
        auto const formal_designator_def =
                generic_name
                | port_name
                | parameter_name
                ;
#endif

#if 0
        // formal_parameter_list ::=
        // parameter_interface_list
        auto const formal_parameter_list_def =
                parameter_interface_list
                ;
#endif

#if 0
        // formal_part ::=
        // formal_designator
        //     | function_name ( formal_designator )
        //     | type_mark ( formal_designator )
        auto const formal_part_def =
                formal_designator
                | function_name '(' formal_designator ')'     | type_mark '(' formal_designator )
;
#endif

#if 0
// full_type_declaration ::=
// type identifier is type_definition ;
auto const full_type_declaration_def =
        TYPE identifier IS type_definition > ';'
;
#endif

#if 0
// function_call ::=
// function_name [ ( actual_parameter_part ) ]
auto const function_call_def =
        function_name -( '(' actual_parameter_part ')' )
        ;
#endif

#if 0
// generate_statement ::=
// generate_label :
//     generation_scheme generate
//     [ { block_declarative_item }
//     begin ]
//     { concurrent_statement }
//     end generate [ generate_label ] ;
auto const generate_statement_def =
        generate_label > ':'     generation_scheme GENERATE
        -( { block_declarative_item }
BEGIN )
{ concurrent_statement }
END GENERATE -( generate_label ) > ';'
;
#endif

#if 0
// generation_scheme ::=
// for generate_parameter_specification
//     | if condition
auto const generation_scheme_def =
        FOR generate_parameter_specification
        | IF condition
        ;
#endif

#if 0
// generic_clause ::=
// generic ( generic_list ) ;
auto const generic_clause_def =
        GENERIC '(' generic_list ')' > ';'
;
#endif

#if 0
// generic_list ::=
// generic_interface_list
auto const generic_list_def =
        generic_interface_list
        ;
#endif

#if 0
// generic_map_aspect ::=
// generic map ( generic_association_list )
auto const generic_map_aspect_def =
        GENERIC MAP '(' generic_association_list )
;
#endif


// graphic_character ::=                                                [§ 13.1]
// basic_graphic_character | lower_case_letter | other_special_character
auto const graphic_character_def =
      basic_graphic_character
    | lower_case_letter
    | other_special_character
    ;


#if 0
// group_constituent ::=
// name | character_literal
auto const group_constituent_def =
        name | character_literal
        ;
#endif

#if 0
// group_constituent_list ::=
// group_constituent { , group_constituent }
auto const group_constituent_list_def =
        group_constituent >> ( group_constituent % ',' )
        ;
#endif

#if 0
// group_template_declaration ::=
// group identifier is ( entity_class_entry_list ) ;
auto const group_template_declaration_def =
        GROUP identifier IS '(' entity_class_entry_list ')' > ';'
;
#endif

#if 0
// group_declaration ::=
// group identifier : group_template_name ( group_constituent_list ) ;
auto const group_declaration_def =
        GROUP identifier > ':' group_template_name '(' group_constituent_list ')' > ';'
;
#endif

#if 0
// guarded_signal_specification ::=
// guarded_signal_list : type_mark
auto const guarded_signal_specification_def =
        guarded_signal_list > ':' type_mark
        ;
#endif


// identifier ::=                                                       [§ 13.3]
// basic_identifier | extended_identifier
namespace detail {

    /* The identifier is treated as string. The basic_identifier and
     * extended_identifier can be distuingished simply by test on leading (and
     * trailing) '/'. To enforce use of a single string member on AST node resp.
     * identifier the rule is splitted, otherwise ast::identifier has to handle
     * the variant type. Generalizing these identifiers simplifies (hopefully)
     * the type/identifier handling (without applying the boost visitor). */
    auto const identifier_str = x3::rule<struct _, std::string> { "identifier" } =
          basic_identifier
        | extended_identifier
        ;
}

auto const identifier_def =
    detail::identifier_str
    ;



// identifier_list ::=                                                 [§ 3.2.2]
// identifier { , identifier }
auto const identifier_list_def =
    identifier % ','
    ;


#if 0
// if_statement ::=
// [ if_label : ]
//     if condition then
//     sequence_of_statements
//     { elsif condition then
//     sequence_of_statements }
//     [ else
//     sequence_of_statements ]
//     end if [ if_label ] ;
auto const if_statement_def =
        -( if_label > ':' )
        IF condition THEN
        sequence_of_statements
        { ELSIF condition THEN
    sequence_of_statements }
-( ELSE
        sequence_of_statements )
    END IF -( if_label ) > ';'
;
#endif

#if 0
// incomplete_type_declaration ::=
// type identifier ;
auto const incomplete_type_declaration_def =
        TYPE identifier > ';'
;
#endif

#if 0
// index_constraint ::=
// ( discrete_range { , discrete_range } )
auto const index_constraint_def =
        ( discrete_range >> ( discrete_range % ',' ) )
        ;
#endif

#if 0
// index_specification ::=
// discrete_range
//     | static_expression
auto const index_specification_def =
        discrete_range
        | static_expression
        ;
#endif

#if 0
// index_subtype_definition ::=
// type_mark range <>
auto const index_subtype_definition_def =
        type_mark RANGE <>
;
#endif

#if 0
// indexed_name ::=
// prefix ( expression { , expression } )
auto const indexed_name_def =
        prefix '(' expression >> ( expression % ',' ) )
;
#endif

#if 0
// instantiated_unit ::=
// [ component ] component_name
//     | entity entity_name [ ( architecture_identifier ) ]
//     | configuration configuration_name
auto const instantiated_unit_def =
        -( COMPONENT ) component_name
        | ENTITY entity_name -( '(' architecture_identifier ')' )
        | CONFIGURATION configuration_name
        ;
#endif

#if 0
// instantiation_list ::=
// instantiation_label { , instantiation_label }
//     | others
//     | all
auto const instantiation_list_def =
        instantiation_label >> ( instantiation_label % ',' )
        | OTHERS
        | ALL
        ;
#endif


// integer ::=                                                         § 13.4.1]
// digit { [ underline ] digit }
auto const integer_def =
    lexeme [
        char_("0-9") >> *( -lit("_") >> char_("0-9") )
    ]
    ;


#if 0
// integer_type_definition ::=
// range_constraint
auto const integer_type_definition_def =
        range_constraint
        ;
#endif

#if 0
// interface_constant_declaration ::=
// [ constant ] identifier_list : [ in ] subtype_indication [ := static_expression ]
auto const interface_constant_declaration_def =
        -( CONSTANT ) identifier_list > ':' -( IN ) subtype_indication -(  ":=" >  static_expression )
        ;
#endif

#if 0
// interface_declaration ::=
// interface_constant_declaration
//     | interface_signal_declaration
//     | interface_variable_declaration
//     | interface_file_declaration
auto const interface_declaration_def =
        interface_constant_declaration
        | interface_signal_declaration
        | interface_variable_declaration
        | interface_file_declaration
        ;
#endif

#if 0
// interface_element ::=
// interface_declaration
auto const interface_element_def =
        interface_declaration
        ;
#endif

#if 0
// interface_file_declaration ::=
// file identifier_list : subtype_indication
auto const interface_file_declaration_def =
        FILE identifier_list > ':' subtype_indication
        ;
#endif

#if 0
// interface_list ::=
// interface_element { ; interface_element }
auto const interface_list_def =
        interface_element { > ';' interface_element }
;
#endif

#if 0
// interface_signal_declaration ::=
// [signal] identifier_list : [ mode ] subtype_indication [ bus ] [ := static_expression ]
auto const interface_signal_declaration_def =
        -(SIGNAL) identifier_list > ':' -( mode ) subtype_indication -( BUS ) -(  ":=" >  static_expression )
        ;
#endif

#if 0
// interface_variable_declaration ::=
// [variable] identifier_list : [ mode ] subtype_indication [ := static_expression ]
auto const interface_variable_declaration_def =
        -(VARIABLE) identifier_list > ':' -( mode ) subtype_indication -(  ":=" >  static_expression )
        ;
#endif

#if 0
// iteration_scheme ::=
// while condition
//     | for loop_parameter_specification
auto const iteration_scheme_def =
        WHILE condition
        | FOR loop_parameter_specification
        ;
#endif

#if 0
// label ::=
// identifier
auto const label_def =
        identifier
        ;
#endif


// letter ::=                                                         [§ 13.3.1]
// upper_case_letter | lower_case_letter
auto const letter_def =
    upper_case_letter | lower_case_letter
    ;



// letter_or_digit ::=                                                [§ 13.3.1]
// letter | digit
auto const letter_or_digit_def =
    letter | digit
    ;


#if 0
// library_clause ::=
// library logical_name_list ;
auto const library_clause_def =
        LIBRARY logical_name_list > ';'
;
#endif

#if 0
// library_unit ::=
// primary_unit
//     | secondary_unit
auto const library_unit_def =
        primary_unit
        | secondary_unit
        ;
#endif


// literal ::=                                                         [§ 7.3.1]
//       numeric_literal
//     | enumeration_literal
//     | string_literal
//     | bit_string_literal
//     | null
namespace detail {
    auto const null = x3::rule<struct _, ast::null> { "null" } =
        // FixMe: maybe better identifier
        NULL >> x3::attr( ast::null() )
    ;
}
auto const literal_def = /* Note, order changed since matters */
      enumeration_literal   // FixMe: Treats keyword NULL as identifier
    | string_literal
    | bit_string_literal
    | numeric_literal
    | detail::null
    ;


#if 0
// logical_name ::=
// identifier
auto const logical_name_def =
        identifier
        ;
#endif

#if 0
// logical_name_list ::=
// logical_name { , logical_name }
auto const logical_name_list_def =
        logical_name >> ( logical_name % ',' )
        ;
#endif

#if 0
// loop_statement ::=
// [ loop_label : ]
//     [ iteration_scheme ] loop
//     sequence_of_statements
//     end loop [ loop_label ] ;
auto const loop_statement_def =
        -( loop_label > ':' )
        -( iteration_scheme ) LOOP
        sequence_of_statements
        END LOOP -( loop_label ) > ';'
;
#endif

#if 0
// mode ::=
// in | out | inout | buffer | linkage
auto const mode_def =
        IN | OUT | INOUT | BUFFER | LINKAGE
        ;
#endif

#if 0
// name ::=
// simple_name
//     | operator_symbol
//     | selected_name
//     | indexed_name
//     | slice_name
//     | attribute_name
auto const name_def =
        simple_name
        | operator_symbol
        | selected_name
        | indexed_name
        | slice_name
        | attribute_name
        ;
#endif

#if 0
// next_statement ::=
// [ label : ] next [ loop_label ] [ when condition ] ;
auto const next_statement_def =
        -( LABEL > ':' ) NEXT -( loop_label ) -( WHEN condition ) > ';'
;
#endif

#if 0
// null_statement ::=
// [ label : ] null ;
auto const null_statement_def =
        -( LABEL > ':' ) NULL > ';'
;
#endif


// numeric_literal ::=                                                 [§ 7.3.1]
//       abstract_literal
//     | physical_literal
auto const numeric_literal_def = /* Note, order changed since matters */
      physical_literal
    | abstract_literal
    ;


#if 0
// object_declaration ::=
// constant_declaration
//     | signal_declaration
//     | variable_declaration
//     | file_declaration
auto const object_declaration_def =
        constant_declaration
        | signal_declaration
        | variable_declaration
        | file_declaration
        ;
#endif

#if 0
// operator_symbol ::=                                                   [§ 2.1]
// string_literal
auto const operator_symbol_def =
    string_literal
    ;
#endif

#if 0
// options ::=
// [ guarded ] [ delay_mechanism ]
auto const options_def =
        -( GUARDED ) -( delay_mechanism )
        ;
#endif

#if 0
// package_body ::=
// package body package_simple_name is
//     package_body_declarative_part
//     end [ package body ] [ package_simple_name ] ;
auto const package_body_def =
        PACKAGE BODY package_simple_name IS
        package_body_declarative_part
        END -( PACKAGE BODY ) -( package_simple_name ) > ';'
;
#endif

#if 0
// package_body_declarative_item ::=
// subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const package_body_declarative_item_def =
        subprogram_declaration
        | subprogram_body
        | type_declaration
        | subtype_declaration
        | constant_declaration
        | shared_variable_declaration
        | file_declaration
        | alias_declaration
        | use_clause
        | group_template_declaration
        | group_declaration
        ;
#endif

#if 0
// package_body_declarative_part ::=
// { package_body_declarative_item }
auto const package_body_declarative_part_def =
{ package_body_declarative_item }
;
#endif

#if 0
// package_declaration ::=
// package identifier is
//     package_declarative_part
//     end [ package ] [ package_simple_name ] ;
auto const package_declaration_def =
        PACKAGE identifier IS
        package_declarative_part
        END -( PACKAGE ) -( package_simple_name ) > ';'
;
#endif

#if 0
// package_declarative_item ::=
// subprogram_declaration
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | signal_declaration
//     | shared_variable_declaration
//     | file_declaration
//     | alias_declaration
//     | component_declaration
//     | attribute_declaration
//     | attribute_specification
//     | disconnection_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const package_declarative_item_def =
        subprogram_declaration
        | type_declaration
        | subtype_declaration
        | constant_declaration
        | signal_declaration
        | shared_variable_declaration
        | file_declaration
        | alias_declaration
        | component_declaration
        | attribute_declaration
        | attribute_specification
        | disconnection_specification
        | use_clause
        | group_template_declaration
        | group_declaration
        ;
#endif

#if 0
// package_declarative_part ::=
// { package_declarative_item }
auto const package_declarative_part_def =
{ package_declarative_item }
;
#endif

#if 0
// parameter_specification ::=
// identifier in discrete_range
auto const parameter_specification_def =
        identifier IN discrete_range
        ;
#endif


// physical_literal ::=                                                [§ 3.1.3]
// [ abstract_literal ] unit_name
namespace detail {

    /* Note, the LRM doesn't specify the allowed characters, hence it's assumed
     * that it follows the natural conventions. */
    auto const unit_name = as_rule<std::string>(
        lexeme[ +char_("A-Za-z") ]);

}

auto const physical_literal_def =
    -abstract_literal >> (detail::unit_name - keyword)
    ;


#if 0
// physical_type_definition ::=
// range_constraint
//     units
//     base_unit_declaration
//     { secondary_unit_declaration }
//     end units [ physical_type_simple_name ]
auto const physical_type_definition_def =
        range_constraint
        UNITS
        base_unit_declaration
        { secondary_unit_declaration }
END UNITS -( physical_type_simple_name )
    ;
#endif

#if 0
// port_clause ::=
// port ( port_list ) ;
auto const port_clause_def =
        PORT '(' port_list ')' > ';'
;
#endif

#if 0
// port_list ::=
// port_interface_list
auto const port_list_def =
        port_interface_list
        ;
#endif

#if 0
// port_map_aspect ::=
// port map ( port_association_list )
auto const port_map_aspect_def =
        PORT MAP '(' port_association_list )
;
#endif

#if 0
// prefix ::=
// name
//     | function_call
auto const prefix_def =
        name
        | function_call
        ;
#endif

#if 0
// primary ::=
// name
//     | literal
//     | aggregate
//     | function_call
//     | qualified_expression
//     | type_conversion
//     | allocator
//     | ( expression )
auto const primary_def =
        name
        | LITERAL
        | aggregate
        | function_call
        | qualified_expression
        | type_conversion
        | allocator
        | '(' expression )
;
#endif

#if 0
// primary_unit ::=
// entity_declaration
//     | configuration_declaration
//     | package_declaration
auto const primary_unit_def =
        entity_declaration
        | configuration_declaration
        | package_declaration
        ;
#endif

#if 0
// procedure_call ::=
// procedure_name [ ( actual_parameter_part ) ]
auto const procedure_call_def =
        procedure_name -( '(' actual_parameter_part ')' )
        ;
#endif

#if 0
// procedure_call_statement ::=
// [ label : ] procedure_call ;
auto const procedure_call_statement_def =
        -( LABEL > ':' ) procedure_call > ';'
;
#endif

#if 0
// process_declarative_item ::=
// subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | variable_declaration
//     | file_declaration
//     | alias_declaration
//     | attribute_declaration
//     | attribute_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const process_declarative_item_def =
        subprogram_declaration
        | subprogram_body
        | type_declaration
        | subtype_declaration
        | constant_declaration
        | variable_declaration
        | file_declaration
        | alias_declaration
        | attribute_declaration
        | attribute_specification
        | use_clause
        | group_template_declaration
        | group_declaration
        ;
#endif

#if 0
// process_declarative_part ::=
// { process_declarative_item }
auto const process_declarative_part_def =
{ process_declarative_item }
;
#endif

#if 0
// process_statement ::=
// [ process_label : ]
//     [ postponed ] process [ ( sensitivity_list ) ] [ is ]
//     process_declarative_part
//     begin
//     process_statement_part
//     end [ postponed ] process [ process_label ] ;
auto const process_statement_def =
        -( process_label > ':' )
        -( POSTPONED ) PROCESS -( '(' sensitivity_list ')' ) -( IS )
        process_declarative_part
        BEGIN
        process_statement_part
        END -( POSTPONED ) PROCESS -( process_label ) > ';'
;
#endif

#if 0
// process_statement_part ::=
// { sequential_statement }
auto const process_statement_part_def =
{ sequential_statement }
;
#endif

#if 0
// qualified_expression ::=
// type_mark ' ( expression )
//     | type_mark ' aggregate
auto const qualified_expression_def =
        type_mark ' '(' expression ')'     | type_mark ' aggregate
        ;
#endif

#if 0
// range ::=
// range_attribute_name
//     | simple_expression direction simple_expression
auto const range_def =
        range_attribute_name
        | simple_expression direction simple_expression
        ;
#endif

#if 0
// range_constraint ::=
// range range
auto const range_constraint_def =
        RANGE RANGE
        ;
#endif

#if 0
// record_type_definition ::=
// record
//     element_declaration
//     { element_declaration }
//     end record [ record_type_simple_name ]
auto const record_type_definition_def =
        RECORD
        element_declaration
        { element_declaration }
END RECORD -( record_type_simple_name )
    ;
#endif

#if 0
// relation ::=
// shift_expression [ relational_operator shift_expression ]
auto const relation_def =
        shift_expression -( relational_operator shift_expression )
        ;
#endif

#if 0
// report_statement ::=
// [ label : ]
//     report expression
//     [ severity expression ] ;
auto const report_statement_def =
        -( LABEL > ':' )
        REPORT expression
        -( SEVERITY expression ) > ';'
;
#endif

#if 0
// return_statement ::=
// [ label : ] return [ expression ] ;
auto const return_statement_def =
        -( LABEL > ':' ) RETURN -( expression ) > ';'
;
#endif

#if 0
// scalar_type_definition ::=
// enumeration_type_definition   | integer_type_definition
//     | floating_type_definition      | physical_type_definition
auto const scalar_type_definition_def =
        enumeration_type_definition   | integer_type_definition
        | floating_type_definition      | physical_type_definition
        ;
#endif

#if 0
// secondary_unit ::=
// architecture_body
//     | package_body
auto const secondary_unit_def =
        architecture_body
        | package_body
        ;
#endif

#if 0
// secondary_unit_declaration ::=
// identifier = physical_literal ;
auto const secondary_unit_declaration_def =
        identifier = physical_literal > ';'
;
#endif

#if 0
// selected_name ::=
// prefix . suffix
auto const selected_name_def =
        prefix . suffix
        ;
#endif

#if 0
// selected_signal_assignment ::=
// with expression select
//     target    <= options selected_waveforms ;
auto const selected_signal_assignment_def =
        WITH expression SELECT
        target    <= options selected_waveforms > ';'
;
#endif

#if 0
// selected_waveforms ::=
// { waveform when choices , }
//     waveform when choices
auto const selected_waveforms_def =
{ waveform WHEN choices , }
waveform WHEN choices
;
#endif

#if 0
// sensitivity_clause ::=
// on sensitivity_list
auto const sensitivity_clause_def =
        ON sensitivity_list
        ;
#endif

#if 0
// sensitivity_list ::=
// signal_name { , signal_name }
auto const sensitivity_list_def =
        signal_name >> ( signal_name % ',' )
        ;
#endif

#if 0
// sequence_of_statements ::=
// { sequential_statement }
auto const sequence_of_statements_def =
{ sequential_statement }
;
#endif

#if 0
// sequential_statement ::=
// wait_statement
//     | assertion_statement
//     | report_statement
//     | signal_assignment_statement
//     | variable_assignment_statement
//     | procedure_call_statement
//     | if_statement
//     | case_statement
//     | loop_statement
//     | next_statement
//     | exit_statement
//     | return_statement
//     | null_statement
auto const sequential_statement_def =
        wait_statement
        | assertion_statement
        | report_statement
        | signal_assignment_statement
        | variable_assignment_statement
        | procedure_call_statement
        | if_statement
        | case_statement
        | loop_statement
        | next_statement
        | exit_statement
        | return_statement
        | null_statement
        ;
#endif

#if 0
// shift_expression ::=
// simple_expression [ shift_operator simple_expression ]
auto const shift_expression_def =
        simple_expression -( shift_operator simple_expression )
        ;
#endif

#if 0
// sign ::=
// + | -
auto const sign_def =
        + | -
        ;
#endif

#if 0
// signal_assignment_statement ::=
// [ label : ] target <= [ delay_mechanism ] waveform ;
auto const signal_assignment_statement_def =
        -( LABEL > ':' ) target <= -( delay_mechanism ) waveform > ';'
;
#endif

#if 0
// signal_declaration ::=
// signal identifier_list : subtype_indication [ signal_kind ] [ := expression ] ;
auto const signal_declaration_def =
        SIGNAL identifier_list > ':' subtype_indication -( signal_kind ) -(  ":=" >  expression ) > ';'
;
#endif

#if 0
// signal_kind ::=
// register  |  bus
auto const signal_kind_def =
        REGISTER  |  BUS
        ;
#endif

#if 0
// signal_list ::=
// signal_name { , signal_name }
//     | others
//     | all
auto const signal_list_def =
        signal_name >> ( signal_name % ',' )
        | OTHERS
        | ALL
        ;
#endif

#if 0
// signature ::=
// [ [ type_mark { , type_mark } ] [ return type_mark ] ]
auto const signature_def =
        -( -( type_mark >> ( type_mark % ',' ) ) -( RETURN type_mark ) )
        ;
#endif

#if 0
// simple_expression ::=
// [ sign ] term { adding_operator term }
auto const simple_expression_def =
        -( sign ) term { adding_operator term }
;
#endif


// simple_name ::=                                                       [§ 6.2]
// identifier
auto const simple_name_def =
    detail::identifier_str
    ;


#if 0
// slice_name ::=
// prefix ( discrete_range )
auto const slice_name_def =
        prefix '(' discrete_range )
;
#endif


// string_literal ::=                                                   [§ 13.6]
// " { graphic_character } "
auto const string_literal_def =
    lexeme[
        (      '"'
            >> *( ( graphic_character - '"'  )
                | ( char_('"') >> char_('"') )
                )
            >> '"'
        )
        |
        (      '%' // LRM [§ 13.10]
            >> *( ( graphic_character - '%'  )
                | ( char_('%') >> char_('%') )
                )
            >> '%'
        )
    ]
    ;


#if 0
// subprogram_body ::=
// subprogram_specification is
//     subprogram_declarative_part
//     begin
//     subprogram_statement_part
//     end [ subprogram_kind ] [ designator ] ;
auto const subprogram_body_def =
        subprogram_specification IS
        subprogram_declarative_part
        BEGIN
        subprogram_statement_part
        END -( subprogram_kind ) -( designator ) > ';'
;
#endif

#if 0
// subprogram_declaration ::=
// subprogram_specification ;
auto const subprogram_declaration_def =
        subprogram_specification > ';'
;
#endif

#if 0
// subprogram_declarative_item ::=
// subprogram_declaration
//     | subprogram_body
//     | type_declaration
//     | subtype_declaration
//     | constant_declaration
//     | variable_declaration
//     | file_declaration
//     | alias_declaration
//     | attribute_declaration
//     | attribute_specification
//     | use_clause
//     | group_template_declaration
//     | group_declaration
auto const subprogram_declarative_item_def =
        subprogram_declaration
        | subprogram_body
        | type_declaration
        | subtype_declaration
        | constant_declaration
        | variable_declaration
        | file_declaration
        | alias_declaration
        | attribute_declaration
        | attribute_specification
        | use_clause
        | group_template_declaration
        | group_declaration
        ;
#endif

#if 0
// subprogram_declarative_part ::=
// { subprogram_declarative_item }
auto const subprogram_declarative_part_def =
{ subprogram_declarative_item }
;
#endif

#if 0
// subprogram_kind ::=
// procedure | function
auto const subprogram_kind_def =
        PROCEDURE | FUNCTION
        ;
#endif

#if 0
// subprogram_specification ::=
// procedure designator [ ( formal_parameter_list ) ]
//     | [ pure | impure ]  function designator [ ( formal_parameter_list ) ]
//     return type_mark
auto const subprogram_specification_def =
        PROCEDURE designator -( '(' formal_parameter_list ')' )
        | -( PURE | IMPURE )  FUNCTION designator -( '(' formal_parameter_list ')' )
        RETURN type_mark
        ;
#endif

#if 0
// subprogram_statement_part ::=
// { sequential_statement }
auto const subprogram_statement_part_def =
{ sequential_statement }
;
#endif

#if 0
// subtype_declaration ::=
// subtype identifier is subtype_indication ;
auto const subtype_declaration_def =
        SUBTYPE identifier IS subtype_indication > ';'
;
#endif

#if 0
// subtype_indication ::=
// [ resolution_function_name ] type_mark [ constraint ]
auto const subtype_indication_def =
        -( resolution_function_name ) type_mark -( constraint )
        ;
#endif


// suffix ::=                                                            [§ 6.3]
//       simple_name
//     | character_literal
//     | operator_symbol
//     | all
auto const suffix_def =
      simple_name       // FixMe: treats keyword NULL as identifier
    | character_literal
//  | operator_symbol   // FixMe: No idea about operator_symbol, aka string_literal
    | ALL
    ;


#if 0
// target ::=
// name
//     | aggregate
auto const target_def =
        name
        | aggregate
        ;
#endif

#if 0
// term ::=
// factor { multiplying_operator factor }
auto const term_def =
        factor { multiplying_operator factor }
;
#endif

#if 0
// timeout_clause ::=
// for time_expression
auto const timeout_clause_def =
        FOR time_expression
        ;
#endif

#if 0
// type_conversion ::=
// type_mark ( expression )
auto const type_conversion_def =
        type_mark '(' expression )
;
#endif

#if 0
// type_declaration ::=
// full_type_declaration
//     | incomplete_type_declaration
auto const type_declaration_def =
        full_type_declaration
        | incomplete_type_declaration
        ;
#endif

#if 0
// type_definition ::=
// scalar_type_definition
//     | composite_type_definition
//     | access_type_definition
//     | file_type_definition
auto const type_definition_def =
        scalar_type_definition
        | composite_type_definition
        | access_type_definition
        | file_type_definition
        ;
#endif


// type_mark ::=
//       type_name
//     | subtype_name
/* Note, there is no way to distinguish between type_name and subtype_name at
 * parser level. It's used as simple string parser for symantic sugar at parser
 * level*/
auto const type_mark_def =
    detail::identifier_str
    ;


#if 0
// unconstrained_array_definition ::=
// array ( index_subtype_definition { , index_subtype_definition } )
//     of element_subtype_indication
auto const unconstrained_array_definition_def =
        ARRAY '(' index_subtype_definition >> ( index_subtype_definition % ',' ) ')'     OF element_subtype_indication
        ;
#endif

#if 0
// use_clause ::=
// use selected_name { , selected_name } ;
auto const use_clause_def =
        USE selected_name >> ( selected_name % ',' ) > ';'
;
#endif

#if 0
// variable_assignment_statement ::=
// [ label : ] target  := expression ;
auto const variable_assignment_statement_def =
        -( LABEL > ':' ) target   ":=" >  expression > ';'
;
#endif

#if 0
// variable_declaration ::=
// [ shared ] variable identifier_list : subtype_indication [ := expression ] ;
auto const variable_declaration_def =
        -( SHARED ) VARIABLE identifier_list > ':' subtype_indication -(  ":=" >  expression ) > ';'
;
#endif

#if 0
// wait_statement ::=
// [ label : ] wait [ sensitivity_clause ] [ condition_clause ] [ timeout_clause ] ;
auto const wait_statement_def =
        -( LABEL > ':' ) WAIT -( sensitivity_clause ) -( condition_clause ) -( timeout_clause ) > ';'
;
#endif

#if 0
// waveform ::=
// waveform_element { , waveform_element }
//     | unaffected
auto const waveform_def =
        waveform_element >> ( waveform_element % ',' )
        | UNAFFECTED
        ;
#else
auto const waveform_def = *x3::char_ ;

#endif

#if 0
// waveform_element ::=
// value_expression [ after time_expression ]
//     | null [ after time_expression ]
auto const waveform_element_def =
    value_expression -( AFTER time_expression )
    | NULL -( AFTER time_expression )
    ;
#endif

BOOST_SPIRIT_DEFINE(
        abstract_literal,
        //    access_type_definition,
        //    actual_designator,
        //    actual_parameter_part,
        //    actual_part,
        //    aggregate,
        //    alias_declaration,
        //    alias_designator,
        //    allocator,
        //    architecture_body,
        //    architecture_declarative_part,
        //    architecture_statement_part,
        //    array_type_definition,
        //    assertion,
        //    assertion_statement,
        //    association_element,
        //    association_list,
        //    attribute_declaration,
        //    attribute_designator,
        //    attribute_name,
        //    attribute_specification,
        //base,
        //    base_unit_declaration,
        based_integer,
        based_literal,
        //    basic_character,
        basic_graphic_character,
        basic_identifier,
        //    binding_indication,
        bit_string_literal,
        //    block_configuration,
        //    block_declarative_item,
        //    block_declarative_part,
        //    block_header,
        //    block_specification,
        //    block_statement,
        //    block_statement_part,
        //    case_statement,
        //    case_statement_alternative,
        character_literal,
        //    choice,
        //    choices,
        //    component_configuration,
        //    component_declaration,
        //    component_instantiation_statement,
        //    component_specification,
        //    composite_type_definition,
        //    concurrent_assertion_statement,
        //    concurrent_procedure_call_statement,
        //    concurrent_signal_assignment_statement,
        //    concurrent_statement,
        //    condition,
        //    condition_clause,
        //    conditional_signal_assignment,
        //    conditional_waveforms,
        //    configuration_declaration,
        //    configuration_declarative_item,
        //    configuration_declarative_part,
        //    configuration_item,
        //    configuration_specification,
        //    constant_declaration,
        //    constrained_array_definition,
        //    constraint,
        //    context_clause,
        //    context_item,
        decimal_literal,
        //    declaration,
        //    delay_mechanism,
        //    design_file,
        //    design_unit,
        //    designator,
        direction,
        //    disconnection_specification,
        //    discrete_range,
        //    element_association,
        //    element_declaration,
        //    element_subtype_definition,
        //    entity_aspect,
        //    entity_class,
        //    entity_class_entry,
        //    entity_class_entry_list,
        //    entity_declaration,
        //    entity_declarative_item,
        //    entity_declarative_part,
        //    entity_designator,
        //    entity_header,
        //    entity_name_list,
        //    entity_specification,
        //    entity_statement,
        //    entity_statement_part,
        //    entity_tag,
        enumeration_literal,
        enumeration_type_definition,
        //    exit_statement,
        exponent,
        //    expression,
        extended_digit,
        extended_identifier,
        //    factor,
        //    file_declaration,
        //    file_logical_name,
        //    file_open_information,
        //    file_type_definition,
        //    formal_designator,
        //    formal_parameter_list,
        //    formal_part,
        //    full_type_declaration,
        //    function_call,
        //    generate_statement,
        //    generation_scheme,
        //    generic_clause,
        //    generic_list,
        //    generic_map_aspect,
        graphic_character,
        //    group_constituent,
        //    group_constituent_list,
        //    group_template_declaration,
        //    group_declaration,
        //    guarded_signal_specification,
        identifier,
        identifier_list,
        //    if_statement,
        //    incomplete_type_declaration,
        //    index_constraint,
        //    index_specification,
        //    index_subtype_definition,
        //    indexed_name,
        //    instantiated_unit,
        //    instantiation_list,
        integer,
        //    integer_type_definition,
        //    interface_constant_declaration,
        //    interface_declaration,
        //    interface_element,
        //    interface_file_declaration,
        //    interface_list,
        //    interface_signal_declaration,
        //    interface_variable_declaration,
        //    iteration_scheme,
        //    label,
        letter,
        letter_or_digit,
        //    library_clause,
        //    library_unit,
        literal,
        //    logical_name,
        //    logical_name_list,
        //    loop_statement,
        //    mode,
        //    name,
        //    next_statement,
        //    null_statement,
        numeric_literal,
        //    object_declaration,
        //    operator_symbol,
        //    options,
        //    package_body,
        //    package_body_declarative_item,
        //    package_body_declarative_part,
        //    package_declaration,
        //    package_declarative_item,
        //    package_declarative_part,
        //    parameter_specification,
        physical_literal,
        //    physical_type_definition,
        //    port_clause,
        //    port_list,
        //    port_map_aspect,
        //    prefix,
        //    primary,
        //    primary_unit,
        //    procedure_call,
        //    procedure_call_statement,
        //    process_declarative_item,
        //    process_declarative_part,
        //    process_statement,
        //    process_statement_part,
        //    qualified_expression,
        //    range,
        //    range_constraint,
        //    record_type_definition,
        //    relation,
        //    report_statement,
        //    return_statement,
        //    scalar_type_definition,
        //    secondary_unit,
        //    secondary_unit_declaration,
        //    selected_name,
        //    selected_signal_assignment,
        //    selected_waveforms,
        //    sensitivity_clause,
        //    sensitivity_list,
        //    sequence_of_statements,
        //    sequential_statement,
        //    shift_expression,
        //    sign,
        //    signal_assignment_statement,
        //    signal_declaration,
        //    signal_kind,
        //    signal_list,
        //    signature,
        //    simple_expression,
        simple_name,
        //    slice_name,
        string_literal,
        //    subprogram_body,
        //    subprogram_declaration,
        //    subprogram_declarative_item,
        //    subprogram_declarative_part,
        //    subprogram_kind,
        //    subprogram_specification,
        //    subprogram_statement_part,
        //    subtype_declaration,
        //    subtype_indication,
        suffix,
        //    target,
        //    term,
        //    timeout_clause,
        //    type_conversion,
        //    type_declaration,
        //    type_definition,
        //    type_mark,
        //    unconstrained_array_definition,
        //    use_clause,
        //    variable_assignment_statement,
        //    variable_declaration,
        //    wait_statement,
        waveform
        //    waveform_element
);


/*
 * Annotation and Error handling
 */
struct bit_string_literal_class : x3::annotate_on_success {};

//struct bit_string_literal_class : x3::annotate_on_success, error_handler_base {};


} } } // namespace eda.vhdl93.parser


/*
 * VHDL Skipper
 */
namespace eda { namespace vhdl93 { namespace parser {

// VHDL char set is iso8859:1

namespace x3 = boost::spirit::x3;
namespace iso8859_1 = boost::spirit::x3::iso8859_1;

using iso8859_1::char_;
using iso8859_1::space;


struct skipper_class;
typedef x3::rule<skipper_class> skipper_type;
skipper_type const skipper { "skipper" };

auto const skipper_def =
      space
    | "--" >> *(char_ - x3::eol) >> x3::eol
    ;

BOOST_SPIRIT_DEFINE(skipper)


} } } // namespace eda.vhdl93.parser



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_PARSER_GRAMMAR_DEF_HPP_ */
