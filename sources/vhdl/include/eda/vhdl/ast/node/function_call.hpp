/*
 * function_call.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FUNCTION_CALL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FUNCTION_CALL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp> // forward_ast

#include <eda/vhdl/ast/node/actual_parameter_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct name;


struct function_call : position_tagged
{
    forward_ast<ast::name>                          function_name;
    boost::optional<ast::actual_parameter_part>     actual_parameter_part;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_FUNCTION_CALL_HPP_ */