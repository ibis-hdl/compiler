#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct decimal_literal : position_tagged {
    enum class numeric_type_specifier { integer, real };

    ast::string_span literal;
    numeric_type_specifier type_specifier;

    /// convenience access to numeric type represented.
    numeric_type_specifier numeric_type() const { return type_specifier; }
};

}  // namespace ibis::vhdl::ast
