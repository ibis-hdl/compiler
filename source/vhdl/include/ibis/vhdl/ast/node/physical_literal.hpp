//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/abstract_literal.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct physical_literal : position_tagged {
    abstract_literal literal;
    ast::string_span unit_name;
};

}  // namespace ibis::vhdl::ast
