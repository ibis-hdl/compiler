/*
 * alias_declaration.hpp
 *
 *  Created on: 11.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALIAS_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALIAS_DECLARATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/alias_designator.hpp>
#include <eda/vhdl/ast/subtype_indication.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/signature.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct alias_declaration : position_tagged
{
    ast::alias_designator                       alias_designator;
    optional<ast::subtype_indication>           subtype_indication;
    ast::name                                   name;
    optional<ast::signature>                    signature;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ALIAS_DECLARATION_HPP_ */
