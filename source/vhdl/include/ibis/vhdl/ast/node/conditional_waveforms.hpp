#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <ibis/vhdl/ast/node/waveform.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct conditional_waveforms : position_tagged {
    struct chunk {
        ast::waveform waveform;
        ast::expression condition;
    };

    std::vector<chunk> chunks;
    ast::waveform waveform;
    optional<ast::expression> condition;
};

}  // namespace ibis::vhdl::ast
