#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/case_statement_alternative.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct case_statement : position_tagged {
    optional<ast::label> label;
    ast::expression expression;
    std::vector<ast::case_statement_alternative> alternatives;
    optional<ast::label> end_label;
};

}  // namespace eda::vhdl::ast
