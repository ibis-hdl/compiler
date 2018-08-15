/*
 * secondary_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SECONDARY_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SECONDARY_UNIT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/architecture_body.hpp>
#include <eda/vhdl/ast/node/package_body.hpp>


namespace eda { namespace vhdl { namespace ast {


struct secondary_unit : variant<
    ast::nullary,
    ast::architecture_body,
    ast::package_body
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SECONDARY_UNIT_HPP_ */
