#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/literal.hpp>

namespace ibis::vhdl::ast {

struct name;
struct aggregate;
struct expression;
struct function_call;
struct qualified_expression;
struct allocator;

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
