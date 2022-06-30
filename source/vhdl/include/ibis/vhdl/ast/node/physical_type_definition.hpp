//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/physical_literal.hpp>

#include <ibis/vhdl/ast/node/range_constraint.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using primary_unit_declaration = ast::identifier;

struct secondary_unit_declaration : position_tagged {
    ast::identifier identifier;
    ast::physical_literal physical_literal;
};

struct physical_type_definition : position_tagged {
    ast::range_constraint range_constraint;
    ast::primary_unit_declaration primary_unit_declaration;
    std::vector<ast::secondary_unit_declaration> secondary_unit_declarations;
    optional<ast::simple_name> physical_type_simple_name;
};

}  // namespace ibis::vhdl::ast
