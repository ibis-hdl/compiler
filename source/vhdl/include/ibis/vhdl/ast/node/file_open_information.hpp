//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using file_logical_name = expression;  // string expression

struct file_open_information : position_tagged {
    optional<ast::expression> file_open_kind_expression;
    ast::file_logical_name file_logical_name;  // type: string_expression
};

}  // namespace ibis::vhdl::ast
