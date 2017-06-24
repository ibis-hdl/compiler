/*
 * assertion_statement.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSERTION_STATEMENT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSERTION_STATEMENT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/label.hpp>
#include <eda/vhdl/ast/assertion.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct assertion_statement : position_tagged
{
    optional<ast::label>            label;
    ast::assertion                  assertion;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSERTION_STATEMENT_HPP_ */
