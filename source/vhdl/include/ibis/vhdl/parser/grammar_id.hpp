//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

namespace ibis::vhdl::parser {

//
// Parser Rule IDs
//
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
struct based_integer_class;
struct based_literal_class;
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
struct extended_identifier_class;
struct factor_class;
struct file_declaration_class;
struct file_logical_name_class;
struct file_open_information_class;
struct file_type_definition_class;
// struct floating_type_definition_class;
struct formal_designator_class;
struct formal_parameter_list_class;
struct formal_part_class;
// struct full_type_declaration_class;
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
// struct incomplete_type_declaration_class;
struct index_constraint_class;
struct index_specification_class;
struct index_subtype_definition_class;
struct indexed_name_class;
struct instantiated_unit_class;
struct instantiation_list_class;
struct integer_class;
// struct integer_type_definition_class;
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
struct primary_unit_declaration_class;
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

}  // namespace ibis::vhdl::parser
