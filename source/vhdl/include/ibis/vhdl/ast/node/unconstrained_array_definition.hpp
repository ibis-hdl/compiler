//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/index_subtype_definition.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct unconstrained_array_definition : position_tagged {
    std::vector<ast::index_subtype_definition> index_subtype_definitions;
    ast::subtype_indication element_subtype_indication;
};

}  // namespace ibis::vhdl::ast
