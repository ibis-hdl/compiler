//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/conditional_signal_assignment.hpp>
#include <ibis/vhdl/ast/node/selected_signal_assignment.hpp>

namespace ibis::vhdl::ast {

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

}  // namespace ibis::vhdl::ast
