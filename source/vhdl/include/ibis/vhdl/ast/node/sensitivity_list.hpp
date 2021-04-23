#pragma once

#include <ibis/vhdl/ast/node/name.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct sensitivity_list : std::vector<ast::name> {
};

}  // namespace ibis::vhdl::ast
