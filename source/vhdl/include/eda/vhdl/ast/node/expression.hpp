#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/relation.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct expression : position_tagged {
    struct chunk {
        operator_token logical_operator;
        ast::relation relation;
    };

    ast::relation relation;
    std::vector<chunk> rest_list;
};

}  // namespace eda::vhdl::ast
