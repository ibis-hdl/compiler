/*
 * physical_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct abstract_literal;


struct physical_literal
{
    x3::forward_ast<abstract_literal> literal;
    std::string                     unit_name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PHYSICAL_LITERAL_HPP_ */
