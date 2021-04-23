#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct bit_string_literal : position_tagged {
    enum class base_specifier { bin, oct, hex };

    ast::string_span literal;
    base_specifier base_type;
};

}  // namespace ibis::vhdl::ast
