/*
 * group_declaration.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/group_constituent_list.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct group_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::name                   group_template_name;
    ast::group_constituent_list group_constituent_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_DECLARATION_HPP_ */
