#pragma once

#include <eda/vhdl/ast/node/name.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct sensitivity_list : std::vector<ast::name> {
};

}  // namespace eda::vhdl::ast
