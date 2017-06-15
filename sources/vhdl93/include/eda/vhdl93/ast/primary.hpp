/*
 * primary.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>


#include <eda/vhdl93/ast/util/nullary.hpp>
//#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/literal.hpp>
//#include <eda/vhdl93/ast/aggregate.hpp>.hpp>
#include <eda/vhdl93/ast/function_call.hpp>
//#include <eda/vhdl93/ast/expression.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct name;
struct expression;

// primary ::=
//      name
//    | literal
//    | aggregate
//    | function_call
//    | qualified_expression
//    | type_conversion
//    | allocator
//    | ( expression )
#if 0
using primary = x3::variant<
    nullary,
    // aggregate,
    // allocator,
    expression,
    function_call,
    literal,
    name
    // qualified_expression,
    // type_conversion
>;
#else
struct primary : x3::variant<
    nullary,
    x3::forward_ast<name>,
    literal,
    // aggregate,
    function_call,
    // qualified_expression,
    // type_conversion,
    // allocator,
    x3::forward_ast<expression>
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_ */
