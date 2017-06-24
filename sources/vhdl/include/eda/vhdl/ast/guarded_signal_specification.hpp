/*
 * guarded_signal_specification.hpp
 *
 *  Created on: 17.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/signal_list.hpp>
#include <eda/vhdl/ast/type_mark.hpp>


namespace eda { namespace vhdl { namespace ast {


struct guarded_signal_specification : position_tagged
{
    ast::signal_list            guarded_signal_list;
    ast::type_mark              type_mark;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GUARDED_SIGNAL_SPECIFICATION_HPP_ */
