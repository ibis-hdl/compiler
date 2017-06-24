/*
 * subprogram_body.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_BODY_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_BODY_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/subprogram_specification.hpp>
#include <eda/vhdl/ast/subprogram_declarative_part.hpp>
#include <eda/vhdl/ast/subprogram_statement_part.hpp>
#include <eda/vhdl/ast/keyword_token.hpp>
#include <eda/vhdl/ast/designator.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct subprogram_body : position_tagged
{
    ast::subprogram_specification       specification;
    ast::subprogram_declarative_part    declarative_part;
    ast::subprogram_statement_part      statement_part;
    optional<ast::keyword_token>        kind;
    optional<ast::designator>           designator;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SUBPROGRAM_BODY_HPP_ */
