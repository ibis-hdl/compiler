/*
 * entity_header.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_HEADER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_HEADER_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/generic_clause.hpp>
#include <eda/vhdl/ast/port_clause.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct entity_header : x3::variant<
    ast::nullary,
    ast::generic_clause,    // formal_generic_clause
    ast::port_clause        // formal_port_clause
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_HEADER_HPP_ */
