#pragma once

#include <eda/vhdl/ast/node/design_unit.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct design_file : std::vector<ast::design_unit> {
};

}  // namespace eda::vhdl::ast
