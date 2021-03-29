#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/abstract_literal.hpp>
#include <eda/vhdl/ast/util/string_span.hpp>

namespace eda::vhdl::ast {

struct physical_literal : position_tagged {
    abstract_literal literal;
    ast::string_span unit_name;
};

}  // namespace eda::vhdl::ast
