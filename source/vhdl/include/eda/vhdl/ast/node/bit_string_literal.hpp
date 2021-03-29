#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>

namespace eda::vhdl::ast {

struct bit_string_literal : position_tagged {
    enum class base_specifier { bin, oct, hex };

    ast::string_span literal;
    base_specifier base_type;
};

}  // namespace eda::vhdl::ast
