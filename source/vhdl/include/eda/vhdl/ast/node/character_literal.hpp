#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

namespace eda::vhdl::ast {

struct character_literal : position_tagged {
    char literal;
};

}  // namespace eda::vhdl::ast
