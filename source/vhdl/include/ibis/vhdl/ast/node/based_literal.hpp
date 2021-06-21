#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct based_literal : position_tagged {
    enum class numeric_type_specifier { integer, real };

    struct number_chunk {
        ast::string_span integer_part;
        ast::string_span fractional_part;
        ast::string_span exponent;
        numeric_type_specifier type_specifier;
    };

    ast::string_span base;
    number_chunk number;

    /// convenience access to numeric type represented.
    numeric_type_specifier numeric_type() const { return number.type_specifier; }
};

}  // namespace ibis::vhdl::ast
