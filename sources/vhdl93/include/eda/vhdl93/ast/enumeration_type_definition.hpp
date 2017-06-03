/*
 * enumeration_type_definition.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_


#include <eda/vhdl93/ast/namespace_alias.hpp>
#include <eda/vhdl93/ast/position_tagged.hpp>

#include <eda/vhdl93/ast/enumeration_literal.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct enumeration_type_definition : std::vector<enumeration_literal> { };


} } } // namespace eda.vhdl93.ast



#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_ENUMERATION_TYPE_DEFINITION_HPP_ */
