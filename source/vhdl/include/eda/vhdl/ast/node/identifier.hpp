#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>

namespace eda::vhdl::ast {

struct identifier : position_tagged {
    ast::string_span name;
};

}  // namespace eda::vhdl::ast
