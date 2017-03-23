/*
 * identifier.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_


#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct identifier : public std::string
{
	using std::string::string;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_ */
