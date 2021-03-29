#pragma once

#if 1
// DISABLED #include <eda/vhdl/ast/node/abstract_literal.hpp>
#include <eda/vhdl/ast/node/access_type_definition.hpp>
// DISABLED #include <eda/vhdl/ast/node/actual_designator.hpp>
#include <eda/vhdl/ast/node/actual_parameter_part.hpp>
// DISABLED #include <eda/vhdl/ast/node/actual_part.hpp>
// DISABLED #include <eda/vhdl/ast/node/aggregate.hpp>
#include <eda/vhdl/ast/node/alias_declaration.hpp>
#include <eda/vhdl/ast/node/alias_designator.hpp>
#include <eda/vhdl/ast/node/allocator.hpp>
#include <eda/vhdl/ast/node/architecture_body.hpp>
#include <eda/vhdl/ast/node/architecture_statement_part.hpp>
//#include <eda/vhdl/ast/node/array_type_definition.hpp>
// DISABLED #include <eda/vhdl/ast/node/assertion.hpp>
#include <eda/vhdl/ast/node/assertion_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/association_element.hpp>
#include <eda/vhdl/ast/node/association_list.hpp>
#include <eda/vhdl/ast/node/attribute_declaration.hpp>
#include <eda/vhdl/ast/node/attribute_name.hpp>
#include <eda/vhdl/ast/node/attribute_specification.hpp>
//#include <eda/vhdl/ast/node/base.hpp>
//#include <eda/vhdl/ast/node/base_specifier.hpp>
//#include <eda/vhdl/ast/node/based_integer.hpp>
// DISABLED #include <eda/vhdl/ast/node/based_literal.hpp>
//#include <eda/vhdl/ast/node/basic_character.hpp>
//#include <eda/vhdl/ast/node/basic_graphic_character.hpp>
//#include <eda/vhdl/ast/node/basic_identifier.hpp>
#include <eda/vhdl/ast/node/binding_indication.hpp>
// DISABLED #include <eda/vhdl/ast/node/bit_string_literal.hpp>
//#include <eda/vhdl/ast/node/bit_value.hpp>
//#include <eda/vhdl/ast/node/block_configuration.hpp>
//#include <eda/vhdl/ast/node/block_declarative_item.hpp>
#include <eda/vhdl/ast/node/block_declarative_part.hpp>
#include <eda/vhdl/ast/node/block_header.hpp>
#include <eda/vhdl/ast/node/block_specification.hpp>
#include <eda/vhdl/ast/node/block_statement.hpp>
//#include <eda/vhdl/ast/node/block_statement_part.hpp>
#include <eda/vhdl/ast/node/case_statement.hpp>
#include <eda/vhdl/ast/node/case_statement_alternative.hpp>
// DISABLED #include <eda/vhdl/ast/node/character_literal.hpp>
// DISABLED #include <eda/vhdl/ast/node/choice.hpp>
#include <eda/vhdl/ast/node/choices.hpp>

// required due to forwarding
#include <eda/vhdl/ast/node/component_configuration.hpp>

