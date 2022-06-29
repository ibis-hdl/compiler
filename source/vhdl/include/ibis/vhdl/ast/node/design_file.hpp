//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/node/design_unit.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using design_file = std::vector<ast::design_unit>;

}  // namespace ibis::vhdl::ast
