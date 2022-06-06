//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/expression.hpp>
#include <ibis/vhdl/ast/node/prefix.hpp>
#include <ibis/vhdl/ast/node/signature.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct attribute_name : position_tagged {
    ast::prefix prefix;
    optional<ast::signature> signature;
    ast::simple_name attribute_designator;
    optional<ast::expression> expression;
};

}  // namespace ibis::vhdl::ast
