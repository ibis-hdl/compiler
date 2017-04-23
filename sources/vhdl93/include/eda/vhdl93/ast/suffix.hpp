/*
 * suffix.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>

#include <eda/vhdl93/ast/nullary.hpp>
#include <eda/vhdl93/ast/keyword_token.hpp>
#include <eda/vhdl93/ast/character_literal.hpp>
#include <eda/vhdl93/ast/operator_symbol.hpp>
#include <eda/vhdl93/ast/simple_name.hpp>

#include <boost/spirit/home/x3/support/ast/variant.hpp>


namespace eda { namespace vhdl93 { namespace ast {


struct suffix :
    x3::variant<
        nullary,
        simple_name,
        character_literal,
        // operator_symbol,
        keyword_token
    >
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_SUFFIX_HPP_ */
