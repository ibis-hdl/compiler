#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/condition_clause.hpp>
#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/sensitivity_clause.hpp>
#include <eda/vhdl/ast/node/timeout_clause.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct wait_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::sensitivity_clause> sensitivity_clause;
    optional<ast::condition_clause> condition_clause;
    optional<ast::timeout_clause> timeout_clause;
};

}  // namespace eda::vhdl::ast
