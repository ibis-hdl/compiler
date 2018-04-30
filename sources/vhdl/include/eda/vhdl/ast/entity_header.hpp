/*
 * entity_header.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_HEADER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_HEADER_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/generic_clause.hpp>
#include <eda/vhdl/ast/port_clause.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct entity_header : position_tagged
{
    optional<ast::generic_clause>   formal_generic_clause;
    optional<ast::port_clause>      formal_port_clause;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_HEADER_HPP_ */
