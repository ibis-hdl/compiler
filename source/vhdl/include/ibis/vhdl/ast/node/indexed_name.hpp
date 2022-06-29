//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/prefix.hpp>
#include <ibis/vhdl/ast/node/expression.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct indexed_name : position_tagged {
    ast::prefix prefix;
    std::vector<expression> expression_list;
};

}  // namespace ibis::vhdl::ast
