/*
 * procedure_call_statement.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_STATEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/procedure_call.hpp>

#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct procedure_call_statement : position_tagged
{
    boost::optional<ast::label>     label;
    ast::procedure_call             procedure_call;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PROCEDURE_CALL_STATEMENT_HPP_ */