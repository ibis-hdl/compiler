#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <vector>

namespace ibis::vhdl::ast {

struct name;

struct formal_part : position_tagged {
    std::vector<ast::name> context_tied_names;
};

}  // namespace ibis::vhdl::ast
