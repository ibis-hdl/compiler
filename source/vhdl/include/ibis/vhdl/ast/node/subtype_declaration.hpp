//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>

#include <boost/range/iterator_range.hpp>

namespace ibis::vhdl::ast {

struct subtype_declaration : position_tagged {
    ast::identifier identifier;
    ast::subtype_indication subtype_indication;
};

}  // namespace ibis::vhdl::ast