#include <eda/vhdl/ast/node/component_declaration.hpp>
//#include <eda/vhdl/ast/node/component_instantiation_statement.hpp>
#include <eda/vhdl/ast/node/component_specification.hpp>
//#include <eda/vhdl/ast/node/composite_type_definition.hpp>
// DISABLED #include <eda/vhdl/ast/node/concurrent_assertion_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/concurrent_procedure_call_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/concurrent_signal_assignment_statement.hpp>
#include <eda/vhdl/ast/node/concurrent_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/condition.hpp>
//#include <eda/vhdl/ast/node/condition_clause.hpp>
#include <eda/vhdl/ast/node/conditional_signal_assignment.hpp>
// DISABLED #include <eda/vhdl/ast/node/conditional_waveforms.hpp>
#include <eda/vhdl/ast/node/configuration_declaration.hpp>
//#include <eda/vhdl/ast/node/configuration_declarative_item.hpp>
//#include <eda/vhdl/ast/node/configuration_declarative_part.hpp>
//#include <eda/vhdl/ast/node/configuration_item.hpp>
//#include <eda/vhdl/ast/node/configuration_specification.hpp>
#include <eda/vhdl/ast/node/constant_declaration.hpp>
//#include <eda/vhdl/ast/node/constrained_array_definition.hpp>
#include <eda/vhdl/ast/node/constraint.hpp>
#include <eda/vhdl/ast/node/context_clause.hpp>
// DISABLED #include <eda/vhdl/ast/node/context_item.hpp>
// DISABLED #include <eda/vhdl/ast/node/decimal_literal.hpp>
// UNUSED_IN_BNF#include <eda/vhdl/ast/node/declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/delay_mechanism.hpp>
#include <eda/vhdl/ast/node/design_file.hpp>
//#include <eda/vhdl/ast/node/design_unit.hpp>
//#include <eda/vhdl/ast/node/designator.hpp>
#include <eda/vhdl/ast/node/disconnection_specification.hpp>
//#include <eda/vhdl/ast/node/discrete_range.hpp>
// DISABLED#include <eda/vhdl/ast/node/element_association.hpp>
//#include <eda/vhdl/ast/node/element_declaration.hpp>
//#include <eda/vhdl/ast/node/element_subtype_definition.hpp>
#include <eda/vhdl/ast/node/entity_aspect.hpp>
//#include <eda/vhdl/ast/node/entity_class.hpp>
//#include <eda/vhdl/ast/node/entity_class_entry.hpp>
#include <eda/vhdl/ast/node/entity_class_entry_list.hpp>
#include <eda/vhdl/ast/node/entity_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/entity_declarative_item.hpp>
#include <eda/vhdl/ast/node/entity_declarative_part.hpp>
//#include <eda/vhdl/ast/node/entity_designator.hpp>
// DISABLED #include <eda/vhdl/ast/node/guarded_signal_specification.hpp>
#include <eda/vhdl/ast/node/entity_header.hpp>
//#include <eda/vhdl/ast/node/entity_name_list.hpp>
//#include <eda/vhdl/ast/node/entity_specification.hpp>
//#include <eda/vhdl/ast/node/entity_statement.hpp>
//#include <eda/vhdl/ast/node/entity_statement_part.hpp>
//#include <eda/vhdl/ast/node/entity_tag.hpp>
// DISABLED #include <eda/vhdl/ast/node/enumeration_literal.hpp>
#include <eda/vhdl/ast/node/enumeration_type_definition.hpp>
// DISABLED #include <eda/vhdl/ast/node/exit_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/expression.hpp>
//#include <eda/vhdl/ast/node/extended_digit.hpp>
//#include <eda/vhdl/ast/node/extended_identifier.hpp>
// DISABLED  #include <eda/vhdl/ast/node/factor.hpp>
#include <eda/vhdl/ast/node/file_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/file_logical_name.hpp>
// DISABLED #include <eda/vhdl/ast/node/file_open_information.hpp>
#include <eda/vhdl/ast/node/file_type_definition.hpp>
#include <eda/vhdl/ast/node/formal_parameter_list.hpp>
#include <eda/vhdl/ast/node/generic_clause.hpp>
#include <eda/vhdl/ast/node/generic_map_aspect.hpp>
// DISABLED #include <eda/vhdl/ast/node/group_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/formal_part.hpp>
//#include <eda/vhdl/ast/node/full_type_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/function_call.hpp>
#include <eda/vhdl/ast/node/generate_statement.hpp>
//#include <eda/vhdl/ast/node/generation_scheme.hpp>
#include <eda/vhdl/ast/node/if_statement.hpp>
// DISABLED#include <eda/vhdl/ast/node/instantiation_list.hpp>
#include <eda/vhdl/ast/node/instantiated_unit.hpp>
//#include <eda/vhdl/ast/node/integer_type_definition.hpp>
// DISABLED #include <eda/vhdl/ast/node/interface_constant_declaration.hpp>
#include <eda/vhdl/ast/node/interface_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/interface_element.hpp>
// DISABLED #include <eda/vhdl/ast/node/interface_file_declaration.hpp>
#include <eda/vhdl/ast/node/interface_list.hpp>
// DISABLED #include <eda/vhdl/ast/node/interface_signal_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/interface_variable_declaration.hpp>
//#include <eda/vhdl/ast/node/iteration_scheme.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
//#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/library_clause.hpp>
//#include <eda/vhdl/ast/node/library_unit.hpp>
// DISABLED #include <eda/vhdl/ast/node/literal.hpp>
#include <eda/vhdl/ast/node/loop_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/name.hpp>
// DISABLED #include <eda/vhdl/ast/node/next_statement.hpp>
// DISABELD #include <eda/vhdl/ast/node/null_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/numeric_literal.hpp>
// UNSUED_IN_BNF//#include <eda/vhdl/ast/node/object_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/operator_token.hpp>
// DISABLED #include <eda/vhdl/ast/node/operator_symbol.hpp>
#include <eda/vhdl/ast/node/options.hpp>
#include <eda/vhdl/ast/node/port_clause.hpp>
#include <eda/vhdl/ast/node/port_map_aspect.hpp>
#include <eda/vhdl/ast/node/package_body.hpp>
//#include <eda/vhdl/ast/node/package_body_declarative_item.hpp>
//#include <eda/vhdl/ast/node/package_body_declarative_part.hpp>
#include <eda/vhdl/ast/node/package_declaration.hpp>
//#include <eda/vhdl/ast/node/package_declarative_item.hpp>
//#include <eda/vhdl/ast/node/package_declarative_part.hpp>
//#include <eda/vhdl/ast/node/parameter_specification.hpp>
// DISABLED #include <eda/vhdl/ast/node/physical_literal.hpp>
//#include <eda/vhdl/ast/node/physical_type_definition.hpp>
//#include <eda/vhdl/ast/node/port_clause.hpp>
#include <eda/vhdl/ast/node/procedure_call_statement.hpp>
// DISABLED#include <eda/vhdl/ast/node/process_declarative_item.hpp>
#include <eda/vhdl/ast/node/process_declarative_part.hpp>
#include <eda/vhdl/ast/node/process_statement.hpp>
//#include <eda/vhdl/ast/node/process_statement_part.hpp>
//#include <eda/vhdl/ast/node/qualified_expression.hpp>
// DISABLED #include <eda/vhdl/ast/node/range.hpp>
//#include <eda/vhdl/ast/node/record_type_definition.hpp>
// DISABLED #include <eda/vhdl/ast/node/relation.hpp>
// DISABLED #include <eda/vhdl/ast/node/report_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/return_statement.hpp>
//#include <eda/vhdl/ast/node/scalar_type_definition.hpp>
//#include <eda/vhdl/ast/node/secondary_unit.hpp>
//#include <eda/vhdl/ast/node/secondary_unit_declaration.hpp>
// DISABLED #include <eda/vhdl/ast/node/selected_name.hpp>
#include <eda/vhdl/ast/node/selected_signal_assignment.hpp>
#include <eda/vhdl/ast/node/selected_waveforms.hpp>
#include <eda/vhdl/ast/node/sensitivity_clause.hpp>
//#include <eda/vhdl/ast/node/sequence_of_statements.hpp>
#include <eda/vhdl/ast/node/sequential_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/shift_expression.hpp>
#include <eda/vhdl/ast/node/signal_assignment_statement.hpp>
//#include <eda/vhdl/ast/node/signal_declaration.hpp>
#include <eda/vhdl/ast/node/signal_list.hpp>
// DISABLED #include <eda/vhdl/ast/node/signature.hpp>
// DISABLED #include <eda/vhdl/ast/node/simple_expression.hpp>
// DISABLED #include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/node/slice_name.hpp>
// DISABLED #include <eda/vhdl/ast/node/string_literal.hpp>
//#include <eda/vhdl/ast/node/subprogram_body.hpp>
//#include <eda/vhdl/ast/node/subprogram_declaration.hpp>
//#include <eda/vhdl/ast/node/subprogram_declarative_item.hpp>
#include <eda/vhdl/ast/node/subprogram_declarative_part.hpp>
//#include <eda/vhdl/ast/node/subprogram_kind.hpp>
#include <eda/vhdl/ast/node/subprogram_specification.hpp>
#include <eda/vhdl/ast/node/subprogram_statement_part.hpp>
#include <eda/vhdl/ast/node/subtype_declaration.hpp>
//#include <eda/vhdl/ast/node/subtype_indication.hpp>
// DISABLED #include <eda/vhdl/ast/node/suffix.hpp>
// DISABLED #include <eda/vhdl/ast/node/target.hpp>
// DISABLED #include <eda/vhdl/ast/node/term.hpp>
//#include <eda/vhdl/ast/node/timeout_clause.hpp>
#include <eda/vhdl/ast/node/type_conversion.hpp>
#include <eda/vhdl/ast/node/type_declaration.hpp>
//#include <eda/vhdl/ast/node/type_definition.hpp>
//#include <eda/vhdl/ast/node/unconstrained_array_definition.hpp>
#include <eda/vhdl/ast/node/use_clause.hpp>
//#include <eda/vhdl/ast/node/variable_assignment_statement.hpp>
#include <eda/vhdl/ast/node/variable_declaration.hpp>
#include <eda/vhdl/ast/node/wait_statement.hpp>
// DISABLED #include <eda/vhdl/ast/node/waveform.hpp>
// DISABLED #include <eda/vhdl/ast/node/waveform_element.hpp>
#else
#include <eda/vhdl/ast/node/design_file.hpp>
#endif
