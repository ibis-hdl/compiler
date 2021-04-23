#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/identifier.hpp>
#include <ibis/vhdl/ast/node/operator_symbol.hpp>

namespace ibis::vhdl::ast {

struct designator : variant<ast::nullary, ast::identifier, ast::operator_symbol> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
