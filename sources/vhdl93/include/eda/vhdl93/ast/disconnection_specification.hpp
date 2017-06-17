/*
 * disconnection_specification.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCONNECTION_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCONNECTION_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/guarded_signal_specification.hpp>
#include <eda/vhdl93/ast/expression.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct disconnection_specification : position_tagged
{
    ast::guarded_signal_specification   guarded_signal_specification;
    ast::expression                     time_expression;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DISCONNECTION_SPECIFICATION_HPP_ */
