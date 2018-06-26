/*
 * identifier.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>


namespace eda { namespace vhdl { namespace ast {


struct identifier : position_tagged
{
    ast::string_span                                name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_HPP_ */
