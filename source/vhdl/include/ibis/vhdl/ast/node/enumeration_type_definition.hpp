//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/node/enumeration_literal.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct enumeration_type_definition : std::vector<enumeration_literal> {};

}  // namespace ibis::vhdl::ast
