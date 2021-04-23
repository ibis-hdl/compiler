#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/simple_name.hpp>
#include <ibis/vhdl/ast/node/discrete_range.hpp>
#include <ibis/vhdl/ast/node/simple_expression.hpp>
#include <ibis/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace ibis::vhdl::ast {

using choice =                  // --
    variant<nullary,            // --
            simple_name,        // --
            discrete_range,     // --
            simple_expression,  // --
            keyword_token       // OTHERS
            >;

using choices = std::vector<choice>;

}  // namespace ibis::vhdl::ast
