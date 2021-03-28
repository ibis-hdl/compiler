/*
 * design_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGN_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGN_UNIT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/context_clause.hpp>
#include <eda/vhdl/ast/node/library_unit.hpp>


namespace eda { namespace vhdl { namespace ast {


struct design_unit : position_tagged
{
    ast::context_clause                 context_clause;
    ast::library_unit                   library_unit;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGN_UNIT_HPP_ */
