/*
 * architecture_body.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ARCHITECTURE_BODY_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ARCHITECTURE_BODY_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/architecture_declarative_part.hpp>
#include <eda/vhdl/ast/architecture_statement_part.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct architecture_body : position_tagged
{
    ast::identifier                     identifier;
    ast::name                           entity_name;
    ast::architecture_declarative_part  declarative_part;
    ast::architecture_statement_part    statement_part;
    optional<ast::identifier>           end_name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ARCHITECTURE_BODY_HPP_ */
