/*
 * report_statement.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_REPORT_STATEMENT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_REPORT_STATEMENT_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/label.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <boost/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct report_statement : position_tagged
{
    boost::optional<ast::label>         label;
    ast::expression                     report;
    boost::optional<ast::expression>    severity;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_REPORT_STATEMENT_HPP_ */
