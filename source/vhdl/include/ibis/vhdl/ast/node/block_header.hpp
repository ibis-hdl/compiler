//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/generic_clause.hpp>
#include <ibis/vhdl/ast/node/generic_map_aspect.hpp>
#include <ibis/vhdl/ast/node/port_clause.hpp>
#include <ibis/vhdl/ast/node/port_map_aspect.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct block_header : position_tagged {
    struct generic_part_chunk {
        ast::generic_clause generic_clause;
        optional<ast::generic_map_aspect> generic_map_aspect;
    };

    struct port_part_chunk {
        ast::port_clause port_clause;
        optional<ast::port_map_aspect> port_map_aspect;
    };

    optional<generic_part_chunk> generic_part;
    optional<port_part_chunk> port_part;
};

}  // namespace ibis::vhdl::ast
