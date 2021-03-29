#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <vector>

namespace eda::vhdl::ast {

struct name;

struct formal_part : position_tagged {
    std::vector<ast::name> context_tied_names;
};

}  // namespace eda::vhdl::ast
