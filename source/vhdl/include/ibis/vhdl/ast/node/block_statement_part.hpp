//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <vector>

namespace ibis::vhdl::ast {

struct concurrent_statement;  // forward due to cyclic dependency

///
/// Ast node cyclic dependency as:
///
/// \dot
/// digraph concurrent_statement  {
///  concurrent_statement -> block_statement;
///  block_statement      -> block_statement_part;
///  block_statement_part -> concurrent_statement [label=<<i>forward</i>>];
/// }
/// \enddot
///
struct block_statement_part : std::vector<ast::concurrent_statement> {};

}  // namespace ibis::vhdl::ast
