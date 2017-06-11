/*
 * assertion.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/condition.hpp>
#include <eda/vhdl93/ast/expression.hpp>
#include <eda/vhdl93/ast/optional.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct assertion : position_tagged
{
    ast::condition                      condition;
    optional<ast::expression>           report;
    optional<ast::expression>           severity;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ASSERTION_HPP_ */
