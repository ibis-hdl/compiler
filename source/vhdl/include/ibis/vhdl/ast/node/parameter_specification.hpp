#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/discrete_range.hpp>

namespace ibis::vhdl::ast {

struct parameter_specification : position_tagged {
    ast::identifier identifier;
    ast::discrete_range discrete_range;
};

}  // namespace ibis::vhdl::ast
