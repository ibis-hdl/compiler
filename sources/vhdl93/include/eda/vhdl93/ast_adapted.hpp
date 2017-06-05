/*
 * ast_adapted.hpp
 *
 *  Created on: 15.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_


#include <eda/vhdl93/ast.hpp>

#include <boost/fusion/include/adapt_struct.hpp>


BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::access_type_definition,
    subtype_indication
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::actual_part_chunk,
    context_tied_name, actual_designator
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::assertion,
    condition, report, severity
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::assertion_statement,
    label, assertion
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::association_element,
    formal_part, actual_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::attribute_declaration,
    identifier, type_mark
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::attribute_name,
    prefix, signature, attribute_designator, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::attribute_specification,
    attribute_designator, entity_specification, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::based_literal,
    base, number, exponent
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::bit_string_literal,
    literal, hint
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::character_literal,
    literal
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::condition,
   boolean_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::condition_clause,
    condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::decimal_literal,
    literal, hint
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::delay_mechanism,
    time_expression, type
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::entity_designator,
    entity_tag, signature
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::entity_specification,
    entity_name_list, entity_class
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::exit_statement,
    label, loop_label, condition
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::expression,
    relation, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::expression::chunk,
    logical_operator, relation
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::factor_binary_operation,
    primary_lhs, operator_, primary_rhs
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::factor_unary_operation,
    operator_, primary
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::formal_part_chunk,
    context_tied_name, formal_designator
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::function_call,
    function_name, actual_parameter_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::identifier,
    name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::indexed_name,
    prefix, expression_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::library_clause,
    logical_name_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::options,
    guarded, delay_mechanism
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::null_statement,
    label
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::physical_literal,
    literal, unit_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::procedure_call,
    procedure_name, actual_parameter_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::procedure_call_statement,
    label, procedure_call
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::range_expression, // part of range
    lhs, direction, rhs
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::relation,
    shift_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::relation::chunk,
    relational_operator, shift_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::report_statement,
    label, report, severity
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::return_statement,
    label, expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::selected_name,
    prefix, suffix
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::selected_waveform,
    waveform, choices
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::sensitivity_clause,
    sensitivity_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::shift_expression,
    simple_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::shift_expression::chunk,
    shift_operator, simple_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::signal_assignment_statement,
    label, target, delay_mechanism, waveform
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::signature,
    parameter_type_list, return_type
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::simple_expression,
    sign, term, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::simple_expression::chunk,
    adding_operator, term
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::string_literal,
    literal
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::subtype_indication,
    unspecified_name_list, constraint
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::term,
    factor, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::term::chunk,
    multiplying_operator, factor
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::timeout_clause,
    time_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::use_clause::selected_name,
    prefix_list, suffix
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::use_clause,
    list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::wait_statement,
    label, sensitivity_clause, condition_clause, timeout_clause
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::waveform_element,
    form, time_expression
)


#include <eda/vhdl93/ast/traits/move_to.hpp>


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_ */
