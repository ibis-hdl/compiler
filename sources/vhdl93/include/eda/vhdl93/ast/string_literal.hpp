/*
 * string_literal.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_STRING_LITERAL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_STRING_LITERAL_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <eda/support/boost/spirit_x3/string_view.hpp>

#include <string>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct string_literal : x3::position_tagged
{
    std::string                     literal;
//    std::string_view                literal;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_STRING_LITERAL_HPP_ */
