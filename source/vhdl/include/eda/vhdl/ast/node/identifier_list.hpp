#pragma once

#include <eda/vhdl/ast/node/identifier.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct identifier_list : std::vector<ast::identifier> {
};

}  // namespace eda::vhdl::ast
