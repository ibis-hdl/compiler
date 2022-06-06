//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/physical_literal.hpp>

namespace ibis::vhdl::ast {

struct secondary_unit_declaration : position_tagged {
    ast::identifier identifier;
    ast::physical_literal physical_literal;
};

}  // namespace ibis::vhdl::ast
