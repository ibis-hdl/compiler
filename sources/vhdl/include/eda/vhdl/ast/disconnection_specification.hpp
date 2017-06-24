/*
 * disconnection_specification.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCONNECTION_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCONNECTION_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/guarded_signal_specification.hpp>
#include <eda/vhdl/ast/expression.hpp>


namespace eda { namespace vhdl { namespace ast {


struct disconnection_specification : position_tagged
{
    ast::guarded_signal_specification   guarded_signal_specification;
    ast::expression                     time_expression;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DISCONNECTION_SPECIFICATION_HPP_ */
