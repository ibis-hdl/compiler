/*
 * unconstrained_array_definition.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/index_subtype_definition.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct unconstrained_array_definition : position_tagged
{
    std::vector<ast::index_subtype_definition>  index_subtype_definitions;
    ast::subtype_indication                     element_subtype_indication;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UNCONSTRAINED_ARRAY_DEFINITION_HPP_ */
