#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/waveform.hpp>
#include <eda/vhdl/ast/node/choices.hpp>
#include <vector>

namespace eda::vhdl::ast {

// Non-BNF, artificial element for selected_waveforms
struct selected_waveform : position_tagged {
    ast::waveform waveform;
    ast::choices choices;
};

struct selected_waveforms : std::vector<selected_waveform> {
};

}  // namespace eda::vhdl::ast
