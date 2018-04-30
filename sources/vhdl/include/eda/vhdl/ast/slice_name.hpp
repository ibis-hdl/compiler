/*
 * slice_name.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SLICE_NAME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SLICE_NAME_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/discrete_range.hpp>
#include <eda/vhdl/ast/prefix.hpp>


namespace eda { namespace vhdl { namespace ast {


struct slice_name : position_tagged
{
    ast::prefix                     prefix;
    ast::discrete_range             discrete_range;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SLICE_NAME_HPP_ */
