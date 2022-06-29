//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct identifier_list : std::vector<ast::identifier> {};

}  // namespace ibis::vhdl::ast
