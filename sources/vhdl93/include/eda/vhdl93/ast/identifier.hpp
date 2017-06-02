/*
 * identifier.hpp
 *
 *  Created on: 22.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <string_view>


namespace eda { namespace vhdl93 { namespace ast {


struct identifier : position_tagged
{
    identifier() = default;

    identifier(std::string_view&& sv) : name{ std::move(sv) }
    { }

    identifier& operator=(std::string_view&& sv)
    {
        name = std::move(sv);
        return *this;
    }

    std::string_view            name;
};


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_IDENTIFIER_HPP_ */
