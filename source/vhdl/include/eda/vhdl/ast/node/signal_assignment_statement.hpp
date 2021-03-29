#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/delay_mechanism.hpp>
#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/target.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <eda/vhdl/ast/node/waveform.hpp>

namespace eda::vhdl::ast {

struct signal_assignment_statement : position_tagged {
    optional<ast::label> label;
    ast::target target;
    optional<ast::delay_mechanism> delay_mechanism;
    ast::waveform waveform;
};

}  // namespace eda::vhdl::ast
