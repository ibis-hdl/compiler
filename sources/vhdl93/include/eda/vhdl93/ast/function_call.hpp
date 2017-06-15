/*
 * function_call.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

//#include <eda/vhdl93/ast/name.hpp>
#include <string_view>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct name;


struct function_call : position_tagged
{
    x3::forward_ast<ast::name>  function_name;
    std::string_view            actual_parameter_part;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_FUNCTION_CALL_HPP_ */
