/*
 * position_tagged.hpp
 *
 *  Created on: 23.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_


#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>


namespace eda { namespace vhdl { namespace ast {


struct position_tagged : x3::position_tagged { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_ */
