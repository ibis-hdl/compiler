//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/primary_unit.hpp>
#include <ibis/vhdl/ast/node/secondary_unit.hpp>

namespace ibis::vhdl::ast {

using library_unit = variant<ast::nullary, ast::primary_unit, ast::secondary_unit>;

}
