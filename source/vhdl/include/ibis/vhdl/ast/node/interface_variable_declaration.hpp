//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/identifier_list.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/subtype_indication.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct interface_variable_declaration : position_tagged {
    bool VARIABLE;
    ast::identifier_list identifier_list;
    optional<ast::keyword_token> mode;
    ast::subtype_indication subtype_indication;
    optional<ast::expression> static_expression;

    interface_variable_declaration()
        : VARIABLE{}
    {
    }
};

}  // namespace ibis::vhdl::ast
