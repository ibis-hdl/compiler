//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/primary.hpp>

namespace ibis::vhdl::ast {

struct factor_binary_operation : position_tagged {
    ast::primary primary_lhs;
    operator_token operator_;
    ast::primary primary_rhs;
};

struct factor_unary_operation : position_tagged {
    operator_token operator_;
    ast::primary primary;
};

// factor ::=
//     primary [ ** primary ]
//     | ABS primary
//     | NOT primary
struct factor : variant<nullary, primary, factor_binary_operation, factor_unary_operation> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
