#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/target.hpp>
#include <ibis/vhdl/ast/node/options.hpp>
#include <ibis/vhdl/ast/node/selected_waveforms.hpp>

namespace ibis::vhdl::ast {

struct selected_signal_assignment : position_tagged {
    ast::expression expression;
    ast::target target;
    ast::options options;
    ast::selected_waveforms selected_waveforms;
};

}  // namespace ibis::vhdl::ast
