/*
 * position_tagged.hpp
 *
 *  Created on: 23.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

/* special boost.spirit.x3 header to get rid off the annoying unused parameter
 * warnings from x3 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#pragma GCC diagnostic pop


namespace eda { namespace vhdl { namespace ast {


using position_tagged = x3::position_tagged;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_POSITION_TAGGED_HPP_ */
