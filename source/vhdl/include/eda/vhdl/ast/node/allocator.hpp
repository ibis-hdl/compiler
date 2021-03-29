#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/subtype_indication.hpp>
#include <eda/vhdl/ast/node/qualified_expression.hpp>

namespace eda::vhdl::ast {

struct allocator : variant<ast::nullary, ast::subtype_indication, ast::qualified_expression> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
