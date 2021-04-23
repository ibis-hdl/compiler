#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/discrete_range.hpp>
#include <ibis/vhdl/ast/node/prefix.hpp>

namespace ibis::vhdl::ast {

struct slice_name : position_tagged {
    ast::prefix prefix;
    ast::discrete_range discrete_range;
};

}  // namespace ibis::vhdl::ast
