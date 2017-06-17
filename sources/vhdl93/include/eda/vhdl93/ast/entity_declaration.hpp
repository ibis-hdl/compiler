/*
 * entity_declaration.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/entity_header.hpp>
#include <eda/vhdl93/ast/entity_declarative_part.hpp>
#include <eda/vhdl93/ast/entity_statement_part.hpp> // FixMe / ToDo
#include <eda/vhdl93/ast/simple_name.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct entity_declaration : position_tagged
{
    ast::identifier                 identifier;
    ast::entity_header              entity_header;
    ast::entity_declarative_part    entity_declarative_part;
    ast::entity_statement_part      entity_statement_part;
    ast::simple_name                name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENTITY_DECLARATION_HPP_ */
