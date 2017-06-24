/*
 * component_declaration.hpp
 *
 *  Created on: 16.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_DECLARATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/generic_clause.hpp>
#include <eda/vhdl/ast/port_clause.hpp>
#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct component_declaration : position_tagged
{
    ast::identifier                 identifier;
    optional<ast::generic_clause>   local_generic_clause;
    optional<ast::port_clause>      local_port_clause;
    optional<ast::simple_name>      name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_COMPONENT_DECLARATION_HPP_ */
