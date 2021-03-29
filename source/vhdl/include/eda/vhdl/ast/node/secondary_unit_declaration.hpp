#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/identifier.hpp>
#include <eda/vhdl/ast/node/physical_literal.hpp>

namespace eda::vhdl::ast {

struct secondary_unit_declaration : position_tagged {
    ast::identifier identifier;
    ast::physical_literal physical_literal;
};

}  // namespace eda::vhdl::ast
