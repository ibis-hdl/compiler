//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/selected_name.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using logical_name = ast::identifier;
using logical_name_list = std::vector<logical_name>;

struct library_clause : position_tagged {
    ast::logical_name_list logical_name_list;
};

}  // namespace ibis::vhdl::ast
