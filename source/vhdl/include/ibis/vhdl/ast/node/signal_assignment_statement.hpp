#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/delay_mechanism.hpp>
#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/target.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <ibis/vhdl/ast/node/waveform.hpp>

namespace ibis::vhdl::ast {

struct signal_assignment_statement : position_tagged {
    optional<ast::label> label;
    ast::target target;
    optional<ast::delay_mechanism> delay_mechanism;
    ast::waveform waveform;
};

}  // namespace ibis::vhdl::ast
