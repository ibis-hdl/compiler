/*
 * library_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LIBRARY_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LIBRARY_UNIT_HPP_


#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <eda/vhdl/ast/primary_unit.hpp>
#include <eda/vhdl/ast/secondary_unit.hpp>
#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/nullary.hpp>


namespace eda { namespace vhdl { namespace ast {


struct library_unit : x3::variant<
    ast::nullary,
    ast::primary_unit,
    ast::secondary_unit
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LIBRARY_UNIT_HPP_ */
