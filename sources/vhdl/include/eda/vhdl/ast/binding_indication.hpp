/*
 * binding_indication.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BINDING_INDICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BINDING_INDICATION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/entity_aspect.hpp>
#include <eda/vhdl/ast/generic_map_aspect.hpp>
#include <eda/vhdl/ast/port_map_aspect.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct binding_indication : position_tagged
{
    optional<ast::entity_aspect>        entity_aspect;
    ast::generic_map_aspect             generic_map_aspect;
    ast::port_map_aspect                port_map_aspect;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_BINDING_INDICATION_HPP_ */
