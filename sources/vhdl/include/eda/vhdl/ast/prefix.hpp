/*
 * prefix.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PREFIX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PREFIX_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
//#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/function_call.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct name;

#if 0
using prefix = x3::variant<
    nullary,
    name,
    function_call
>;
#else
struct prefix : x3::variant<
    nullary,
    x3::forward_ast<name>,
    function_call
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PREFIX_HPP_ */
