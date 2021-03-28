/*
 * group_declaration.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_DECLARATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/name.hpp>
#include <eda/vhdl/ast/node/group_constituent_list.hpp>


namespace eda { namespace vhdl { namespace ast {


struct group_declaration : position_tagged
{
    ast::identifier             identifier;
    ast::name                   group_template_name;
    ast::group_constituent_list group_constituent_list;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GROUP_DECLARATION_HPP_ */
