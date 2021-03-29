#pragma once

#include <eda/vhdl/ast/node/concurrent_statement.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct architecture_statement_part : std::vector<ast::concurrent_statement> {
};

}  // namespace eda::vhdl::ast
