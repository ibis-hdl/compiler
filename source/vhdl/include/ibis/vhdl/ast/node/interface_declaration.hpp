//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/interface_constant_declaration.hpp>
#include <ibis/vhdl/ast/node/interface_file_declaration.hpp>
#include <ibis/vhdl/ast/node/interface_signal_declaration.hpp>
#include <ibis/vhdl/ast/node/interface_variable_declaration.hpp>

namespace ibis::vhdl::ast {

using interface_declaration =
    variant<nullary, interface_constant_declaration, interface_signal_declaration,
            interface_variable_declaration, interface_file_declaration>;

}
