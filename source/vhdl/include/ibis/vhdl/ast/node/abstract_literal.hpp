//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/decimal_literal.hpp>
#include <ibis/vhdl/ast/node/based_literal.hpp>

namespace ibis::vhdl::ast {

struct abstract_literal : variant<nullary, decimal_literal, based_literal> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
