#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/assertion.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct concurrent_assertion_statement : position_tagged {
    optional<ast::label> label;
    bool postponed;
    ast::assertion assertion;

    concurrent_assertion_statement()
        : postponed{}
    {
    }
};

}  // namespace eda::vhdl::ast
