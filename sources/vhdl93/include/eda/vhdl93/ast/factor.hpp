/*
 * factor.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;

struct primary;
struct unary_expression;
struct binary_expression;

struct factor :
    x3::variant<
        x3::forward_ast<unary_expression>,
        x3::forward_ast<binary_expression>,
        x3::forward_ast<primary>
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FACTOR_HPP_ */
