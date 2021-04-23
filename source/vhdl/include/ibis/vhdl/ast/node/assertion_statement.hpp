#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/assertion.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct assertion_statement : position_tagged {
    optional<ast::label> label;
    ast::assertion assertion;
};

}  // namespace ibis::vhdl::ast
