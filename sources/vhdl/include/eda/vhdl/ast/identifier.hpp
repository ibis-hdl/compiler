/*
 * identifier.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <string_view>


namespace eda { namespace vhdl { namespace ast {


struct identifier : position_tagged
{
    std::string_view                name;

    identifier() = default;

    identifier(std::string_view&& sv)
    : name{ std::move(sv) }
    { }
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_IDENTIFIER_HPP_ */
