//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/designator.hpp>
#include <ibis/vhdl/ast/node/formal_parameter_list.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <ibis/vhdl/ast/node/name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct subprogram_specification_procedure : position_tagged {
    ast::designator designator;
    optional<ast::formal_parameter_list> formal_parameter_list;
};

struct subprogram_specification_function : position_tagged {
    // LRM93 2.1
    // A function is impure if its specification contains the
    // reserved word IMPURE; otherwise it is said to be pure.
    bool impure;
    ast::designator designator;
    optional<ast::formal_parameter_list> formal_parameter_list;
    ast::name return_type_mark;

    subprogram_specification_function()
        : impure{}
    {
    }
};

struct subprogram_specification
    : variant<ast::subprogram_specification_procedure, ast::subprogram_specification_function> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
