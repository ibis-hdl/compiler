#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/node/waveform.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct conditional_waveforms : position_tagged {
    struct chunk {
        ast::waveform waveform;
        ast::expression condition;
    };

    std::vector<chunk> chunks;
    ast::waveform waveform;
    optional<ast::expression> condition;
};

}  // namespace eda::vhdl::ast
