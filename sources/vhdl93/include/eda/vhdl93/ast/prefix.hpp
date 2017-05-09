/*
 * prefix.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PREFIX_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PREFIX_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/name.hpp>
#include <eda/vhdl93/ast/function_call.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


using prefix = x3::variant<
    nullary,
    name,
    function_call
>;


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_PREFIX_HPP_ */
