#pragma once

#include <string_view>
#include <tuple>

namespace eda::vhdl::ast {

/**
 * lookup an AST node name for a useful name to use with error message
 * construction.
 *
 * @param which AST node name.
 * @return Beautified name of the rule if found, otherwise the original
 *         string. Also, on success true is returned, otherwise false.
 */
std::tuple<bool, std::string_view> pretty_node_name(std::string_view which);

}  // namespace eda::vhdl::ast
