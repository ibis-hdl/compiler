#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/util/string_span.hpp>

namespace eda::vhdl::ast {

struct decimal_literal : position_tagged {
    enum class kind_specifier { integer, real };

    ast::string_span literal;
    kind_specifier kind_type;
};

}  // namespace eda::vhdl::ast
