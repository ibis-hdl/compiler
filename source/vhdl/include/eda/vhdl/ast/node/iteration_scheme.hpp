/*
 * iteration_scheme.hpp
 *
 *  Created on: 19.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ITERATION_SCHEME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ITERATION_SCHEME_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/condition.hpp>
#include <eda/vhdl/ast/node/parameter_specification.hpp>


namespace eda { namespace vhdl { namespace ast {


struct iteration_scheme : variant<
    ast::nullary,
    ast::condition,
    ast::parameter_specification
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ITERATION_SCHEME_HPP_ */
