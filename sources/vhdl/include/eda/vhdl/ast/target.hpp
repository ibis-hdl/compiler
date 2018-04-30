/*
 * target.hpp
 *
 *  Created on: 18.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TARGET_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TARGET_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/aggregate.hpp>
#include <eda/vhdl/ast/name.hpp>


namespace eda { namespace vhdl { namespace ast {


struct target : variant<
    nullary,
    name,
    aggregate
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_TARGET_HPP_ */
