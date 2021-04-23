#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/factor.hpp>
#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct term : position_tagged {
    struct chunk {
        operator_token multiplying_operator;
        ast::factor factor;
    };

    ast::factor factor;
    std::vector<chunk> rest_list;
};

}  // namespace ibis::vhdl::ast
