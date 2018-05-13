/*
 * ast.hpp
 *
 *  Created on: 02.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_AST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_AST_HPP_

#if 1
//DISABLED #include <eda/vhdl/ast/abstract_literal.hpp>
#include <eda/vhdl/ast/access_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/actual_designator.hpp>
#include <eda/vhdl/ast/actual_parameter_part.hpp>
//DISABLED #include <eda/vhdl/ast/actual_part.hpp>
//DISABLED #include <eda/vhdl/ast/aggregate.hpp>
#include <eda/vhdl/ast/alias_declaration.hpp>
#include <eda/vhdl/ast/alias_designator.hpp>
#include <eda/vhdl/ast/allocator.hpp>
#include <eda/vhdl/ast/architecture_body.hpp>
#include <eda/vhdl/ast/architecture_statement_part.hpp>
//#include <eda/vhdl/ast/array_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/assertion.hpp>
#include <eda/vhdl/ast/assertion_statement.hpp>
//DISABLED #include <eda/vhdl/ast/association_element.hpp>
#include <eda/vhdl/ast/association_list.hpp>
#include <eda/vhdl/ast/attribute_declaration.hpp>
#include <eda/vhdl/ast/attribute_name.hpp>
#include <eda/vhdl/ast/attribute_specification.hpp>
//#include <eda/vhdl/ast/base.hpp>
//#include <eda/vhdl/ast/base_specifier.hpp>
//#include <eda/vhdl/ast/based_integer.hpp>
//DISABLED #include <eda/vhdl/ast/based_literal.hpp>
//#include <eda/vhdl/ast/basic_character.hpp>
//#include <eda/vhdl/ast/basic_graphic_character.hpp>
//#include <eda/vhdl/ast/basic_identifier.hpp>
#include <eda/vhdl/ast/binding_indication.hpp>
//DISABLED #include <eda/vhdl/ast/bit_string_literal.hpp>
//#include <eda/vhdl/ast/bit_value.hpp>
//#include <eda/vhdl/ast/block_configuration.hpp>
//#include <eda/vhdl/ast/block_declarative_item.hpp>
#include <eda/vhdl/ast/block_declarative_part.hpp>
#include <eda/vhdl/ast/block_header.hpp>
#include <eda/vhdl/ast/block_specification.hpp>
#include <eda/vhdl/ast/block_statement.hpp>
//#include <eda/vhdl/ast/block_statement_part.hpp>
#include <eda/vhdl/ast/case_statement.hpp>
#include <eda/vhdl/ast/case_statement_alternative.hpp>
//DISABLED #include <eda/vhdl/ast/character_literal.hpp>
//DISABLED #include <eda/vhdl/ast/choice.hpp>
#include <eda/vhdl/ast/choices.hpp>

// required due to forwarding
#include <eda/vhdl/ast/component_configuration.hpp>

#include <eda/vhdl/ast/component_declaration.hpp>
//#include <eda/vhdl/ast/component_instantiation_statement.hpp>
#include <eda/vhdl/ast/component_specification.hpp>
//#include <eda/vhdl/ast/composite_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/concurrent_assertion_statement.hpp>
//DISABLED #include <eda/vhdl/ast/concurrent_procedure_call_statement.hpp>
//DISABLED #include <eda/vhdl/ast/concurrent_signal_assignment_statement.hpp>
#include <eda/vhdl/ast/concurrent_statement.hpp>
//DISABLED #include <eda/vhdl/ast/condition.hpp>
//#include <eda/vhdl/ast/condition_clause.hpp>
#include <eda/vhdl/ast/conditional_signal_assignment.hpp>
//DISABLED #include <eda/vhdl/ast/conditional_waveforms.hpp>
#include <eda/vhdl/ast/configuration_declaration.hpp>
//#include <eda/vhdl/ast/configuration_declarative_item.hpp>
//#include <eda/vhdl/ast/configuration_declarative_part.hpp>
//#include <eda/vhdl/ast/configuration_item.hpp>
//#include <eda/vhdl/ast/configuration_specification.hpp>
#include <eda/vhdl/ast/constant_declaration.hpp>
//#include <eda/vhdl/ast/constrained_array_definition.hpp>
#include <eda/vhdl/ast/constraint.hpp>
#include <eda/vhdl/ast/context_clause.hpp>
//DISABLED #include <eda/vhdl/ast/context_item.hpp>
//DISABLED #include <eda/vhdl/ast/decimal_literal.hpp>
//UNUSED_IN_BNF#include <eda/vhdl/ast/declaration.hpp>
//DISABLED #include <eda/vhdl/ast/delay_mechanism.hpp>
#include <eda/vhdl/ast/design_file.hpp>
//#include <eda/vhdl/ast/design_unit.hpp>
//#include <eda/vhdl/ast/designator.hpp>
#include <eda/vhdl/ast/disconnection_specification.hpp>
//#include <eda/vhdl/ast/discrete_range.hpp>
//DISABLED#include <eda/vhdl/ast/element_association.hpp>
//#include <eda/vhdl/ast/element_declaration.hpp>
//#include <eda/vhdl/ast/element_subtype_definition.hpp>
#include <eda/vhdl/ast/entity_aspect.hpp>
//#include <eda/vhdl/ast/entity_class.hpp>
//#include <eda/vhdl/ast/entity_class_entry.hpp>
#include <eda/vhdl/ast/entity_class_entry_list.hpp>
#include <eda/vhdl/ast/entity_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/entity_declarative_item.hpp>
#include <eda/vhdl/ast/entity_declarative_part.hpp>
//#include <eda/vhdl/ast/entity_designator.hpp>
//DISABLED #include <eda/vhdl/ast/guarded_signal_specification.hpp>
#include <eda/vhdl/ast/entity_header.hpp>
//#include <eda/vhdl/ast/entity_name_list.hpp>
//#include <eda/vhdl/ast/entity_specification.hpp>
//#include <eda/vhdl/ast/entity_statement.hpp>
//#include <eda/vhdl/ast/entity_statement_part.hpp>
//#include <eda/vhdl/ast/entity_tag.hpp>
//DISABLED #include <eda/vhdl/ast/enumeration_literal.hpp>
#include <eda/vhdl/ast/enumeration_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/exit_statement.hpp>
//DISABLED #include <eda/vhdl/ast/expression.hpp>
//#include <eda/vhdl/ast/extended_digit.hpp>
//#include <eda/vhdl/ast/extended_identifier.hpp>
//DISABLED  #include <eda/vhdl/ast/factor.hpp>
#include <eda/vhdl/ast/file_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/file_logical_name.hpp>
//DISABLED #include <eda/vhdl/ast/file_open_information.hpp>
#include <eda/vhdl/ast/file_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/formal_designator.hpp>
#include <eda/vhdl/ast/formal_parameter_list.hpp>
#include <eda/vhdl/ast/generic_clause.hpp>
#include <eda/vhdl/ast/generic_map_aspect.hpp>
//DISABLED #include <eda/vhdl/ast/group_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/formal_part.hpp>
//#include <eda/vhdl/ast/full_type_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/function_call.hpp>
#include <eda/vhdl/ast/generate_statement.hpp>
//#include <eda/vhdl/ast/generation_scheme.hpp>
#include <eda/vhdl/ast/if_statement.hpp>
//DISABLED#include <eda/vhdl/ast/instantiation_list.hpp>
#include <eda/vhdl/ast/instantiated_unit.hpp>
//#include <eda/vhdl/ast/integer_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/interface_constant_declaration.hpp>
#include <eda/vhdl/ast/interface_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/interface_element.hpp>
//DISABLED #include <eda/vhdl/ast/interface_file_declaration.hpp>
#include <eda/vhdl/ast/interface_list.hpp>
//DISABLED #include <eda/vhdl/ast/interface_signal_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/interface_variable_declaration.hpp>
//#include <eda/vhdl/ast/iteration_scheme.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
//#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/library_clause.hpp>
//#include <eda/vhdl/ast/library_unit.hpp>
//DISABLED #include <eda/vhdl/ast/literal.hpp>
#include <eda/vhdl/ast/loop_statement.hpp>
//DISABLED #include <eda/vhdl/ast/name.hpp>
//DISABLED #include <eda/vhdl/ast/next_statement.hpp>
//DISABELD #include <eda/vhdl/ast/null_statement.hpp>
//DISABLED #include <eda/vhdl/ast/numeric_literal.hpp>
//UNSUED_IN_BNF//#include <eda/vhdl/ast/object_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/operator_token.hpp>
//DISABLED #include <eda/vhdl/ast/operator_symbol.hpp>
#include <eda/vhdl/ast/options.hpp>
#include <eda/vhdl/ast/port_clause.hpp>
#include <eda/vhdl/ast/port_map_aspect.hpp>
#include <eda/vhdl/ast/package_body.hpp>
//#include <eda/vhdl/ast/package_body_declarative_item.hpp>
//#include <eda/vhdl/ast/package_body_declarative_part.hpp>
#include <eda/vhdl/ast/package_declaration.hpp>
//#include <eda/vhdl/ast/package_declarative_item.hpp>
//#include <eda/vhdl/ast/package_declarative_part.hpp>
//#include <eda/vhdl/ast/parameter_specification.hpp>
//DISABLED #include <eda/vhdl/ast/physical_literal.hpp>
//#include <eda/vhdl/ast/physical_type_definition.hpp>
//#include <eda/vhdl/ast/port_clause.hpp>
#include <eda/vhdl/ast/procedure_call_statement.hpp>
//DISABLED#include <eda/vhdl/ast/process_declarative_item.hpp>
#include <eda/vhdl/ast/process_declarative_part.hpp>
#include <eda/vhdl/ast/process_statement.hpp>
//#include <eda/vhdl/ast/process_statement_part.hpp>
//#include <eda/vhdl/ast/qualified_expression.hpp>
//DISABLED #include <eda/vhdl/ast/range.hpp>
//#include <eda/vhdl/ast/record_type_definition.hpp>
//DISABLED #include <eda/vhdl/ast/relation.hpp>
//DISABLED #include <eda/vhdl/ast/report_statement.hpp>
//DISABLED #include <eda/vhdl/ast/return_statement.hpp>
//#include <eda/vhdl/ast/scalar_type_definition.hpp>
//#include <eda/vhdl/ast/secondary_unit.hpp>
//#include <eda/vhdl/ast/secondary_unit_declaration.hpp>
//DISABLED #include <eda/vhdl/ast/selected_name.hpp>
#include <eda/vhdl/ast/selected_signal_assignment.hpp>
#include <eda/vhdl/ast/selected_waveforms.hpp>
#include <eda/vhdl/ast/sensitivity_clause.hpp>
//#include <eda/vhdl/ast/sequence_of_statements.hpp>
#include <eda/vhdl/ast/sequential_statement.hpp>
//DISABLED #include <eda/vhdl/ast/shift_expression.hpp>
#include <eda/vhdl/ast/signal_assignment_statement.hpp>
//#include <eda/vhdl/ast/signal_declaration.hpp>
#include <eda/vhdl/ast/signal_list.hpp>
//DISABLED #include <eda/vhdl/ast/signature.hpp>
//DISABLED #include <eda/vhdl/ast/simple_expression.hpp>
//DISABLED #include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/slice_name.hpp>
//DISABLED #include <eda/vhdl/ast/string_literal.hpp>
//#include <eda/vhdl/ast/subprogram_body.hpp>
//#include <eda/vhdl/ast/subprogram_declaration.hpp>
//#include <eda/vhdl/ast/subprogram_declarative_item.hpp>
#include <eda/vhdl/ast/subprogram_declarative_part.hpp>
//#include <eda/vhdl/ast/subprogram_kind.hpp>
#include <eda/vhdl/ast/subprogram_specification.hpp>
#include <eda/vhdl/ast/subprogram_statement_part.hpp>
#include <eda/vhdl/ast/subtype_declaration.hpp>
//#include <eda/vhdl/ast/subtype_indication.hpp>
//DISABLED #include <eda/vhdl/ast/suffix.hpp>
//DISABLED #include <eda/vhdl/ast/target.hpp>
//DISABLED #include <eda/vhdl/ast/term.hpp>
//#include <eda/vhdl/ast/timeout_clause.hpp>
#include <eda/vhdl/ast/type_conversion.hpp>
#include <eda/vhdl/ast/type_declaration.hpp>
//#include <eda/vhdl/ast/type_definition.hpp>
//#include <eda/vhdl/ast/unconstrained_array_definition.hpp>
#include <eda/vhdl/ast/use_clause.hpp>
//#include <eda/vhdl/ast/variable_assignment_statement.hpp>
#include <eda/vhdl/ast/variable_declaration.hpp>
#include <eda/vhdl/ast/wait_statement.hpp>
//DISABLED #include <eda/vhdl/ast/waveform.hpp>
//DISABLED #include <eda/vhdl/ast/waveform_element.hpp>
#else
#include <eda/vhdl/ast/design_file.hpp>
#endif


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_AST_HPP_ */
