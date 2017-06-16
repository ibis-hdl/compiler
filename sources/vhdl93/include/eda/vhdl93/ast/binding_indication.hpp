/*
 * binding_indication.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINDING_INDICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINDING_INDICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/entity_aspect.hpp>
#include <eda/vhdl93/ast/generic_map_aspect.hpp>
#include <eda/vhdl93/ast/port_map_aspect.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>

namespace eda { namespace vhdl93 { namespace ast {


struct binding_indication : position_tagged
{
    optional<ast::entity_aspect>        entity_aspect;
    optional<ast::generic_map_aspect>   generic_map_aspect;
    optional<ast::port_map_aspect>      port_map_aspect;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_BINDING_INDICATION_HPP_ */
