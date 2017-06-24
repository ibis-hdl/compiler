/*
 * secondary_unit_declaration.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SECONDARY_UNIT_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SECONDARY_UNIT_DECLARATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/physical_literal.hpp>


namespace eda { namespace vhdl { namespace ast {


struct secondary_unit_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::physical_literal       physical_literal;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SECONDARY_UNIT_DECLARATION_HPP_ */
