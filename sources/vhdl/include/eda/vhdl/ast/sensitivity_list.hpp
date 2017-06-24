/*
 * sensitivity_list.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_LIST_HPP_


#include <eda/vhdl/ast/util/namespace_alias.hpp>
#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/name.hpp>
#include <vector>

namespace eda { namespace vhdl { namespace ast {


struct sensitivity_list : std::vector<ast::name> { };


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_LIST_HPP_ */
