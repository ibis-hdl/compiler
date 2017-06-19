/*
 * parameter_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PARAMETER_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PARAMETER_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/identifier.hpp>
#include <eda/vhdl93/ast/discrete_range.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct parameter_specification : position_tagged
{
    ast::identifier                 identifier;
    ast::discrete_range             discrete_range;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PARAMETER_SPECIFICATION_HPP_ */
