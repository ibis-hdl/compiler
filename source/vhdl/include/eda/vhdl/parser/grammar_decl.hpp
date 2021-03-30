#pragma once

#include <eda/vhdl/parser/grammar_type.hpp>

namespace eda::vhdl::parser {

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)

BOOST_SPIRIT_DECLARE(abstract_literal_type);
BOOST_SPIRIT_DECLARE(access_type_definition_type);
BOOST_SPIRIT_DECLARE(actual_designator_type);
BOOST_SPIRIT_DECLARE(actual_parameter_part_type);
BOOST_SPIRIT_DECLARE(actual_part_type);
BOOST_SPIRIT_DECLARE(aggregate_type);
BOOST_SPIRIT_DECLARE(alias_declaration_type);
BOOST_SPIRIT_DECLARE(alias_designator_type);
BOOST_SPIRIT_DECLARE(allocator_type);
BOOST_SPIRIT_DECLARE(architecture_body_type);
BOOST_SPIRIT_DECLARE(architecture_declarative_part_type);
BOOST_SPIRIT_DECLARE(architecture_statement_part_type);
BOOST_SPIRIT_DECLARE(array_type_definition_type);
BOOST_SPIRIT_DECLARE(assertion_type);
BOOST_SPIRIT_DECLARE(assertion_statement_type);
BOOST_SPIRIT_DECLARE(association_element_type);
BOOST_SPIRIT_DECLARE(association_list_type);
BOOST_SPIRIT_DECLARE(attribute_declaration_type);
BOOST_SPIRIT_DECLARE(attribute_designator_type);
BOOST_SPIRIT_DECLARE(attribute_name_type);
BOOST_SPIRIT_DECLARE(attribute_specification_type);
BOOST_SPIRIT_DECLARE(base_type);
BOOST_SPIRIT_DECLARE(based_integer_type);
BOOST_SPIRIT_DECLARE(based_literal_type);
BOOST_SPIRIT_DECLARE(basic_graphic_character_type);
BOOST_SPIRIT_DECLARE(basic_identifier_type);
BOOST_SPIRIT_DECLARE(binding_indication_type);
BOOST_SPIRIT_DECLARE(bit_string_literal_type);
BOOST_SPIRIT_DECLARE(block_configuration_type);
BOOST_SPIRIT_DECLARE(block_declarative_item_type);
BOOST_SPIRIT_DECLARE(block_declarative_part_type);
BOOST_SPIRIT_DECLARE(block_header_type);
BOOST_SPIRIT_DECLARE(block_specification_type);
BOOST_SPIRIT_DECLARE(block_statement_type);
BOOST_SPIRIT_DECLARE(block_statement_part_type);
BOOST_SPIRIT_DECLARE(case_statement_type);
BOOST_SPIRIT_DECLARE(case_statement_alternative_type);
BOOST_SPIRIT_DECLARE(character_literal_type);
BOOST_SPIRIT_DECLARE(choice_type);
BOOST_SPIRIT_DECLARE(choices_type);
BOOST_SPIRIT_DECLARE(component_configuration_type);
BOOST_SPIRIT_DECLARE(component_declaration_type);
BOOST_SPIRIT_DECLARE(component_instantiation_statement_type);
BOOST_SPIRIT_DECLARE(component_specification_type);
BOOST_SPIRIT_DECLARE(composite_type_definition_type);
BOOST_SPIRIT_DECLARE(concurrent_assertion_statement_type);
BOOST_SPIRIT_DECLARE(concurrent_procedure_call_statement_type);
BOOST_SPIRIT_DECLARE(concurrent_signal_assignment_statement_type);
BOOST_SPIRIT_DECLARE(concurrent_statement_type);
BOOST_SPIRIT_DECLARE(condition_type);
BOOST_SPIRIT_DECLARE(condition_clause_type);
BOOST_SPIRIT_DECLARE(conditional_signal_assignment_type);
BOOST_SPIRIT_DECLARE(conditional_waveforms_type);
BOOST_SPIRIT_DECLARE(configuration_declaration_type);
BOOST_SPIRIT_DECLARE(configuration_declarative_item_type);
BOOST_SPIRIT_DECLARE(configuration_declarative_part_type);
BOOST_SPIRIT_DECLARE(configuration_item_type);
BOOST_SPIRIT_DECLARE(configuration_specification_type);
BOOST_SPIRIT_DECLARE(constant_declaration_type);
BOOST_SPIRIT_DECLARE(constrained_array_definition_type);
BOOST_SPIRIT_DECLARE(constraint_type);
BOOST_SPIRIT_DECLARE(context_clause_type);
BOOST_SPIRIT_DECLARE(context_item_type);
BOOST_SPIRIT_DECLARE(decimal_literal_type);
BOOST_SPIRIT_DECLARE(delay_mechanism_type);
// BOOST_SPIRIT_DECLARE(design_file_type);
BOOST_SPIRIT_DECLARE(design_unit_type);
BOOST_SPIRIT_DECLARE(designator_type);
BOOST_SPIRIT_DECLARE(direction_type);
BOOST_SPIRIT_DECLARE(disconnection_specification_type);
BOOST_SPIRIT_DECLARE(discrete_range_type);
BOOST_SPIRIT_DECLARE(element_association_type);
BOOST_SPIRIT_DECLARE(element_declaration_type);
BOOST_SPIRIT_DECLARE(element_subtype_definition_type);
BOOST_SPIRIT_DECLARE(entity_aspect_type);
BOOST_SPIRIT_DECLARE(entity_class_type);
BOOST_SPIRIT_DECLARE(entity_class_entry_type);
BOOST_SPIRIT_DECLARE(entity_class_entry_list_type);
BOOST_SPIRIT_DECLARE(entity_declaration_type);
BOOST_SPIRIT_DECLARE(entity_declarative_item_type);
BOOST_SPIRIT_DECLARE(entity_declarative_part_type);
BOOST_SPIRIT_DECLARE(entity_designator_type);
BOOST_SPIRIT_DECLARE(entity_header_type);
BOOST_SPIRIT_DECLARE(entity_name_list_type);
BOOST_SPIRIT_DECLARE(entity_specification_type);
BOOST_SPIRIT_DECLARE(entity_statement_type);
BOOST_SPIRIT_DECLARE(entity_statement_part_type);
BOOST_SPIRIT_DECLARE(entity_tag_type);
BOOST_SPIRIT_DECLARE(enumeration_literal_type);
BOOST_SPIRIT_DECLARE(enumeration_type_definition_type);
BOOST_SPIRIT_DECLARE(exit_statement_type);
BOOST_SPIRIT_DECLARE(exponent_type);
BOOST_SPIRIT_DECLARE(expression_type);
BOOST_SPIRIT_DECLARE(extended_identifier_type);
BOOST_SPIRIT_DECLARE(factor_type);
BOOST_SPIRIT_DECLARE(file_declaration_type);
BOOST_SPIRIT_DECLARE(file_logical_name_type);
BOOST_SPIRIT_DECLARE(file_open_information_type);
BOOST_SPIRIT_DECLARE(file_type_definition_type);
BOOST_SPIRIT_DECLARE(formal_designator_type);
BOOST_SPIRIT_DECLARE(formal_parameter_list_type);
BOOST_SPIRIT_DECLARE(formal_part_type);
BOOST_SPIRIT_DECLARE(function_call_type);
BOOST_SPIRIT_DECLARE(generate_statement_type);
BOOST_SPIRIT_DECLARE(generation_scheme_type);
BOOST_SPIRIT_DECLARE(generic_clause_type);
BOOST_SPIRIT_DECLARE(generic_map_aspect_type);
BOOST_SPIRIT_DECLARE(graphic_character_type);
BOOST_SPIRIT_DECLARE(group_constituent_type);
BOOST_SPIRIT_DECLARE(group_constituent_list_type);
BOOST_SPIRIT_DECLARE(group_template_declaration_type);
BOOST_SPIRIT_DECLARE(group_declaration_type);
BOOST_SPIRIT_DECLARE(guarded_signal_specification_type);
BOOST_SPIRIT_DECLARE(identifier_type);
BOOST_SPIRIT_DECLARE(identifier_list_type);
BOOST_SPIRIT_DECLARE(if_statement_type);
BOOST_SPIRIT_DECLARE(index_constraint_type);
BOOST_SPIRIT_DECLARE(index_specification_type);
BOOST_SPIRIT_DECLARE(index_subtype_definition_type);
BOOST_SPIRIT_DECLARE(indexed_name_type);
BOOST_SPIRIT_DECLARE(instantiated_unit_type);
BOOST_SPIRIT_DECLARE(instantiation_list_type);
BOOST_SPIRIT_DECLARE(integer_type);
BOOST_SPIRIT_DECLARE(interface_constant_declaration_type);
BOOST_SPIRIT_DECLARE(interface_declaration_type);
BOOST_SPIRIT_DECLARE(interface_element_type);
BOOST_SPIRIT_DECLARE(interface_file_declaration_type);
BOOST_SPIRIT_DECLARE(interface_list_type);
BOOST_SPIRIT_DECLARE(interface_signal_declaration_type);
BOOST_SPIRIT_DECLARE(interface_variable_declaration_type);
BOOST_SPIRIT_DECLARE(iteration_scheme_type);
BOOST_SPIRIT_DECLARE(label_type);
BOOST_SPIRIT_DECLARE(letter_type);
BOOST_SPIRIT_DECLARE(letter_or_digit_type);
BOOST_SPIRIT_DECLARE(library_clause_type);
BOOST_SPIRIT_DECLARE(library_unit_type);
BOOST_SPIRIT_DECLARE(literal_type);
BOOST_SPIRIT_DECLARE(logical_name_type);
BOOST_SPIRIT_DECLARE(logical_name_list_type);
BOOST_SPIRIT_DECLARE(loop_statement_type);
BOOST_SPIRIT_DECLARE(mode_type);
BOOST_SPIRIT_DECLARE(name_type);
BOOST_SPIRIT_DECLARE(next_statement_type);
BOOST_SPIRIT_DECLARE(null_statement_type);
BOOST_SPIRIT_DECLARE(numeric_literal_type);
BOOST_SPIRIT_DECLARE(operator_symbol_type);
BOOST_SPIRIT_DECLARE(options_type);
BOOST_SPIRIT_DECLARE(package_body_type);
BOOST_SPIRIT_DECLARE(package_body_declarative_item_type);
BOOST_SPIRIT_DECLARE(package_body_declarative_part_type);
BOOST_SPIRIT_DECLARE(package_declaration_type);
BOOST_SPIRIT_DECLARE(package_declarative_item_type);
BOOST_SPIRIT_DECLARE(package_declarative_part_type);
BOOST_SPIRIT_DECLARE(parameter_specification_type);
BOOST_SPIRIT_DECLARE(physical_literal_type);
BOOST_SPIRIT_DECLARE(physical_type_definition_type);
BOOST_SPIRIT_DECLARE(port_clause_type);
BOOST_SPIRIT_DECLARE(port_map_aspect_type);
BOOST_SPIRIT_DECLARE(prefix_type);
BOOST_SPIRIT_DECLARE(primary_type);
BOOST_SPIRIT_DECLARE(primary_unit_type);
BOOST_SPIRIT_DECLARE(primary_unit_declaration_type);
BOOST_SPIRIT_DECLARE(procedure_call_type);
BOOST_SPIRIT_DECLARE(procedure_call_statement_type);
BOOST_SPIRIT_DECLARE(process_declarative_item_type);
BOOST_SPIRIT_DECLARE(process_declarative_part_type);
BOOST_SPIRIT_DECLARE(process_statement_type);
BOOST_SPIRIT_DECLARE(process_statement_part_type);
BOOST_SPIRIT_DECLARE(qualified_expression_type);
BOOST_SPIRIT_DECLARE(range_type);
BOOST_SPIRIT_DECLARE(range_constraint_type);
BOOST_SPIRIT_DECLARE(record_type_definition_type);
BOOST_SPIRIT_DECLARE(relation_type);
BOOST_SPIRIT_DECLARE(report_statement_type);
BOOST_SPIRIT_DECLARE(return_statement_type);
BOOST_SPIRIT_DECLARE(scalar_type_definition_type);
BOOST_SPIRIT_DECLARE(secondary_unit_type);
BOOST_SPIRIT_DECLARE(secondary_unit_declaration_type);
BOOST_SPIRIT_DECLARE(selected_name_type);
BOOST_SPIRIT_DECLARE(selected_signal_assignment_type);
BOOST_SPIRIT_DECLARE(selected_waveforms_type);
BOOST_SPIRIT_DECLARE(sensitivity_clause_type);
BOOST_SPIRIT_DECLARE(sensitivity_list_type);
BOOST_SPIRIT_DECLARE(sequence_of_statements_type);
BOOST_SPIRIT_DECLARE(sequential_statement_type);
BOOST_SPIRIT_DECLARE(shift_expression_type);
BOOST_SPIRIT_DECLARE(sign_type);
BOOST_SPIRIT_DECLARE(signal_assignment_statement_type);
BOOST_SPIRIT_DECLARE(signal_declaration_type);
BOOST_SPIRIT_DECLARE(signal_kind_type);
BOOST_SPIRIT_DECLARE(signal_list_type);
BOOST_SPIRIT_DECLARE(signature_type);
BOOST_SPIRIT_DECLARE(simple_expression_type);
BOOST_SPIRIT_DECLARE(simple_name_type);
BOOST_SPIRIT_DECLARE(slice_name_type);
BOOST_SPIRIT_DECLARE(string_literal_type);
BOOST_SPIRIT_DECLARE(subprogram_body_type);
BOOST_SPIRIT_DECLARE(subprogram_declaration_type);
BOOST_SPIRIT_DECLARE(subprogram_declarative_part_type);
BOOST_SPIRIT_DECLARE(subprogram_kind_type);
BOOST_SPIRIT_DECLARE(subprogram_specification_type);
BOOST_SPIRIT_DECLARE(subprogram_statement_part_type);
BOOST_SPIRIT_DECLARE(subtype_declaration_type);
BOOST_SPIRIT_DECLARE(subtype_indication_type);
BOOST_SPIRIT_DECLARE(suffix_type);
BOOST_SPIRIT_DECLARE(target_type);
BOOST_SPIRIT_DECLARE(term_type);
BOOST_SPIRIT_DECLARE(timeout_clause_type);
BOOST_SPIRIT_DECLARE(type_conversion_type);
BOOST_SPIRIT_DECLARE(type_declaration_type);
BOOST_SPIRIT_DECLARE(type_definition_type);
BOOST_SPIRIT_DECLARE(type_mark_type);
BOOST_SPIRIT_DECLARE(unconstrained_array_definition_type);
BOOST_SPIRIT_DECLARE(use_clause_type);
BOOST_SPIRIT_DECLARE(variable_assignment_statement_type);
BOOST_SPIRIT_DECLARE(variable_declaration_type);
BOOST_SPIRIT_DECLARE(wait_statement_type);
BOOST_SPIRIT_DECLARE(waveform_type);
BOOST_SPIRIT_DECLARE(waveform_element_type);

#endif  // !defined(DOXYGEN_DOCUMENTATION_BUILD)

}  // namespace eda::vhdl::parser