#pragma once

#include <eda/vhdl/ast/node/sequential_statement.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct sequence_of_statements : std::vector<ast::sequential_statement> {
};

}  // namespace eda::vhdl::ast
