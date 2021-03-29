#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/operator_symbol.hpp>

namespace eda::vhdl::ast {

struct designator : variant<ast::nullary, ast::identifier, ast::operator_symbol> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
