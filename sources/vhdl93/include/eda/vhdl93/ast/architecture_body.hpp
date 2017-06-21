/*
 * architecture_body.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_BODY_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_BODY_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/architecture_declarative_part.hpp>
#include <eda/vhdl93/ast/architecture_statement_part.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct architecture_body : position_tagged
{
    ast::identifier                     identifier;
    ast::name                           entity_name;
    ast::architecture_declarative_part  declarative_part;
    ast::architecture_statement_part    statement_part;
    optional<ast::identifier>           end_name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ARCHITECTURE_BODY_HPP_ */
