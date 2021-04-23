#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/abstract_literal.hpp>
#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct physical_literal : position_tagged {
    abstract_literal literal;
    ast::string_span unit_name;
};

}  // namespace ibis::vhdl::ast
