/*
 * physical_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_LITERAL_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/abstract_literal.hpp>

#include <string_view>


namespace eda { namespace vhdl { namespace ast {


struct physical_literal : position_tagged
{
    abstract_literal                literal;
    std::string_view                unit_name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_LITERAL_HPP_ */
