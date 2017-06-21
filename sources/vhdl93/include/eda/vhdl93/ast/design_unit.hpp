/*
 * design_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_UNIT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/context_clause.hpp>
#include <eda/vhdl93/ast/library_unit.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct design_unit : position_tagged
{
    ast::context_clause                 context_clause;
    ast::library_unit                   library_unit;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_UNIT_HPP_ */
