//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/node/interface_declaration.hpp>
#include <vector>

namespace ibis::vhdl::ast {

// only used in context of interface_list
using interface_element = ast::interface_declaration;

struct interface_list : std::vector<ast::interface_element> {};

}  // namespace ibis::vhdl::ast
