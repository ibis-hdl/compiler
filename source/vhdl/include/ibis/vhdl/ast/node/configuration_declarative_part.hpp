//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/use_clause.hpp>
#include <ibis/vhdl/ast/node/attribute_specification.hpp>
#include <ibis/vhdl/ast/node/group_declaration.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using configuration_declarative_item =     // --
    variant<ast::nullary,                  // --
            ast::use_clause,               // --
            ast::attribute_specification,  // --
            ast::group_declaration         // --
            >;
using configuration_declarative_part = std::vector<ast::configuration_declarative_item>;

}  // namespace ibis::vhdl::ast
