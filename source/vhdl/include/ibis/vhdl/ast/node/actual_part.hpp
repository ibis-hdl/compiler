//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/actual_designator.hpp>

namespace ibis::vhdl::ast {

struct name;

struct actual_part_chunk {
    forward_ast<ast::name> context_tied_name;  // function_name | type_mark(name)
    ast::actual_designator actual_designator;
};

using actual_part = variant<actual_designator, actual_part_chunk>;

}  // namespace ibis::vhdl::ast
