/*
 * parameter_specification.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PARAMETER_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PARAMETER_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/discrete_range.hpp>


namespace eda { namespace vhdl { namespace ast {


struct parameter_specification : position_tagged
{
    ast::identifier                 identifier;
    ast::discrete_range             discrete_range;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PARAMETER_SPECIFICATION_HPP_ */
