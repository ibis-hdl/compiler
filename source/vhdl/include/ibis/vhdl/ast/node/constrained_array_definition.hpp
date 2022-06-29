//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/index_constraint.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>

namespace ibis::vhdl::ast {

struct constrained_array_definition : position_tagged {
    ast::index_constraint index_constraint;
    ast::subtype_indication element_subtype_indication;
};

}  // namespace ibis::vhdl::ast
