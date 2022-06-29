//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string_view>

namespace ibis::vhdl::ast {

///
/// lookup an AST node name for a more readable name to use with error message
/// construction.
///
/// @param which AST node name.
/// @return Beautified name of the rule if found, otherwise the original
///        string. Also, on success true is returned, otherwise false.
///
std::string_view pretty_node_name(std::string_view which);

}  // namespace ibis::vhdl::ast
