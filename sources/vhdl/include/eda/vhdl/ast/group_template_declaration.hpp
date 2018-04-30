/*
 * group_template_declaration.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_TEMPLATE_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_TEMPLATE_DECLARATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/entity_class_entry_list.hpp>


namespace eda { namespace vhdl { namespace ast {


struct group_template_declaration : position_tagged
{
    ast::identifier                 identifier;
    ast::entity_class_entry_list    entity_class_entry_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_TEMPLATE_DECLARATION_HPP_ */
