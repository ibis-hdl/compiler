#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/choices.hpp>
#include <ibis/vhdl/ast/node/sequence_of_statements.hpp>

namespace ibis::vhdl::ast {

struct case_statement_alternative : position_tagged {
    ast::choices choices;
    ast::sequence_of_statements sequence_of_statements;
};

}  // namespace ibis::vhdl::ast
