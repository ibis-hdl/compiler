/*
 * operator_symbol.hpp
 *
 *  Created on: 12.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct operator_symbol : x3::position_tagged
{
    std::string         symbol;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_ */
