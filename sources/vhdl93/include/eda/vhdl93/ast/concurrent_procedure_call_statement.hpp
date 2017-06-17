/*
 * concurrent_procedure_call_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/procedure_call.hpp>
#include <eda/vhdl93/ast/util/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct concurrent_procedure_call_statement : position_tagged
{
    optional<ast::label>            label;
    bool                            postponed;
    ast::procedure_call             procedure_call;

    concurrent_procedure_call_statement() : postponed{}
    { }
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_ */
