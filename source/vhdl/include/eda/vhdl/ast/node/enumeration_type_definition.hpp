/*
 * enumeration_type_definition.hpp
 *
 *  Created on: 02.04.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_TYPE_DEFINITION_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_TYPE_DEFINITION_HPP_


#include <eda/vhdl/ast/node/enumeration_literal.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct enumeration_type_definition : std::vector<enumeration_literal> { };


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_ENUMERATION_TYPE_DEFINITION_HPP_ */
