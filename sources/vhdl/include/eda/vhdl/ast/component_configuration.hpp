/*
 * component_configuration.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_CONFIGURATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_CONFIGURATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/component_specification.hpp>
#include <eda/vhdl/ast/binding_indication.hpp>
#include <eda/vhdl/ast/block_configuration.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct component_configuration : position_tagged
{
    ast::component_specification                component_specification;
    optional<ast::binding_indication>           binding_indication;
    optional<ast::block_configuration>          block_configuration;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_CONFIGURATION_HPP_ */
