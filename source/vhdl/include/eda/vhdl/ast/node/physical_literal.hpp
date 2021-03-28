/*
 * physical_literal.hpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_LITERAL_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_LITERAL_HPP_


#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/abstract_literal.hpp>
#include <eda/vhdl/ast/util/string_span.hpp>


namespace eda { namespace vhdl { namespace ast {


struct physical_literal : position_tagged
{
    abstract_literal                                literal;
    ast::string_span                                unit_name;
};


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PHYSICAL_LITERAL_HPP_ */
