/*
 * simple_name.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_


#include <string>


namespace eda { namespace vhdl93 { namespace ast {


/* FixMe: same as ast::identifier, may be used or not. */
struct simple_name
{
    std::string        name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_ */
