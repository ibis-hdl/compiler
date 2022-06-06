//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/node/concurrent_statement.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct architecture_statement_part : std::vector<ast::concurrent_statement> {};

}  // namespace ibis::vhdl::ast
