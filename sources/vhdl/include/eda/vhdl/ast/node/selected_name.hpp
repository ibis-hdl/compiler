/*
 * selected_name.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_NAME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_NAME_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/prefix.hpp>
#include <eda/vhdl/ast/node/suffix.hpp>


namespace eda { namespace vhdl { namespace ast {


struct selected_name : position_tagged
{
    ast::prefix             prefix;
    ast::suffix             suffix;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SELECTED_NAME_HPP_ */