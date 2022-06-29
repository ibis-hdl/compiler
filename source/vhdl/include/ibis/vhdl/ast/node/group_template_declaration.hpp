//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/entity_class_entry_list.hpp>

namespace ibis::vhdl::ast {

struct group_template_declaration : position_tagged {
    ast::identifier identifier;
    ast::entity_class_entry_list entity_class_entry_list;
};

}  // namespace ibis::vhdl::ast
