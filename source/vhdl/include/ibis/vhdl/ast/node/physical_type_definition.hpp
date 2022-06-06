//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/primary_unit_declaration.hpp>
#include <ibis/vhdl/ast/node/range_constraint.hpp>
#include <ibis/vhdl/ast/node/secondary_unit_declaration.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct physical_type_definition : position_tagged {
    ast::range_constraint range_constraint;
    ast::primary_unit_declaration primary_unit_declaration;
    std::vector<ast::secondary_unit_declaration> secondary_unit_declarations;
    optional<ast::simple_name> physical_type_simple_name;
};

}  // namespace ibis::vhdl::ast
