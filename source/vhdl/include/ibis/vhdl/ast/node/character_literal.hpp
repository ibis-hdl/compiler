//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

namespace ibis::vhdl::ast {

struct character_literal : position_tagged {
    char literal;
};

}  // namespace ibis::vhdl::ast
