/*
 * secondary_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/architecture_body.hpp>
#include <eda/vhdl93/ast/package_body.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct secondary_unit : x3::variant<
    ast::nullary,
    ast::architecture_body,
    ast::package_body
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SECONDARY_UNIT_HPP_ */
