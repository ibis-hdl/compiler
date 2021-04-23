#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/assertion.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct concurrent_assertion_statement : position_tagged {
    optional<ast::label> label;
    bool postponed;
    ast::assertion assertion;

    concurrent_assertion_statement()
        : postponed{}
    {
    }
};

}  // namespace ibis::vhdl::ast
