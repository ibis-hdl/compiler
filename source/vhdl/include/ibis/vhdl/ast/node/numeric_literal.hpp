//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/abstract_literal.hpp>
#include <ibis/vhdl/ast/node/physical_literal.hpp>

namespace ibis::vhdl::ast {

struct numeric_literal : variant<nullary, abstract_literal, physical_literal> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
