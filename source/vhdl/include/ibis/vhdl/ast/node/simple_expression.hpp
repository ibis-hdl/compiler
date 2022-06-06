//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/term.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct simple_expression : position_tagged {
    struct chunk {
        operator_token adding_operator;
        ast::term term;
    };

    optional<operator_token> sign;
    ast::term term;
    std::vector<chunk> rest_list;
};

}  // namespace ibis::vhdl::ast
