#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/range.hpp>

namespace eda::vhdl::ast {

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

}  // namespace eda::vhdl::ast
