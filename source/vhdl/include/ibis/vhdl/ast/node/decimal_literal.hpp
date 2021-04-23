#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/util/string_span.hpp>

namespace ibis::vhdl::ast {

struct decimal_literal : position_tagged {
    enum class kind_specifier { integer, real };

    ast::string_span literal;
    kind_specifier kind_type;
};

}  // namespace ibis::vhdl::ast
