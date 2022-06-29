//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/enumeration_type_definition.hpp>
#include <ibis/vhdl/ast/node/range_constraint.hpp>
#include <ibis/vhdl/ast/node/physical_type_definition.hpp>

namespace ibis::vhdl::ast {

struct scalar_type_definition
    : variant<ast::nullary, ast::enumeration_type_definition,
              ast::range_constraint,  // {integer,floating}_type_definition
              ast::physical_type_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
