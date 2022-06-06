//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct instantiated_unit_component {
    ast::name name;
};

struct instantiated_unit_entity {
    ast::name name;
    optional<ast::identifier> architecture_identifier;
};

struct instantiated_unit_configuration {
    ast::name name;
};

struct instantiated_unit
    : variant<ast::nullary, ast::instantiated_unit_component, ast::instantiated_unit_entity,
              ast::instantiated_unit_configuration> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
