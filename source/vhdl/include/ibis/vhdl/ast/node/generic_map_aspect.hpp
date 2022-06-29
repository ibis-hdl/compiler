//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/association_list.hpp>

namespace ibis::vhdl::ast {

struct generic_map_aspect : position_tagged {
    ast::association_list association_list;
};

}  // namespace ibis::vhdl::ast
