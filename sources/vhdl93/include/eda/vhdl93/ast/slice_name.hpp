/*
 * slice_name.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SLICE_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SLICE_NAME_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/prefix.hpp>
#include <eda/vhdl93/ast/discrete_range.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct slice_name : position_tagged
{
    ast::prefix                     prefix;
    ast::discrete_range             discrete_range;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SLICE_NAME_HPP_ */
