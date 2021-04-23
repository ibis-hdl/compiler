#pragma once

#include <ibis/vhdl/ast/node/design_unit.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct design_file : std::vector<ast::design_unit> {
};

}  // namespace ibis::vhdl::ast
