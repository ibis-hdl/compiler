//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/instantiated_unit.hpp>
#include <ibis/vhdl/ast/node/generic_map_aspect.hpp>
#include <ibis/vhdl/ast/node/port_map_aspect.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct component_instantiation_statement : position_tagged {
    optional<ast::label> label;
    ast::instantiated_unit instantiated_unit;
    optional<ast::generic_map_aspect> generic_map_aspect;
    optional<ast::port_map_aspect> port_map_aspect;
};

}  // namespace ibis::vhdl::ast
