//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/condition_clause.hpp>
#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/sensitivity_clause.hpp>
#include <ibis/vhdl/ast/node/timeout_clause.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct wait_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::sensitivity_clause> sensitivity_clause;
    optional<ast::condition_clause> condition_clause;
    optional<ast::timeout_clause> timeout_clause;
};

}  // namespace ibis::vhdl::ast
