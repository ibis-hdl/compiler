/*
 * assertion.hpp
 *
 *  Created on: 04.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSERTION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSERTION_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/condition.hpp>
#include <eda/vhdl/ast/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>


namespace eda { namespace vhdl { namespace ast {


struct assertion : position_tagged
{
    ast::condition                      condition;
    optional<ast::expression>           report;
    optional<ast::expression>           severity;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ASSERTION_HPP_ */
