/*
 * group_template_declaration.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_TEMPLATE_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_TEMPLATE_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/entity_class_entry_list.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct group_template_declaration : position_tagged
{
    ast::identifier                 identifier;
    ast::entity_class_entry_list    entity_class_entry_list;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GROUP_TEMPLATE_DECLARATION_HPP_ */
