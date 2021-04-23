#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/condition.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct next_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::label> loop_label;
    optional<ast::condition> condition;
};

}  // namespace ibis::vhdl::ast
