/*
 * selected_name.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_NAME_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/prefix.hpp>
#include <eda/vhdl93/ast/suffix.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct selected_name : position_tagged
{
    ast::prefix             prefix;
    ast::suffix             suffix;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SELECTED_NAME_HPP_ */
