/*
 * function_call.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FUNCTION_CALL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FUNCTION_CALL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

//#include <eda/vhdl/ast/name.hpp>
#include <string_view>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct name;


struct function_call : position_tagged
{
    x3::forward_ast<ast::name>  function_name;
    std::string_view            actual_parameter_part;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FUNCTION_CALL_HPP_ */
