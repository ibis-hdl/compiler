/*
 * primary.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>


#include <eda/vhdl93/ast/nullary.hpp>
//#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/function_call.hpp>
#include <eda/vhdl93/ast/literal.hpp>
#include <eda/vhdl93/ast/name.hpp>


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct expression;

using primary = x3::variant<
    nullary,
    // aggregate,
    // allocator,
    x3::forward_ast<expression>, // break cycle
    function_call,
    literal,
    name
    // qualified_expression,
    // type_conversion
>;


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_ */
