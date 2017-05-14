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
#include <boost/fusion/include/io.hpp>


BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::attribute_declaration,
    identifier, type_mark
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::attribute_name,
    prefix, signature, attribute_designator, expression
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

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::enumeration_type_definition,
    list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::expression::chunk,
    operator_, relation
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::expression,
    relation, rest_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::factor_binary_operation,
    primary_lhs, operator_, primary_rhs
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::factor_unary_operation,
    operator_, primary
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::function_call,
    name, actual_parameter_part
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::identifier,
    name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::identifier_list,
    list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::indexed_name,
    prefix, expression_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::library_clause,
    logical_name_list
)

// base class: string_literal
//BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::operator_symbol,
//    literal
//)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::physical_literal,
    literal, unit_name
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::relation::chunk,
    operator_, shift_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::relation,
    shift_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::selected_name,
    prefix, suffix
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::sensitivity_clause,
    sensitivity_list
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::shift_expression::chunk,
    operator_, simple_expression
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::shift_expression,
    simple_expression, rest
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::signature,
    parameter_type_list, return_type
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::simple_expression::chunk,
    operator_, term
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::simple_expression,
    sign, term, rest_list
)

// base class: identifier
//BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::simple_name,
//    name
//)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::string_literal,
    literal
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::term::chunk,
    operator_, factor
)

BOOST_FUSION_ADAPT_STRUCT(eda::vhdl93::ast::term,
    factor, rest_list
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


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ADAPTED_HPP_ */
