/*
 * iteration_scheme.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ITERATION_SCHEME_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ITERATION_SCHEME_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/util/nullary.hpp>
#include <eda/vhdl93/ast/condition.hpp>
#include <eda/vhdl93/ast/parameter_specification.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct iteration_scheme : x3::variant<
    ast::nullary,
    ast::condition,
    ast::parameter_specification
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ITERATION_SCHEME_HPP_ */
