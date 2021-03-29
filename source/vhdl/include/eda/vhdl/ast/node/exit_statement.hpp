#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/condition.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct exit_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::label> loop_label;
    optional<ast::condition> condition;
};

}  // namespace eda::vhdl::ast
