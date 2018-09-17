/*
 * pretty_node_name.hpp
 *
 *  Created on: 17.09.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRETTY_NODE_NAME_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRETTY_NODE_NAME_HPP_

#include <string_view>

namespace eda {
namespace vhdl {
namespace ast {

/**
 * lookup a AST node name for a useful name to use with error message
 * construction.
 *
 * @param which AST node name.
 * @return Beautified name of the rule.
 */
std::string_view pretty_node_name(std::string_view which);

} // namespace ast
} // namespace vhdl
} // namespace eda



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_PRETTY_NODE_NAME_HPP_ */
