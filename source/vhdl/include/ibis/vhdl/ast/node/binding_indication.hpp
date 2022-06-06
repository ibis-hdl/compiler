//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/entity_aspect.hpp>
#include <ibis/vhdl/ast/node/generic_map_aspect.hpp>
#include <ibis/vhdl/ast/node/port_map_aspect.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct binding_indication : position_tagged {
    optional<ast::entity_aspect> entity_aspect;
    ast::generic_map_aspect generic_map_aspect;
    ast::port_map_aspect port_map_aspect;
};

}  // namespace ibis::vhdl::ast
