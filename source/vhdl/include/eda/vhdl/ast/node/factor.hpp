#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/primary.hpp>

namespace eda::vhdl::ast {

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

}  // namespace eda::vhdl::ast
