//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/simple_expression.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct shift_expression : position_tagged {
    struct chunk {
        operator_token shift_operator;
        ast::simple_expression simple_expression;
    };

    ast::simple_expression simple_expression;
    optional<chunk> rest;
};

}  // namespace ibis::vhdl::ast
