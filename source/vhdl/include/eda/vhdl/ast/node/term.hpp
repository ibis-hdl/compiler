#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/factor.hpp>
#include <eda/vhdl/ast/node/operator_token.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct term : position_tagged {
    struct chunk {
        operator_token multiplying_operator;
        ast::factor factor;
    };

    ast::factor factor;
    std::vector<chunk> rest_list;
};

}  // namespace eda::vhdl::ast
