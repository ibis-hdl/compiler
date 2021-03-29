#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>

namespace eda::vhdl::ast {

struct based_literal : position_tagged {
    enum class kind_specifier { integer, real };

    struct number_chunk {
        ast::string_span integer_part;
        ast::string_span fractional_part;
        ast::string_span exponent;
        kind_specifier kind_type;
    };

    ast::string_span base;
    number_chunk number;
};

}  // namespace eda::vhdl::ast
