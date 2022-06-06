//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/node/association_element.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct association_list : std::vector<ast::association_element> {};

}  // namespace ibis::vhdl::ast
