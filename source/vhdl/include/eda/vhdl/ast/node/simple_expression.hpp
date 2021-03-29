#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/operator_token.hpp>
#include <eda/vhdl/ast/node/term.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct simple_expression : position_tagged {
    struct chunk {
        operator_token adding_operator;
        ast::term term;
    };

    optional<operator_token> sign;
    ast::term term;
    std::vector<chunk> rest_list;
};

}  // namespace eda::vhdl::ast
