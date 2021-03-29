#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/simple_name.hpp>
#include <eda/vhdl/ast/node/discrete_range.hpp>
#include <eda/vhdl/ast/node/simple_expression.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <vector>

namespace eda::vhdl::ast {

using choice =                  // --
    variant<nullary,            // --
            simple_name,        // --
            discrete_range,     // --
            simple_expression,  // --
            keyword_token       // OTHERS
            >;

using choices = std::vector<choice>;

}  // namespace eda::vhdl::ast
