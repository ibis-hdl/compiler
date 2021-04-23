#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/guarded_signal_specification.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>

namespace ibis::vhdl::ast {

struct disconnection_specification : position_tagged {
    ast::guarded_signal_specification guarded_signal_specification;
    ast::expression time_expression;
};

}  // namespace ibis::vhdl::ast
