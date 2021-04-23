#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/case_statement_alternative.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

struct case_statement : position_tagged {
    optional<ast::label> label;
    ast::expression expression;
    std::vector<ast::case_statement_alternative> alternatives;
    optional<ast::label> end_label;
};

}  // namespace ibis::vhdl::ast
