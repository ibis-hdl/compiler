#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/iteration_scheme.hpp>
#include <eda/vhdl/ast/node/sequence_of_statements.hpp>
#include <eda/vhdl/ast/util/optional.hpp>

namespace eda::vhdl::ast {

struct loop_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::iteration_scheme> iteration_scheme;
    ast::sequence_of_statements sequence_of_statements;
    optional<ast::label> end_label;
};

}  // namespace eda::vhdl::ast
