/*
 * sensitivity_list.hpp
 *
 *  Created on: 13.05.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_LIST_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_LIST_HPP_


#include <eda/vhdl/ast/node/name.hpp>
#include <vector>


namespace eda { namespace vhdl { namespace ast {


struct sensitivity_list : std::vector<ast::name> { };


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_SENSITIVITY_LIST_HPP_ */
