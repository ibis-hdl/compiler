#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/context_clause.hpp>
#include <eda/vhdl/ast/node/library_unit.hpp>

namespace eda::vhdl::ast {

struct design_unit : position_tagged {
    ast::context_clause context_clause;
    ast::library_unit library_unit;
};

}  // namespace eda::vhdl::ast
