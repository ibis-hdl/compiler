/*
 * name.hpp
 *
 *  Created on: 05.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>
#include <eda/vhdl93/ast/operator_symbol.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


// name ::=
//      simple_name
//    | operator_symbol
//    | selected_name
//    | indexed_name
//    | slice_name
//    | attribute_name
#if 0
using name = x3::variant<
    nullary,
    // attribute_name,
    // indexed_name,
    operator_symbol,
    // selected_name,
    simple_name
    // slice_name
>;
#else
struct name : x3::variant<
    nullary,
    simple_name,
    operator_symbol
    // indexed_name,
    // selected_name,
    // slice_name
    // attribute_name,
>
{
    using base_type::base_type;
    using base_type::operator=;
};
#endif

} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_NAME_HPP_ */
