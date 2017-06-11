/*
 * element_association.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_ASSOCIATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_ASSOCIATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/choices.hpp>
#include <eda/vhdl93/ast/expression.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct element_association : position_tagged
{
    ast::choices            choices;
    ast::expression         expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ELEMENT_ASSOCIATION_HPP_ */
