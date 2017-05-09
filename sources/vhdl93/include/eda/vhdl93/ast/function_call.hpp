/*
 * function_call.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct function_name : ast::identifier
{
    function_name& operator=(std::string_view&& sv)
    {
        name = std::move(sv);
        return *this;
    }
};


struct function_call : position_tagged
{
    function_name           name;
    std::string             actual_parameter_part;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_ */
