/*
 * entity_declaration.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DECLARATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DECLARATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/entity_declarative_part.hpp>
#include <eda/vhdl/ast/entity_header.hpp>
#include <eda/vhdl/ast/entity_statement_part.hpp>
#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct entity_declaration : position_tagged
{
    ast::identifier                         identifier;
    ast::entity_header                      header;
    ast::entity_declarative_part            declarative_part;
    optional<ast::entity_statement_part>    statement_part;
    optional<ast::simple_name>              name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_DECLARATION_HPP_ */
