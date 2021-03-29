#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/selected_name.hpp>
#include <vector>

namespace eda::vhdl::ast {

using logical_name = ast::identifier;

struct library_clause : position_tagged {
    std::vector<logical_name> logical_name_list;
};

}  // namespace eda::vhdl::ast
