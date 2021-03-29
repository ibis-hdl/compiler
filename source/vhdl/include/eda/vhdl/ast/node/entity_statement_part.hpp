#pragma once

#include <eda/vhdl/ast/util/variant.hpp>

#include <eda/vhdl/ast/util/nullary.hpp>
#include <eda/vhdl/ast/node/concurrent_assertion_statement.hpp>
#include <eda/vhdl/ast/node/concurrent_procedure_call_statement.hpp>
#include <eda/vhdl/ast/node/process_statement.hpp>
#include <vector>

namespace eda::vhdl::ast {

using entity_statement = variant<
    ast::nullary, ast::concurrent_assertion_statement,
    ast::concurrent_procedure_call_statement,  // passive_concurrent_procedure_call_statement
    ast::process_statement                     // passive_process_statement
    >;

struct entity_statement_part : std::vector<ast::entity_statement> {
};

}  // namespace eda::vhdl::ast
