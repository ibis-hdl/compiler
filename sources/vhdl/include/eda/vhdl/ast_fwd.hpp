/*
 * ast_fwd.hpp
 *
 *  Created on: 24.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FWD_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FWD_HPP_


namespace eda { namespace vhdl { namespace ast {

/**
 * AST nodes forward declared
 *
 * Quick & Dirty created by
 * \code.{.sh}
 * grep struct sources/vhdl/include/eda/vhdl/ast/\*.hpp 
 *  | awk -F':' '{print $2}' | sed -e '/^ /d' -e '/chunk/d' -e 's/ $/;/g' 
 *  | sort | uniq
 * \endcode
 */
struct abstract_literal;
struct access_type_definition;
struct actual_designator;
struct aggregate;
struct alias_declaration;
struct alias_designator;
struct allocator;
struct architecture_body;
struct architecture_statement_part;
struct array_type_definition;
struct assertion;
struct assertion_statement;
struct association_element;
struct association_list;
struct attribute_declaration;
struct attribute_name;
struct attribute_specification;
struct based_literal;
struct binding_indication;
struct bit_string_literal;
struct block_configuration;
struct block_header;
struct block_specification;
struct block_statement;
struct block_statement_part;
struct case_statement;
struct case_statement_alternative;
struct character_literal;
struct component_configuration;
struct component_declaration;
struct component_instantiation_statement;
struct component_specification;
struct composite_type_definition;
struct concurrent_assertion_statement;
struct concurrent_procedure_call_statement;
struct concurrent_signal_assignment_statement;
struct concurrent_statement;
struct conditional_signal_assignment;
struct conditional_waveforms;
struct condition_clause;
struct configuration_declaration;
struct configuration_declarative_part;
struct configuration_specification;
struct constant_declaration;
struct constrained_array_definition;
struct constraint;
struct decimal_literal;
struct delay_mechanism;
struct designator;
struct design_file;
struct design_unit;
struct disconnection_specification;
struct discrete_range;
struct element_association;
struct element_declaration;
struct entity_aspect;
struct entity_aspect_configuration;
struct entity_aspect_entity;
struct entity_class_entry_list;
struct entity_declaration;
struct entity_declarative_part;
struct entity_designator;
struct entity_designator_list;
struct entity_header;
struct entity_name_list;
struct entity_specification;
struct entity_statement_part;
struct enumeration_literal;
struct enumeration_type_definition;
struct exit_statement;
struct expression;
struct factor;
struct factor_binary_operation;
struct factor_unary_operation;
struct file_declaration;
struct file_open_information;
struct formal_part;
struct function_call;
struct generate_statement;
struct generation_scheme;
struct generic_clause;
struct generic_map_aspect;
struct group_declaration;
struct group_template_declaration;
struct guarded_signal_specification;
struct identifier;
struct identifier_list;
struct if_statement;
struct index_constraint;
struct indexed_name;
struct index_specification;
struct index_subtype_definition;
struct instantiated_unit;
struct instantiated_unit_component;
struct instantiated_unit_configuration;
struct instantiated_unit_entity;
struct instantiation_list;
struct interface_constant_declaration;
struct interface_file_declaration;
struct interface_list;
struct interface_signal_declaration;
struct interface_variable_declaration;
struct iteration_scheme;
struct library_clause;
struct literal;
struct loop_statement;
struct name;
struct next_statement;
struct null_statement;
struct numeric_literal;
struct options;
struct package_body;
struct package_declaration;
struct parameter_specification;
struct physical_literal;
struct physical_type_definition;
struct port_clause;
struct port_map_aspect;
struct prefix;
struct primary;
struct primary_unit;
struct procedure_call;
struct procedure_call_statement;
struct process_declarative_part;
struct process_statement;
struct qualified_expression;
struct range;
struct range_expression;
struct record_type_definition;
struct relation;
struct report_statement;
struct return_statement;
struct scalar_type_definition;
struct secondary_unit;
struct secondary_unit_declaration;
struct selected_name;
struct selected_signal_assignment;
struct selected_waveform;
struct selected_waveforms;
struct sensitivity_clause;
struct sensitivity_list;
struct sequence_of_statements;
struct shift_expression;
struct signal_assignment_statement;
struct signal_declaration;
struct signal_list;
struct signal_list_list;
struct signature;
struct simple_expression;
struct slice_name;
struct string_literal;
struct subprogram_body;
struct subprogram_specification;
struct subprogram_specification_function;
struct subprogram_specification_procedure;
struct subtype_declaration;
struct subtype_indication;
struct suffix;
struct target;
struct term;
struct timeout_clause;
struct type_conversion;
struct type_declaration;
struct type_definition;
struct unconstrained_array_definition;
struct use_clause;
struct variable_assignment_statement;
struct variable_declaration;
struct wait_statement;
struct waveform;
struct waveform_element;
struct waveform_element_list;



struct nullary;


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FWD_HPP_ */
