#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct string_literal : position_tagged {
    ast::string_span literal;
};

}  // namespace ibis::vhdl::ast
