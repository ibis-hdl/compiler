#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/choices.hpp>
#include <eda/vhdl/ast/node/sequence_of_statements.hpp>

namespace eda::vhdl::ast {

struct case_statement_alternative : position_tagged {
    ast::choices choices;
    ast::sequence_of_statements sequence_of_statements;
};

}  // namespace eda::vhdl::ast
