/*
 * subtype_declaration.hpp
 *
 *  Created on: 10.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_DECLARATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>

#include <string_view>


namespace eda { namespace vhdl93 { namespace ast {


struct subtype_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::subtype_indication     subtype_indication;
};


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUBTYPE_DECLARATION_HPP_ */
