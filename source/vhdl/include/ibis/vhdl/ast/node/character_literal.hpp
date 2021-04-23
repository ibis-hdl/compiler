#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

namespace ibis::vhdl::ast {

struct character_literal : position_tagged {
    char literal;
};

}  // namespace ibis::vhdl::ast
