/*
 * abstract_literal.hpp
 *
 *  Created on: 16.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ABSTRACT_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ABSTRACT_LITERAL_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/decimal_literal.hpp>
#include <eda/vhdl/ast/node/based_literal.hpp>


namespace eda { namespace vhdl { namespace ast {


struct abstract_literal : variant<
    nullary,
    decimal_literal,
    based_literal
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ABSTRACT_LITERAL_HPP_ */
