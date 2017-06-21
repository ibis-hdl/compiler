/*
 * library_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_UNIT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/primary_unit.hpp>
#include <eda/vhdl93/ast/secondary_unit.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct library_unit : x3::variant<
    ast::nullary,
    ast::primary_unit,
    ast::secondary_unit
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_LIBRARY_UNIT_HPP_ */
