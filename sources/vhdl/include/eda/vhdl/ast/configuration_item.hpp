/*
 * configuration_item.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_ITEM_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_ITEM_HPP_


#include <eda/vhdl/ast/util/variant.hpp>


#include <eda/vhdl/ast/util/nullary.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct block_configuration;
struct component_configuration;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 * digraph component_configuration  {
 *   component_configuration -> block_configuration;
 *   block_configuration     -> configuration_item;
 *   configuration_item      -> component_configuration;
 *   configuration_item      -> block_configuration [ label="forward"];
 * }
 * \enddot
 */
struct configuration_item : variant<
    ast::nullary,
    forward_ast<ast::block_configuration>,
    forward_ast<ast::component_configuration>
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_ITEM_HPP_ */
