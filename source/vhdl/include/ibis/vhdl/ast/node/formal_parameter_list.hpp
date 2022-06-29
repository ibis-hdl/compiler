//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/node/interface_list.hpp>

namespace ibis::vhdl::ast {

// formal_parameter_list ::= parameter_interface_list
using formal_parameter_list = interface_list;

}  // namespace ibis::vhdl::ast
