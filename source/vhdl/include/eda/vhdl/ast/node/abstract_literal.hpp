#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/decimal_literal.hpp>
#include <eda/vhdl/ast/node/based_literal.hpp>

namespace eda::vhdl::ast {

struct abstract_literal : variant<nullary, decimal_literal, based_literal> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
