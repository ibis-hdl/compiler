/*
 * case_statement.hpp
 *
 *  Created on: 05.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CASE_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CASE_STATEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/case_statement_alternative.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct case_statement : position_tagged
{
    optional<ast::label>                            label;
    ast::expression                                 expression;
    std::vector<ast::case_statement_alternative>    alternatives;
    optional<ast::label>                            end_label;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CASE_STATEMENT_HPP_ */
