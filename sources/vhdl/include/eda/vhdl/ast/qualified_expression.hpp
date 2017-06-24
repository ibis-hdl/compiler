/*
 * qualified_expression.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_QUALIFIED_EXPRESSION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_QUALIFIED_EXPRESSION_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/aggregate.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/type_mark.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


struct qualified_expression : position_tagged
{
    ast::type_mark          type_mark;
    x3::variant<
        ast::nullary,
        ast::expression,
        ast::aggregate
    >                       aggregate_or_expression;    // Note iverilog/vhdl aggregate_or_primary, case_statement_alternative ff
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_QUALIFIED_EXPRESSION_HPP_ */
