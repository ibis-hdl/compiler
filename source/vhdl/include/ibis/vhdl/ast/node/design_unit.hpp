//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/context_clause.hpp>
#include <ibis/vhdl/ast/node/library_unit.hpp>

namespace ibis::vhdl::ast {

struct design_unit : position_tagged {
    ast::context_clause context_clause;
    ast::library_unit library_unit;
};

}  // namespace ibis::vhdl::ast
