/*
 * position_tagged.hpp
 *
 *  Created on: 23.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UTIL_POSITION_TAGGED_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UTIL_POSITION_TAGGED_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct position_tagged : x3::position_tagged { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_UTIL_POSITION_TAGGED_HPP_ */
