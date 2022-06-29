//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/instantiation_list.hpp>
#include <ibis/vhdl/ast/node/name.hpp>

namespace ibis::vhdl::ast {

struct component_specification : position_tagged {
    ast::instantiation_list instantiation_list;
    ast::name component_name;
};

}  // namespace ibis::vhdl::ast
