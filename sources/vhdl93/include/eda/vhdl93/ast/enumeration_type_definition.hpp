/*
 * enumeration_type_definition.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


namespace x3 = boost::spirit::x3;


struct enumeration_literal;


struct enumeration_type_definition : x3::position_tagged
{
    std::vector<enumeration_literal>    list;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_ */
