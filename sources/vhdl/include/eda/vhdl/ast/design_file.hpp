/*
 * design_file.hpp
 *
 *  Created on: 21.06.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGN_FILE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGN_FILE_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/design_unit.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct design_file : std::vector<ast::design_unit> { };


} } } // namespace eda.vhdl.ast


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_DESIGN_FILE_HPP_ */
