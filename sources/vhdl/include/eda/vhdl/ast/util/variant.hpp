/*
 * variant.hpp
 *
 *  Created on: 30.04.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_VARIANT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_VARIANT_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


template <typename ...Types>
using variant = x3::variant<Types...>;

template <typename T>
using forward_ast = x3::forward_ast<T>;


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_VARIANT_HPP_ */
