/*
 * designator.hpp
 *
 *  Created on: 09.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGNATOR_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGNATOR_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/identifier.hpp>
#include <eda/vhdl/ast/operator_symbol.hpp>


namespace eda { namespace vhdl { namespace ast {


struct designator : variant<
    ast::nullary,
    ast::identifier,
    ast::operator_symbol
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGNATOR_HPP_ */
