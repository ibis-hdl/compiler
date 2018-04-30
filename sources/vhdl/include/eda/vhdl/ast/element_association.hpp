/*
 * element_association.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ELEMENT_ASSOCIATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ELEMENT_ASSOCIATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/choices.hpp>
#include <eda/vhdl/ast/expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct element_association : position_tagged
{
    ast::choices            choices;
    ast::expression         expression;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ELEMENT_ASSOCIATION_HPP_ */
