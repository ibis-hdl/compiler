/*
 * guarded_signal_specification.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/signal_list.hpp>
#include <eda/vhdl93/ast/type_mark.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct guarded_signal_specification : position_tagged
{
    ast::signal_list            guarded_signal_list;
    ast::type_mark              type_mark;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_ */
