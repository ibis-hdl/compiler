#pragma once

#include <eda/vhdl/ast/node/discrete_range.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct index_constraint : std::vector<ast::discrete_range> {
};

}  // namespace eda::vhdl::ast
