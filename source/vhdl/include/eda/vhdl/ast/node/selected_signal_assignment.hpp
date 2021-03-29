#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/node/target.hpp>
#include <eda/vhdl/ast/node/options.hpp>
#include <eda/vhdl/ast/node/selected_waveforms.hpp>

namespace eda::vhdl::ast {

struct selected_signal_assignment : position_tagged {
    ast::expression expression;
    ast::target target;
    ast::options options;
    ast::selected_waveforms selected_waveforms;
};

}  // namespace eda::vhdl::ast
