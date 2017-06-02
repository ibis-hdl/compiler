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

//#include <eda/vhdl93/ast/name.hpp>
#include <string>


namespace eda { namespace vhdl93 { namespace ast {


struct name;


struct function_call : position_tagged
{
    x3::forward_ast<ast::name>  function_name;
    std::string                 actual_parameter_part;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_ */
