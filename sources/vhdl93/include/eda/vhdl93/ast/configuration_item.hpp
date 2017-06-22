/*
 * configuration_item.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_ITEM_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_ITEM_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
//FORWARD #include <eda/vhdl93/ast/block_configuration.hpp>
#include <eda/vhdl93/ast/component_configuration.hpp>
#include <vector>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct block_configuration;


/**
 * Ast node cyclic dependency as:
 *
 * \dot
 * digraph component_configuration  {
 *   component_configuration -> block_configuration;
 *   block_configuration -> configuration_item;
 *   configuration_item -> component_configuration;
 *   configuration_item -> block_configuration [ label="forward"];
 * }
 * \enddot
 */
struct configuration_item : x3::variant<
    ast::nullary,
    x3::forward_ast<ast::block_configuration>,
    ast::component_configuration
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONFIGURATION_ITEM_HPP_ */
