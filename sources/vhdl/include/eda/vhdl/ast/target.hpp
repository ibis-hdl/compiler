/*
 * target.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TARGET_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TARGET_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/aggregate.hpp>
#include <eda/vhdl/ast/name.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {

#if 0
using target = x3::variant<
    nullary,
    name,
    aggregate
>;
#else
struct target : x3::variant<
    nullary,
    name,
    aggregate
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TARGET_HPP_ */
