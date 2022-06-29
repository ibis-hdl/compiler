//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/prefix.hpp>
#include <ibis/vhdl/ast/node/suffix.hpp>

namespace ibis::vhdl::ast {

struct selected_name : position_tagged {
    ast::prefix prefix;
    ast::suffix suffix;
};

}  // namespace ibis::vhdl::ast
