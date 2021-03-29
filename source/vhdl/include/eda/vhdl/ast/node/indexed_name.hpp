#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/prefix.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct indexed_name : position_tagged {
    ast::prefix prefix;
    std::vector<expression> expression_list;
};

}  // namespace eda::vhdl::ast
