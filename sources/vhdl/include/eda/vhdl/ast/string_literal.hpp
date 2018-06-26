/*
 * string_literal.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STRING_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STRING_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>


namespace eda { namespace vhdl { namespace ast {


struct string_literal : position_tagged
{
    ast::string_span                                literal;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STRING_LITERAL_HPP_ */
