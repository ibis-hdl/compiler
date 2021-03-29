#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>

namespace eda::vhdl::ast {

struct string_literal : position_tagged {
    ast::string_span literal;
};

}  // namespace eda::vhdl::ast
