//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/range.hpp>

namespace ibis::vhdl::ast {

struct subtype_indication;

///
/// Ast node cyclic dependency as:
///
/// \dot
/// digraph concurrent_statement  {
///  subtype_indication -> constraint;
///  constraint -> index_constraint -> discrete_range;
///  discrete_range -> subtype_indication [ label=<<i>forward</i>>];
/// }
/// \enddot
///
struct discrete_range
    : variant<ast::nullary,
              forward_ast<ast::subtype_indication>,  // discrete_subtype_indication
              ast::range> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
