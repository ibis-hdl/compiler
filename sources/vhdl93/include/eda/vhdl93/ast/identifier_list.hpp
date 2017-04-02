/*
 * identifier_list.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_LIST_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_LIST_HPP_


#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct identifier;


struct identifier_list
{
    std::vector<identifier>       list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_LIST_HPP_ */
