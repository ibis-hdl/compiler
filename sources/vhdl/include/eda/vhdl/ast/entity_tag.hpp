/*
 * entity_tag.hpp
 *
 *  Created on: 16.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_TAG_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_TAG_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/simple_name.hpp>
#include <eda/vhdl/ast/character_literal.hpp>
#include <eda/vhdl/ast/operator_symbol.hpp>


namespace eda { namespace vhdl { namespace ast {


using entity_tag = variant<
    nullary,
    simple_name,
    character_literal,
    operator_symbol
>;


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENTITY_TAG_HPP_ */
