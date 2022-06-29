//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <ibis/vhdl/ast/node/qualified_expression.hpp>

namespace ibis::vhdl::ast {

struct allocator : variant<ast::nullary, ast::subtype_indication, ast::qualified_expression> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
