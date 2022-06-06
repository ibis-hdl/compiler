//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/literal.hpp>

#include <vector>

namespace ibis::vhdl::ast {

struct name;
struct expression;
struct function_call;
struct qualified_expression;
struct allocator;

struct element_association;
using aggregate = std::vector<ast::element_association>;

// primary ::=
//      name
//    | literal
//    | aggregate
//    | function_call
//    | qualified_expression
//    | type_conversion
//    | allocator
//    | ( expression )
struct primary
    : variant<nullary, forward_ast<name>, literal, forward_ast<aggregate>,
              forward_ast<function_call>, forward_ast<qualified_expression>,
              // type_conversion,
              forward_ast<allocator>, forward_ast<expression> > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
