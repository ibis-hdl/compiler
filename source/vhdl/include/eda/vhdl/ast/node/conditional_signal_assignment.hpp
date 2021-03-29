#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/target.hpp>
#include <eda/vhdl/ast/node/options.hpp>
#include <eda/vhdl/ast/node/conditional_waveforms.hpp>

namespace eda::vhdl::ast {

struct conditional_signal_assignment : position_tagged {
    ast::target target;
    ast::options options;
    ast::conditional_waveforms conditional_waveforms;
};

}  // namespace eda::vhdl::ast
