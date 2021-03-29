#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/delay_mechanism.hpp>
#include <eda/vhdl/ast/node/keyword_token.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct options : position_tagged {
    bool guarded;
    optional<ast::delay_mechanism> delay_mechanism;

    options()
        : guarded{}
    {
    }
};

}  // namespace eda::vhdl::ast
