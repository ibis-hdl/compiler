//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/node/discrete_range.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct index_constraint : std::vector<ast::discrete_range> {};

}  // namespace ibis::vhdl::ast
