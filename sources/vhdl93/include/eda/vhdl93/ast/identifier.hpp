/*
 * identifier.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp> // x3::position_tagged

#include <eda/support/boost/spirit_x3/string_view.hpp>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct identifier : x3::position_tagged
{
    std::string_view            name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_ */
