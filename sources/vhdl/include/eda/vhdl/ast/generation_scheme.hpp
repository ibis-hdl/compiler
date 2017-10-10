/*
 * generation_scheme.hpp
 *
 *  Created on: 20.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERATION_SCHEME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERATION_SCHEME_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/parameter_specification.hpp>
#include <eda/vhdl/ast/condition.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl { namespace ast {


struct generation_scheme : x3::variant<
    ast::nullary,
    ast::parameter_specification,
    ast::condition
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_GENERATION_SCHEME_HPP_ */