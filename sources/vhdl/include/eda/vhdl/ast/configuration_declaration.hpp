/*
 * configuration_declaration.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_DECLARATION_HPP_


#include <eda/vhdl/ast/block_configuration.hpp>
#include <eda/vhdl/ast/configuration_declarative_part.hpp>
#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>


namespace eda { namespace vhdl { namespace ast {


struct configuration_declaration : position_tagged
{
    ast::identifier                     identifier;
    ast::name                           entity_name;
    ast::configuration_declarative_part declarative_part;
    ast::block_configuration            block_configuration;
    optional<ast::identifier>           end_label;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONFIGURATION_DECLARATION_HPP_ */
