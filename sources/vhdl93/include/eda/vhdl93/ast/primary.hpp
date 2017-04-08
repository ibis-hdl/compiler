/*
 * primary.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct aggregate;
struct allocator;
struct expression;
struct function_call;
struct literal;
struct name;
struct qualified_expression;
struct type_conversion;

struct primary :
    x3::variant<
//        x3::forward_ast<aggregate>,
//        x3::forward_ast<allocator>,
//        x3::forward_ast<expression>,
//        x3::forward_ast<function_call>,
        x3::forward_ast<literal>,
        x3::forward_ast<name>
//        x3::forward_ast<qualified_expression>,
//        x3::forward_ast<type_conversion>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PRIMARY_HPP_ */
