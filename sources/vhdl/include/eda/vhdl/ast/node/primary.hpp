/*
 * primary.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRIMARY_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRIMARY_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/literal.hpp>


namespace eda { namespace vhdl { namespace ast {


struct name;
struct aggregate;
struct expression;
struct function_call;
struct qualified_expression;
struct allocator;


// primary ::=
//      name
//    | literal
//    | aggregate
//    | function_call
//    | qualified_expression
//    | type_conversion
//    | allocator
//    | ( expression )
struct primary : variant<
    nullary,
    forward_ast<name>,
    literal,
    forward_ast<aggregate>,
    forward_ast<function_call>,
    forward_ast<qualified_expression>,
    // type_conversion,
    forward_ast<allocator>,
    forward_ast<expression>
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRIMARY_HPP_ */