//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/node/sequential_statement.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct sequence_of_statements : std::vector<ast::sequential_statement> {};

}  // namespace ibis::vhdl::ast
