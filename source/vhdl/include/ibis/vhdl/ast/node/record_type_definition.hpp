//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/element_declaration.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct record_type_definition : position_tagged {
    std::vector<ast::element_declaration> element_declarations;
    optional<ast::simple_name> name;
};

}  // namespace ibis::vhdl::ast
