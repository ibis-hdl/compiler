/*
 * design_file.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_FILE_HPP_
#define SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_FILE_HPP_


#include <eda/vhdl93/ast/util/namespace_alias.hpp>
#include <eda/vhdl93/ast/util/position_tagged.hpp>

#include <eda/vhdl93/ast/design_unit.hpp>
#include <vector>


namespace eda { namespace vhdl93 { namespace ast {


struct design_file : std::vector<ast::design_unit> { };


} } } // namespace eda.vhdl93.ast


#endif /* SOURCES_VHDL93_INCLUDE_EDA_VHDL93_AST_DESIGN_FILE_HPP_ */
