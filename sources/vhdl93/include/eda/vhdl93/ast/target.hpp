/*
 * target.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TARGET_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TARGET_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/name.hpp>
//#include <eda/vhdl93/ast/aggregate.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {

#if 0
using target = x3::variant<
    nullary,
    name
    //aggregate
>;
#else
struct target : x3::variant<
    nullary,
    name
    //aggregate
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TARGET_HPP_ */
