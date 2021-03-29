#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/guarded_signal_specification.hpp>
#include <eda/vhdl/ast/node/expression.hpp>

namespace eda::vhdl::ast {

struct disconnection_specification : position_tagged {
    ast::guarded_signal_specification guarded_signal_specification;
    ast::expression time_expression;
};

}  // namespace eda::vhdl::ast
