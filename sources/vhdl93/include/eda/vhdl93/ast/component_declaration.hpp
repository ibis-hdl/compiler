/*
 * component_declaration.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/generic_clause.hpp>
#include <eda/vhdl93/ast/port_clause.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct component_declaration : position_tagged
{
    ast::identifier                 identifier;
    optional<ast::generic_clause>   local_generic_clause;
    optional<ast::port_clause>      local_port_clause;
    optional<ast::simple_name>      name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_COMPONENT_DECLARATION_HPP_ */
