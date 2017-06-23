/*
 * component_configuration.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_CONFIGURATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_CONFIGURATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/component_specification.hpp>
#include <eda/vhdl93/ast/binding_indication.hpp>
#include <eda/vhdl93/ast/block_configuration.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct component_configuration : position_tagged
{
    ast::component_specification                component_specification;
    optional<ast::binding_indication>           binding_indication;
    optional<ast::block_configuration>          block_configuration;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_CONFIGURATION_HPP_ */
