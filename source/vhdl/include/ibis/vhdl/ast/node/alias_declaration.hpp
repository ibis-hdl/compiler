//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/alias_designator.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/node/signature.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct alias_declaration : position_tagged {
    ast::alias_designator alias_designator;
    optional<ast::subtype_indication> subtype_indication;
    ast::name name;
    optional<ast::signature> signature;
};

}  // namespace ibis::vhdl::ast
