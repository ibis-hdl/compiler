/*
 * type_mark.hpp
 *
 *  Created on: 14.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_


/* FixMe: type_mark is basically an ast::name, but directly deriving from this
 * result into compile  error of invalid application of 'sizeof' to incomplete
 * type 'eda::vhdl93::ast::name'
 * The solution of this affects ast::subtype_indication ans printer! */

#if 1
#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>
#include <eda/vhdl93/ast/operator_symbol.hpp>
#include <eda/vhdl93/ast/selected_name.hpp>
#include <eda/vhdl93/ast/indexed_name.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct type_mark : x3::variant<
    nullary,
    simple_name,
    operator_symbol,
    selected_name
    //indexed_name
    // slice_name
    // attribute_name,
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#else

#include <eda/vhdl93/ast/name.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct type_mark : ast::name
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast

#endif


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_TYPE_MARK_HPP_ */
