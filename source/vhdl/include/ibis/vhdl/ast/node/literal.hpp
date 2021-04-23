#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/numeric_literal.hpp>
#include <ibis/vhdl/ast/node/enumeration_literal.hpp>
#include <ibis/vhdl/ast/node/string_literal.hpp>
#include <ibis/vhdl/ast/node/bit_string_literal.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>

namespace ibis::vhdl::ast {

// literal ::=
//        numeric_literal
//      | enumeration_literal
//      | string_literal
//      | bit_string_literal
//      | null
struct literal
    : variant<nullary, numeric_literal, enumeration_literal, string_literal, bit_string_literal,
              keyword_token  // NULL
              > {
    using base_type::base_type;
    using base_type::operator=;
};

}  // namespace ibis::vhdl::ast
