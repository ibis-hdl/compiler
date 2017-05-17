/*
 * condition.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/expression.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct condition : position_tagged
{
   ast::expression          boolean_expression;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONDITION_HPP_ */