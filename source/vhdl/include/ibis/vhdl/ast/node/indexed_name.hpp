#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/prefix.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct indexed_name : position_tagged {
    ast::prefix prefix;
    std::vector<expression> expression_list;
};

}  // namespace ibis::vhdl::ast
