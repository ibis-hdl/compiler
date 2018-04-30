/*
 * library_unit.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LIBRARY_UNIT_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_LIBRARY_UNIT_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/primary_unit.hpp>
#include <eda/vhdl/ast/secondary_unit.hpp>


namespace eda { namespace vhdl { namespace ast {


struct library_unit : variant<
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
