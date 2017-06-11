/*
 * alias_declaration.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DECLARATION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/alias_designator.hpp>
#include <eda/vhdl93/ast/subtype_indication.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/signature.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct alias_declaration : position_tagged
{
    ast::alias_designator                       alias_designator;
    boost::optional<ast::subtype_indication>    subtype_indication;
    ast::name                                   name;
    boost::optional<ast::signature>             signature;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ALIAS_DECLARATION_HPP_ */
