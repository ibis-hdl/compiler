/*
 * grammar_api.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include "grammar_api.hpp"


/*
 * VHDL93 Grammar Test Bench API Definition
 */

namespace eda { namespace vhdl93 {

#if 0
parser::abstract_literal_type const& abstract_literal() {
	return parser::abstract_literal;
}
#endif

#if 0
parser::access_type_definition_type const& access_type_definition() {
	return parser::access_type_definition;
}
#endif

#if 0
parser::actual_designator_type const& actual_designator() {
	return parser::actual_designator;
}
#endif

#if 0
parser::actual_parameter_part_type const& actual_parameter_part() {
	return parser::actual_parameter_part;
}
#endif

#if 0
parser::actual_part_type const& actual_part() {
	return parser::actual_part;
}
#endif

#if 0
parser::adding_operator_type const& adding_operator() {
	return parser::adding_operator;
}
#endif

#if 0
parser::aggregate_type const& aggregate() {
	return parser::aggregate;
}
#endif

#if 0
parser::alias_declaration_type const& alias_declaration() {
	return parser::alias_declaration;
}
#endif

#if 0
parser::alias_designator_type const& alias_designator() {
	return parser::alias_designator;
}
#endif

#if 0
parser::allocator_type const& allocator() {
	return parser::allocator;
}
#endif

#if 0
parser::architecture_body_type const& architecture_body() {
	return parser::architecture_body;
}
#endif

#if 0
parser::architecture_declarative_part_type const& architecture_declarative_part() {
	return parser::architecture_declarative_part;
}
#endif

#if 0
parser::architecture_statement_part_type const& architecture_statement_part() {
	return parser::architecture_statement_part;
}
#endif

#if 0
parser::array_type_definition_type const& array_type_definition() {
	return parser::array_type_definition;
}
#endif

#if 0
parser::assertion_type const& assertion() {
	return parser::assertion;
}
#endif

#if 0
parser::assertion_statement_type const& assertion_statement() {
	return parser::assertion_statement;
}
#endif

#if 0
parser::association_element_type const& association_element() {
	return parser::association_element;
}
#endif

#if 0
parser::association_list_type const& association_list() {
	return parser::association_list;
}
#endif

#if 0
parser::attribute_declaration_type const& attribute_declaration() {
	return parser::attribute_declaration;
}
#endif

#if 0
parser::attribute_designator_type const& attribute_designator() {
	return parser::attribute_designator;
}
#endif

#if 0
parser::attribute_name_type const& attribute_name() {
	return parser::attribute_name;
}
#endif

#if 0
parser::attribute_specification_type const& attribute_specification() {
	return parser::attribute_specification;
}
#endif

#if 0
parser::base_type const& base() {
	return parser::base;
}
#endif

#if 0
parser::base_specifier_type const& base_specifier() {
	return parser::base_specifier;
}
#endif

#if 0
parser::base_unit_declaration_type const& base_unit_declaration() {
	return parser::base_unit_declaration;
}
#endif

#if 0
parser::based_integer_type const& based_integer() {
	return parser::based_integer;
}
#endif

#if 0
parser::based_literal_type const& based_literal() {
	return parser::based_literal;
}
#endif

#if 0
parser::basic_character_type const& basic_character() {
	return parser::basic_character;
}
#endif

#if 0
parser::basic_graphic_character_type const& basic_graphic_character() {
	return parser::basic_graphic_character;
}
#endif

#if 0
parser::basic_identifier_type const& basic_identifier() {
	return parser::basic_identifier;
}
#endif

#if 0
parser::binding_indication_type const& binding_indication() {
	return parser::binding_indication;
}
#endif

#if 0
parser::bit_string_literal_type const& bit_string_literal() {
	return parser::bit_string_literal;
}
#endif

#if 0
parser::bit_value_type const& bit_value() {
	return parser::bit_value;
}
#endif

#if 0
parser::block_configuration_type const& block_configuration() {
	return parser::block_configuration;
}
#endif

#if 0
parser::block_declarative_item_type const& block_declarative_item() {
	return parser::block_declarative_item;
}
#endif

#if 0
parser::block_declarative_part_type const& block_declarative_part() {
	return parser::block_declarative_part;
}
#endif

#if 0
parser::block_header_type const& block_header() {
	return parser::block_header;
}
#endif

#if 0
parser::block_specification_type const& block_specification() {
	return parser::block_specification;
}
#endif

#if 0
parser::block_statement_type const& block_statement() {
	return parser::block_statement;
}
#endif

#if 0
parser::block_statement_part_type const& block_statement_part() {
	return parser::block_statement_part;
}
#endif

#if 0
parser::case_statement_type const& case_statement() {
	return parser::case_statement;
}
#endif

#if 0
parser::case_statement_alternative_type const& case_statement_alternative() {
	return parser::case_statement_alternative;
}
#endif

#if 0
parser::character_literal_type const& character_literal() {
	return parser::character_literal;
}
#endif

#if 0
parser::choice_type const& choice() {
	return parser::choice;
}
#endif

#if 0
parser::choices_type const& choices() {
	return parser::choices;
}
#endif

#if 0
parser::component_configuration_type const& component_configuration() {
	return parser::component_configuration;
}
#endif

#if 0
parser::component_declaration_type const& component_declaration() {
	return parser::component_declaration;
}
#endif

#if 0
parser::component_instantiation_statement_type const& component_instantiation_statement() {
	return parser::component_instantiation_statement;
}
#endif

#if 0
parser::component_specification_type const& component_specification() {
	return parser::component_specification;
}
#endif

#if 0
parser::composite_type_definition_type const& composite_type_definition() {
	return parser::composite_type_definition;
}
#endif

#if 0
parser::concurrent_assertion_statement_type const& concurrent_assertion_statement() {
	return parser::concurrent_assertion_statement;
}
#endif

#if 0
parser::concurrent_procedure_call_statement_type const& concurrent_procedure_call_statement() {
	return parser::concurrent_procedure_call_statement;
}
#endif

#if 0
parser::concurrent_signal_assignment_statement_type const& concurrent_signal_assignment_statement() {
	return parser::concurrent_signal_assignment_statement;
}
#endif

#if 0
parser::concurrent_statement_type const& concurrent_statement() {
	return parser::concurrent_statement;
}
#endif

#if 0
parser::condition_type const& condition() {
	return parser::condition;
}
#endif

#if 0
parser::condition_clause_type const& condition_clause() {
	return parser::condition_clause;
}
#endif

#if 0
parser::conditional_signal_assignment_type const& conditional_signal_assignment() {
	return parser::conditional_signal_assignment;
}
#endif

#if 0
parser::conditional_waveforms_type const& conditional_waveforms() {
	return parser::conditional_waveforms;
}
#endif

#if 0
parser::configuration_declaration_type const& configuration_declaration() {
	return parser::configuration_declaration;
}
#endif

#if 0
parser::configuration_declarative_item_type const& configuration_declarative_item() {
	return parser::configuration_declarative_item;
}
#endif

#if 0
parser::configuration_declarative_part_type const& configuration_declarative_part() {
	return parser::configuration_declarative_part;
}
#endif

#if 0
parser::configuration_item_type const& configuration_item() {
	return parser::configuration_item;
}
#endif

#if 0
parser::configuration_specification_type const& configuration_specification() {
	return parser::configuration_specification;
}
#endif

#if 0
parser::constant_declaration_type const& constant_declaration() {
	return parser::constant_declaration;
}
#endif

#if 0
parser::constrained_array_definition_type const& constrained_array_definition() {
	return parser::constrained_array_definition;
}
#endif

#if 0
parser::constraint_type const& constraint() {
	return parser::constraint;
}
#endif

#if 0
parser::context_clause_type const& context_clause() {
	return parser::context_clause;
}
#endif

#if 0
parser::context_item_type const& context_item() {
	return parser::context_item;
}
#endif

#if 0
parser::decimal_literal_type const& decimal_literal() {
	return parser::decimal_literal;
}
#endif

#if 0
parser::declaration_type const& declaration() {
	return parser::declaration;
}
#endif

#if 0
parser::delay_mechanism_type const& delay_mechanism() {
	return parser::delay_mechanism;
}
#endif

#if 0
parser::design_file_type const& design_file() {
	return parser::design_file;
}
#endif

#if 0
parser::design_unit_type const& design_unit() {
	return parser::design_unit;
}
#endif

#if 0
parser::designator_type const& designator() {
	return parser::designator;
}
#endif

#if 0
parser::direction_type const& direction() {
	return parser::direction;
}
#endif

#if 0
parser::disconnection_specification_type const& disconnection_specification() {
	return parser::disconnection_specification;
}
#endif

#if 0
parser::discrete_range_type const& discrete_range() {
	return parser::discrete_range;
}
#endif

#if 0
parser::element_association_type const& element_association() {
	return parser::element_association;
}
#endif

#if 0
parser::element_declaration_type const& element_declaration() {
	return parser::element_declaration;
}
#endif

#if 0
parser::element_subtype_definition_type const& element_subtype_definition() {
	return parser::element_subtype_definition;
}
#endif

#if 0
parser::entity_aspect_type const& entity_aspect() {
	return parser::entity_aspect;
}
#endif

#if 0
parser::entity_class_type const& entity_class() {
	return parser::entity_class;
}
#endif

#if 0
parser::entity_class_entry_type const& entity_class_entry() {
	return parser::entity_class_entry;
}
#endif

#if 0
parser::entity_class_entry_list_type const& entity_class_entry_list() {
	return parser::entity_class_entry_list;
}
#endif

#if 0
parser::entity_declaration_type const& entity_declaration() {
	return parser::entity_declaration;
}
#endif

#if 0
parser::entity_declarative_item_type const& entity_declarative_item() {
	return parser::entity_declarative_item;
}
#endif

#if 0
parser::entity_declarative_part_type const& entity_declarative_part() {
	return parser::entity_declarative_part;
}
#endif

#if 0
parser::entity_designator_type const& entity_designator() {
	return parser::entity_designator;
}
#endif

#if 0
parser::entity_header_type const& entity_header() {
	return parser::entity_header;
}
#endif

#if 0
parser::entity_name_list_type const& entity_name_list() {
	return parser::entity_name_list;
}
#endif

#if 0
parser::entity_specification_type const& entity_specification() {
	return parser::entity_specification;
}
#endif

#if 0
parser::entity_statement_type const& entity_statement() {
	return parser::entity_statement;
}
#endif

#if 0
parser::entity_statement_part_type const& entity_statement_part() {
	return parser::entity_statement_part;
}
#endif

#if 0
parser::entity_tag_type const& entity_tag() {
	return parser::entity_tag;
}
#endif

#if 0
parser::enumeration_literal_type const& enumeration_literal() {
	return parser::enumeration_literal;
}
#endif

#if 0
parser::enumeration_type_definition_type const& enumeration_type_definition() {
	return parser::enumeration_type_definition;
}
#endif

#if 0
parser::exit_statement_type const& exit_statement() {
	return parser::exit_statement;
}
#endif

#if 0
parser::exponent_type const& exponent() {
	return parser::exponent;
}
#endif

#if 0
parser::expression_type const& expression() {
	return parser::expression;
}
#endif

#if 0
parser::extended_digit_type const& extended_digit() {
	return parser::extended_digit;
}
#endif

#if 0
parser::extended_identifier_type const& extended_identifier() {
	return parser::extended_identifier;
}
#endif

#if 0
parser::factor_type const& factor() {
	return parser::factor;
}
#endif

#if 0
parser::file_declaration_type const& file_declaration() {
	return parser::file_declaration;
}
#endif

#if 0
parser::file_logical_name_type const& file_logical_name() {
	return parser::file_logical_name;
}
#endif

#if 0
parser::file_open_information_type const& file_open_information() {
	return parser::file_open_information;
}
#endif

#if 0
parser::file_type_definition_type const& file_type_definition() {
	return parser::file_type_definition;
}
#endif

#if 0
parser::formal_designator_type const& formal_designator() {
	return parser::formal_designator;
}
#endif

#if 0
parser::formal_parameter_list_type const& formal_parameter_list() {
	return parser::formal_parameter_list;
}
#endif

#if 0
parser::formal_part_type const& formal_part() {
	return parser::formal_part;
}
#endif

#if 0
parser::full_type_declaration_type const& full_type_declaration() {
	return parser::full_type_declaration;
}
#endif

#if 0
parser::function_call_type const& function_call() {
	return parser::function_call;
}
#endif

#if 0
parser::generate_statement_type const& generate_statement() {
	return parser::generate_statement;
}
#endif

#if 0
parser::generation_scheme_type const& generation_scheme() {
	return parser::generation_scheme;
}
#endif

#if 0
parser::generic_clause_type const& generic_clause() {
	return parser::generic_clause;
}
#endif

#if 0
parser::generic_list_type const& generic_list() {
	return parser::generic_list;
}
#endif

#if 0
parser::generic_map_aspect_type const& generic_map_aspect() {
	return parser::generic_map_aspect;
}
#endif

#if 0
parser::graphic_character_type const& graphic_character() {
	return parser::graphic_character;
}
#endif

#if 0
parser::group_constituent_type const& group_constituent() {
	return parser::group_constituent;
}
#endif

#if 0
parser::group_constituent_list_type const& group_constituent_list() {
	return parser::group_constituent_list;
}
#endif

#if 0
parser::group_template_declaration_type const& group_template_declaration() {
	return parser::group_template_declaration;
}
#endif

#if 0
parser::group_declaration_type const& group_declaration() {
	return parser::group_declaration;
}
#endif

#if 0
parser::guarded_signal_specification_type const& guarded_signal_specification() {
	return parser::guarded_signal_specification;
}
#endif

#if 0
parser::identifier_type const& identifier() {
	return parser::identifier;
}
#endif

#if 0
parser::identifier_list_type const& identifier_list() {
	return parser::identifier_list;
}
#endif

#if 0
parser::if_statement_type const& if_statement() {
	return parser::if_statement;
}
#endif

#if 0
parser::incomplete_type_declaration_type const& incomplete_type_declaration() {
	return parser::incomplete_type_declaration;
}
#endif

#if 0
parser::index_constraint_type const& index_constraint() {
	return parser::index_constraint;
}
#endif

#if 0
parser::index_specification_type const& index_specification() {
	return parser::index_specification;
}
#endif

#if 0
parser::index_subtype_definition_type const& index_subtype_definition() {
	return parser::index_subtype_definition;
}
#endif

#if 0
parser::indexed_name_type const& indexed_name() {
	return parser::indexed_name;
}
#endif

#if 0
parser::instantiated_unit_type const& instantiated_unit() {
	return parser::instantiated_unit;
}
#endif

#if 0
parser::instantiation_list_type const& instantiation_list() {
	return parser::instantiation_list;
}
#endif

#if 0
parser::integer_type const& integer() {
	return parser::integer;
}
#endif

#if 0
parser::integer_type_definition_type const& integer_type_definition() {
	return parser::integer_type_definition;
}
#endif

#if 0
parser::interface_constant_declaration_type const& interface_constant_declaration() {
	return parser::interface_constant_declaration;
}
#endif

#if 0
parser::interface_declaration_type const& interface_declaration() {
	return parser::interface_declaration;
}
#endif

#if 0
parser::interface_element_type const& interface_element() {
	return parser::interface_element;
}
#endif

#if 0
parser::interface_file_declaration_type const& interface_file_declaration() {
	return parser::interface_file_declaration;
}
#endif

#if 0
parser::interface_list_type const& interface_list() {
	return parser::interface_list;
}
#endif

#if 0
parser::interface_signal_declaration_type const& interface_signal_declaration() {
	return parser::interface_signal_declaration;
}
#endif

#if 0
parser::interface_variable_declaration_type const& interface_variable_declaration() {
	return parser::interface_variable_declaration;
}
#endif

#if 0
parser::iteration_scheme_type const& iteration_scheme() {
	return parser::iteration_scheme;
}
#endif

#if 0
parser::label_type const& label() {
	return parser::label;
}
#endif

#if 0
parser::letter_type const& letter() {
	return parser::letter;
}
#endif

#if 0
parser::letter_or_digit_type const& letter_or_digit() {
	return parser::letter_or_digit;
}
#endif

#if 0
parser::library_clause_type const& library_clause() {
	return parser::library_clause;
}
#endif

#if 0
parser::library_unit_type const& library_unit() {
	return parser::library_unit;
}
#endif

#if 0
parser::literal_type const& literal() {
	return parser::literal;
}
#endif

#if 0
parser::logical_name_type const& logical_name() {
	return parser::logical_name;
}
#endif

#if 0
parser::logical_name_list_type const& logical_name_list() {
	return parser::logical_name_list;
}
#endif

#if 0
parser::logical_operator_type const& logical_operator() {
	return parser::logical_operator;
}
#endif

#if 0
parser::loop_statement_type const& loop_statement() {
	return parser::loop_statement;
}
#endif

#if 0
parser::miscellaneous_operator_type const& miscellaneous_operator() {
	return parser::miscellaneous_operator;
}
#endif

#if 0
parser::mode_type const& mode() {
	return parser::mode;
}
#endif

#if 0
parser::multiplying_operator_type const& multiplying_operator() {
	return parser::multiplying_operator;
}
#endif

#if 0
parser::name_type const& name() {
	return parser::name;
}
#endif

#if 0
parser::next_statement_type const& next_statement() {
	return parser::next_statement;
}
#endif

#if 0
parser::null_statement_type const& null_statement() {
	return parser::null_statement;
}
#endif

#if 0
parser::numeric_literal_type const& numeric_literal() {
	return parser::numeric_literal;
}
#endif

#if 0
parser::object_declaration_type const& object_declaration() {
	return parser::object_declaration;
}
#endif

#if 0
parser::operator_symbol_type const& operator_symbol() {
	return parser::operator_symbol;
}
#endif

#if 0
parser::options_type const& options() {
	return parser::options;
}
#endif

#if 0
parser::package_body_type const& package_body() {
	return parser::package_body;
}
#endif

#if 0
parser::package_body_declarative_item_type const& package_body_declarative_item() {
	return parser::package_body_declarative_item;
}
#endif

#if 0
parser::package_body_declarative_part_type const& package_body_declarative_part() {
	return parser::package_body_declarative_part;
}
#endif

#if 0
parser::package_declaration_type const& package_declaration() {
	return parser::package_declaration;
}
#endif

#if 0
parser::package_declarative_item_type const& package_declarative_item() {
	return parser::package_declarative_item;
}
#endif

#if 0
parser::package_declarative_part_type const& package_declarative_part() {
	return parser::package_declarative_part;
}
#endif

#if 0
parser::parameter_specification_type const& parameter_specification() {
	return parser::parameter_specification;
}
#endif

#if 0
parser::physical_literal_type const& physical_literal() {
	return parser::physical_literal;
}
#endif

#if 0
parser::physical_type_definition_type const& physical_type_definition() {
	return parser::physical_type_definition;
}
#endif

#if 0
parser::port_clause_type const& port_clause() {
	return parser::port_clause;
}
#endif

#if 0
parser::port_list_type const& port_list() {
	return parser::port_list;
}
#endif

#if 0
parser::port_map_aspect_type const& port_map_aspect() {
	return parser::port_map_aspect;
}
#endif

#if 0
parser::prefix_type const& prefix() {
	return parser::prefix;
}
#endif

#if 0
parser::primary_type const& primary() {
	return parser::primary;
}
#endif

#if 0
parser::primary_unit_type const& primary_unit() {
	return parser::primary_unit;
}
#endif

#if 0
parser::procedure_call_type const& procedure_call() {
	return parser::procedure_call;
}
#endif

#if 0
parser::procedure_call_statement_type const& procedure_call_statement() {
	return parser::procedure_call_statement;
}
#endif

#if 0
parser::process_declarative_item_type const& process_declarative_item() {
	return parser::process_declarative_item;
}
#endif

#if 0
parser::process_declarative_part_type const& process_declarative_part() {
	return parser::process_declarative_part;
}
#endif

#if 0
parser::process_statement_type const& process_statement() {
	return parser::process_statement;
}
#endif

#if 0
parser::process_statement_part_type const& process_statement_part() {
	return parser::process_statement_part;
}
#endif

#if 0
parser::qualified_expression_type const& qualified_expression() {
	return parser::qualified_expression;
}
#endif

#if 0
parser::range_type const& range() {
	return parser::range;
}
#endif

#if 0
parser::range_constraint_type const& range_constraint() {
	return parser::range_constraint;
}
#endif

#if 0
parser::record_type_definition_type const& record_type_definition() {
	return parser::record_type_definition;
}
#endif

#if 0
parser::relation_type const& relation() {
	return parser::relation;
}
#endif

#if 0
parser::relational_operator_type const& relational_operator() {
	return parser::relational_operator;
}
#endif

#if 0
parser::report_statement_type const& report_statement() {
	return parser::report_statement;
}
#endif

#if 0
parser::return_statement_type const& return_statement() {
	return parser::return_statement;
}
#endif

#if 0
parser::scalar_type_definition_type const& scalar_type_definition() {
	return parser::scalar_type_definition;
}
#endif

#if 0
parser::secondary_unit_type const& secondary_unit() {
	return parser::secondary_unit;
}
#endif

#if 0
parser::secondary_unit_declaration_type const& secondary_unit_declaration() {
	return parser::secondary_unit_declaration;
}
#endif

#if 0
parser::selected_name_type const& selected_name() {
	return parser::selected_name;
}
#endif

#if 0
parser::selected_signal_assignment_type const& selected_signal_assignment() {
	return parser::selected_signal_assignment;
}
#endif

#if 0
parser::selected_waveforms_type const& selected_waveforms() {
	return parser::selected_waveforms;
}
#endif

#if 0
parser::sensitivity_clause_type const& sensitivity_clause() {
	return parser::sensitivity_clause;
}
#endif

#if 0
parser::sensitivity_list_type const& sensitivity_list() {
	return parser::sensitivity_list;
}
#endif

#if 0
parser::sequence_of_statements_type const& sequence_of_statements() {
	return parser::sequence_of_statements;
}
#endif

#if 0
parser::sequential_statement_type const& sequential_statement() {
	return parser::sequential_statement;
}
#endif

#if 0
parser::shift_expression_type const& shift_expression() {
	return parser::shift_expression;
}
#endif

#if 0
parser::shift_operator_type const& shift_operator() {
	return parser::shift_operator;
}
#endif

#if 0
parser::sign_type const& sign() {
	return parser::sign;
}
#endif

#if 0
parser::signal_assignment_statement_type const& signal_assignment_statement() {
	return parser::signal_assignment_statement;
}
#endif

#if 0
parser::signal_declaration_type const& signal_declaration() {
	return parser::signal_declaration;
}
#endif

#if 0
parser::signal_kind_type const& signal_kind() {
	return parser::signal_kind;
}
#endif

#if 0
parser::signal_list_type const& signal_list() {
	return parser::signal_list;
}
#endif

#if 0
parser::signature_type const& signature() {
	return parser::signature;
}
#endif

#if 0
parser::simple_expression_type const& simple_expression() {
	return parser::simple_expression;
}
#endif

#if 0
parser::simple_name_type const& simple_name() {
	return parser::simple_name;
}
#endif

#if 0
parser::slice_name_type const& slice_name() {
	return parser::slice_name;
}
#endif

#if 0
parser::string_literal_type const& string_literal() {
	return parser::string_literal;
}
#endif

#if 0
parser::subprogram_body_type const& subprogram_body() {
	return parser::subprogram_body;
}
#endif

#if 0
parser::subprogram_declaration_type const& subprogram_declaration() {
	return parser::subprogram_declaration;
}
#endif

#if 0
parser::subprogram_declarative_item_type const& subprogram_declarative_item() {
	return parser::subprogram_declarative_item;
}
#endif

#if 0
parser::subprogram_declarative_part_type const& subprogram_declarative_part() {
	return parser::subprogram_declarative_part;
}
#endif

#if 0
parser::subprogram_kind_type const& subprogram_kind() {
	return parser::subprogram_kind;
}
#endif

#if 0
parser::subprogram_specification_type const& subprogram_specification() {
	return parser::subprogram_specification;
}
#endif

#if 0
parser::subprogram_statement_part_type const& subprogram_statement_part() {
	return parser::subprogram_statement_part;
}
#endif

#if 0
parser::subtype_declaration_type const& subtype_declaration() {
	return parser::subtype_declaration;
}
#endif

#if 0
parser::subtype_indication_type const& subtype_indication() {
	return parser::subtype_indication;
}
#endif

#if 0
parser::suffix_type const& suffix() {
	return parser::suffix;
}
#endif

#if 0
parser::target_type const& target() {
	return parser::target;
}
#endif

#if 0
parser::term_type const& term() {
	return parser::term;
}
#endif

#if 0
parser::timeout_clause_type const& timeout_clause() {
	return parser::timeout_clause;
}
#endif

#if 0
parser::type_conversion_type const& type_conversion() {
	return parser::type_conversion;
}
#endif

#if 0
parser::type_declaration_type const& type_declaration() {
	return parser::type_declaration;
}
#endif

#if 0
parser::type_definition_type const& type_definition() {
	return parser::type_definition;
}
#endif

#if 0
parser::type_mark_type const& type_mark() {
	return parser::type_mark;
}
#endif

#if 0
parser::unconstrained_array_definition_type const& unconstrained_array_definition() {
	return parser::unconstrained_array_definition;
}
#endif

#if 0
parser::use_clause_type const& use_clause() {
	return parser::use_clause;
}
#endif

#if 0
parser::variable_assignment_statement_type const& variable_assignment_statement() {
	return parser::variable_assignment_statement;
}
#endif

#if 0
parser::variable_declaration_type const& variable_declaration() {
	return parser::variable_declaration;
}
#endif

#if 0
parser::wait_statement_type const& wait_statement() {
	return parser::wait_statement;
}
#endif

#if 0
parser::waveform_type const& waveform() {
	return parser::waveform;
}
#endif

} } // namespace eda.vhdl93


