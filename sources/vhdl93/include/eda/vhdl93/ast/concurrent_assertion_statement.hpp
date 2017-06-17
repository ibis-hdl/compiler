/*
 * concurrent_assertion_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_ASSERTION_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_ASSERTION_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/assertion.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct concurrent_assertion_statement : position_tagged
{
    optional<ast::label>                label;
    bool                                postponed;
    ast::assertion                      assertion;

    concurrent_assertion_statement() : postponed{}
    { }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_ASSERTION_STATEMENT_HPP_ */
