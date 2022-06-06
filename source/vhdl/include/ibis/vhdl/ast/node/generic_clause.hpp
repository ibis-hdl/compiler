//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/interface_list.hpp>

namespace ibis::vhdl::ast {

struct generic_clause : position_tagged {
    ast::interface_list generic_list;
};

}  // namespace ibis::vhdl::ast
