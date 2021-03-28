/*
 * prefix.hpp
 *
 *  Created on: 09.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PREFIX_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PREFIX_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/function_call.hpp>


namespace eda { namespace vhdl { namespace ast {


struct name;


struct prefix : variant<
    nullary,
    forward_ast<name>,
    function_call
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PREFIX_HPP_ */
