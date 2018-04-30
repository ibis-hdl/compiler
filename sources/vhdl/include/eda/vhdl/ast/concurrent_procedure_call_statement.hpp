/*
 * concurrent_procedure_call_statement.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/procedure_call.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct concurrent_procedure_call_statement : position_tagged
{
    optional<ast::label>            label;
    bool                            postponed;
    ast::procedure_call             procedure_call;

    concurrent_procedure_call_statement()
    : postponed{}
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_CONCURRENT_PROCEDURE_CALL_STATEMENT_HPP_ */
