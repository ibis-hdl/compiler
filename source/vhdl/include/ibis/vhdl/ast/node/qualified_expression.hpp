//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/aggregate.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct qualified_expression : position_tagged {
    ast::name type_mark;
    variant<ast::nullary, ast::expression, ast::aggregate> aggregate_or_expression;
};

}  // namespace ibis::vhdl::ast
