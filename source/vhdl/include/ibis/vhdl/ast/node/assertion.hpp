//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/condition.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct assertion : position_tagged {
    ast::condition condition;
    optional<ast::expression> report;
    optional<ast::expression> severity;
};

}  // namespace ibis::vhdl::ast
