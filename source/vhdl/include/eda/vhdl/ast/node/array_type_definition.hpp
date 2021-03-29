#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/unconstrained_array_definition.hpp>
#include <eda/vhdl/ast/node/constrained_array_definition.hpp>

namespace eda::vhdl::ast {

struct array_type_definition
    : variant<ast::nullary, ast::unconstrained_array_definition,
              ast::constrained_array_definition> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
