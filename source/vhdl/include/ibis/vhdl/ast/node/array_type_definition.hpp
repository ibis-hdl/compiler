//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/unconstrained_array_definition.hpp>
#include <ibis/vhdl/ast/node/constrained_array_definition.hpp>

namespace ibis::vhdl::ast {

struct array_type_definition
    : variant<ast::nullary, ast::unconstrained_array_definition,
              ast::constrained_array_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
