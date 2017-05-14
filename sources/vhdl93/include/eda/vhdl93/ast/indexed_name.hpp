/*
 * indexed_name.hpp
 *
 *  Created on: 12.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEXED_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEXED_NAME_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/prefix.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct expression;


struct indexed_name : position_tagged
{
    ast::prefix                     prefix;
    std::vector<expression>         expression_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_INDEXED_NAME_HPP_ */
