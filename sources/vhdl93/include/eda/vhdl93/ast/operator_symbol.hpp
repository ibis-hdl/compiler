/*
 * operator_symbol.hpp
 *
 *  Created on: 12.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_


#include <eda/vhdl93/ast/string_literal.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct operator_symbol : ast::string_literal
{
    operator_symbol& operator=(std::string&& sv)
    {
        literal = std::move(sv);
        return *this;
    }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_OPERATOR_SYMBOL_HPP_ */
