/*
 * enumeration_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_LITERAL_HPP_


#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/character_literal.hpp>
#include <eda/vhdl/ast/identifier.hpp>


namespace eda { namespace vhdl { namespace ast {


struct enumeration_literal : variant<
    nullary,
    identifier,
    character_literal
>
{
    using base_type::base_type;
    using base_type::operator=;
};


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_LITERAL_HPP_ */
