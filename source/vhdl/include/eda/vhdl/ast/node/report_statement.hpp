#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/expression.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct report_statement : position_tagged {
    optional<ast::label> label;
    ast::expression report;
    optional<ast::expression> severity;
};

}  // namespace eda::vhdl::ast
