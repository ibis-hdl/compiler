#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/abstract_literal.hpp>
#include <eda/vhdl/ast/node/physical_literal.hpp>

namespace eda::vhdl::ast {

struct numeric_literal : variant<nullary, abstract_literal, physical_literal> {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace eda::vhdl::ast
