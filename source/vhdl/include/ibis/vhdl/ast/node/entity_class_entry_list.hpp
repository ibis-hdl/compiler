//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct entity_class_entry_list : std::vector<ast::keyword_token> {};

}  // namespace ibis::vhdl::ast
