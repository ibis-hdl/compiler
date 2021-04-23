#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/iteration_scheme.hpp>
#include <ibis/vhdl/ast/node/sequence_of_statements.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

struct loop_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::iteration_scheme> iteration_scheme;
    ast::sequence_of_statements sequence_of_statements;
    optional<ast::label> end_label;
};

}  // namespace ibis::vhdl::ast
