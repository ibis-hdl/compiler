/*
 * operand.hpp
 *
 *  Created on: 09.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERAND_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERAND_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>

#include <eda/vhdl93/ast/nullary.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct binary_operation;
struct primary;
struct unary_operation;


struct operand :
    x3::variant<
        nullary,
        x3::forward_ast<primary>,
        x3::forward_ast<unary_operation>,
        x3::forward_ast<binary_operation>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERAND_HPP_ */
