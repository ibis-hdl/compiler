/*
 * ast_adapted.hpp
 *
 *  Created on: 15.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ADAPTED_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ADAPTED_HPP_


#include <boost/fusion/include/adapt_struct.hpp>
#include <eda/vhdl/ast.hpp>


BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::access_type_definition,
    subtype_indication
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::actual_part_chunk,
    context_tied_name, actual_designator
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::alias_declaration,
    alias_designator, subtype_indication, name, signature
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::architecture_body,
    identifier, entity_name, declarative_part, statement_part, end_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::assertion,
    condition, report, severity
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::assertion_statement,
    label, assertion
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::association_element,
    formal_part, actual_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::attribute_declaration,
    identifier, type_mark
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::attribute_name,
    prefix, signature, attribute_designator, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::attribute_specification,
    attribute_designator, entity_specification, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::based_literal,
    base, number, exponent
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::binding_indication,
    entity_aspect, generic_map_aspect, port_map_aspect
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::bit_string_literal,
    literal, hint
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::block_configuration,
    block_specification, use_clause_list, configuration_item_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::block_header::generic_part_chunk,
    generic_clause, generic_map_aspect
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::block_header::port_part_chunk,
    port_clause, port_map_aspect
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::block_header,
    generic_part, port_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::block_specification_chunk,
    label, index_specification
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::block_statement,
    label, guard_expression, header, declarative_part, statement_part, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::case_statement,
    label, expression, alternatives, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::case_statement_alternative,
    choices, sequence_of_statements
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::character_literal,
    literal
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::component_configuration,
    component_specification, binding_indication, block_configuration
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::component_declaration,
    identifier, local_generic_clause, local_port_clause, name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::component_instantiation_statement,
    label, instantiated_unit, generic_map_aspect, port_map_aspect
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::component_specification,
    instantiation_list, component_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::concurrent_assertion_statement,
    label, postponed, assertion
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::concurrent_procedure_call_statement,
    label, postponed, procedure_call
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::concurrent_signal_assignment_statement,
    label, postponed, signal_assignment
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::conditional_signal_assignment,
    target, options, conditional_waveforms
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::conditional_waveforms::chunk,
    waveform, condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::conditional_waveforms,
    chunks, waveform, condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::condition_clause,
    condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::configuration_declaration,
    identifier, entity_name, declarative_part, block_configuration, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::configuration_specification,
    component_specification, binding_indication
)
BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::constant_declaration,
    identifier_list, subtype_indication, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::constrained_array_definition,
    index_constraint, element_subtype_indication
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::decimal_literal,
    literal, hint
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::delay_mechanism,
    time_expression, type
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::design_unit,
    context_clause, library_unit
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::disconnection_specification,
    guarded_signal_specification, time_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::element_association,
    choices, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::element_declaration,
    identifier_list, element_subtype_definition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::entity_aspect_entity,
    name, architecture_identifier
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::entity_aspect_configuration,
    name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::entity_declaration,
    identifier, header, declarative_part, statement_part, name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::entity_designator,
    entity_tag, signature
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::entity_header,
    formal_generic_clause, formal_port_clause
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::entity_specification,
    entity_name_list, entity_class
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::exit_statement,
    label, loop_label, condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::expression,
    relation, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::expression::chunk,
    logical_operator, relation
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::factor_binary_operation,
    primary_lhs, operator_, primary_rhs
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::factor_unary_operation,
    operator_, primary
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::file_declaration,
    identifier_list, subtype_indication, file_open_information
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::file_open_information,
        file_open_kind_expression, file_logical_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::formal_part_chunk,
    context_tied_name, formal_designator
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::function_call,
    function_name, actual_parameter_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::generate_statement,
    label, generation_scheme, block_declarative_parts, concurrent_statements, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::generic_clause,
    generic_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::generic_map_aspect,
    association_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::group_declaration,
    identifier, group_template_name, group_constituent_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::group_template_declaration,
    identifier, entity_class_entry_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::guarded_signal_specification,
    guarded_signal_list, type_mark
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::if_statement,
    label, if_condition, then_sequence_of_statements, elseif_chunks, else_sequence_of_statements, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::if_statement::elsif_chunk,
    condition, sequence_of_statements
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::identifier,
    name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::indexed_name,
    prefix, expression_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::index_subtype_definition,
    type_mark
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::instantiated_unit_chunk,
    entity_name, architecture_identifier
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::interface_constant_declaration,
    CONSTANT, identifier_list, IN, subtype_indication, static_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::interface_signal_declaration,
    SIGNAL, identifier_list, mode, subtype_indication, BUS, static_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::interface_variable_declaration,
    VARIABLE, identifier_list, mode, subtype_indication, static_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::interface_file_declaration,
    identifier_list, subtype_indication
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::library_clause,
    logical_name_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::loop_statement,
    label, iteration_scheme, sequence_of_statements, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::next_statement,
    label, loop_label, condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::null_statement,
    label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::options,
    guarded, delay_mechanism
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::package_body,
    name, declarative_part, end_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::package_declaration,
    identifier, declarative_part, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::parameter_specification,
    identifier, discrete_range
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::physical_literal,
    literal, unit_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::physical_type_definition,
    range_constraint, primary_unit_declaration, secondary_unit_declarations, physical_type_simple_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::port_clause,
    port_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::port_map_aspect,
    association_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::procedure_call,
    procedure_name, actual_parameter_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::procedure_call_statement,
    label, procedure_call
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::process_statement,
    label, postponed, sensitivity_list, declarative_part, statement_part, end_postponed, end_label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::qualified_expression,
    type_mark, aggregate_or_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::range_expression, // part of range
    lhs, direction, rhs
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::record_type_definition,
    element_declarations, name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::relation,
    shift_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::relation::chunk,
    relational_operator, shift_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::report_statement,
    label, report, severity
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::return_statement,
    label, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::secondary_unit_declaration,
    identifier, physical_literal
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::selected_name,
    prefix, suffix
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::selected_signal_assignment,
    expression, target, options, selected_waveforms
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::selected_waveform,
    waveform, choices
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::sensitivity_clause,
    sensitivity_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::shift_expression,
    simple_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::shift_expression::chunk,
    shift_operator, simple_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::signal_assignment_statement,
    label, target, delay_mechanism, waveform
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::signal_declaration,
    identifier_list, subtype_indication, signal_kind, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::signature,
    parameter_type_list, return_type
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::simple_expression,
    sign, term, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::simple_expression::chunk,
    adding_operator, term
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::slice_name,
    prefix, discrete_range
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::string_literal,
    literal
)
BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::subprogram_body,
    specification, declarative_part, statement_part, kind, designator
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::subprogram_specification_procedure,
    designator, formal_parameter_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::subprogram_specification_function,
    impure, designator, formal_parameter_list, return_type_mark
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::subtype_declaration,
    identifier, subtype_indication
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::subtype_indication,
    unspecified_name_list, constraint
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::term,
    factor, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::term::chunk,
    multiplying_operator, factor
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::timeout_clause,
    time_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::type_declaration,
    identifier, type_definition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::type_conversion,
    type_mark, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::unconstrained_array_definition,
    index_subtype_definitions, element_subtype_indication
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::use_clause::selected_name,
    prefix_list, suffix
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::use_clause,
    list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::variable_assignment_statement,
    label, target, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::variable_declaration,
    shared, identifier_list, subtype_indication, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::wait_statement,
    label, sensitivity_clause, condition_clause, timeout_clause
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl::ast::waveform_element,
    form, time_expression
)


#include <eda/vhdl/ast/traits/move_to.hpp>


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ADAPTED_HPP_ */
