#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/operator_token.hpp>
#include <ibis/vhdl/ast/node/relation.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct expression : position_tagged {
    struct chunk {
        operator_token logical_operator;
        ast::relation relation;
    };

    ast::relation relation;
    std::vector<chunk> rest_list;
};

}  // namespace ibis::vhdl::ast
