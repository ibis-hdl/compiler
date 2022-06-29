//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct index_subtype_definition : position_tagged {
    ast::name type_mark;
};

}  // namespace ibis::vhdl::ast
