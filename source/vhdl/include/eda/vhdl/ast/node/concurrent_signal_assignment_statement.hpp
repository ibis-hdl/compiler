#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/conditional_signal_assignment.hpp>
#include <eda/vhdl/ast/node/selected_signal_assignment.hpp>

namespace eda::vhdl::ast {

struct concurrent_signal_assignment_statement : position_tagged {
    optional<ast::label> label;
    bool postponed;
    variant<                                 // --
        ast::conditional_signal_assignment,  // --
        ast::selected_signal_assignment      // --
        >
        signal_assignment;

    concurrent_signal_assignment_statement()
        : postponed{}
    {
    }
};

}  // namespace eda::vhdl::ast
