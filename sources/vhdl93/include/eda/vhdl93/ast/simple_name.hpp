/*
 * simple_name.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_


#include <eda/vhdl93/ast/identifier.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct simple_name : ast::identifier
{
    simple_name& operator=(std::string_view const& sv)
    {
        name = sv;
        return *this;
    }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SIMPLE_NAME_HPP_ */
