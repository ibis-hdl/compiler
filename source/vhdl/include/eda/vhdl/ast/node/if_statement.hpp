#pragma once

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <eda/vhdl/ast/node/concurrent_statement.hpp>
#include <eda/vhdl/ast/node/condition.hpp>
#include <eda/vhdl/ast/node/label.hpp>
#include <eda/vhdl/ast/node/sequence_of_statements.hpp>
#include <eda/vhdl/ast/util/optional.hpp>
#include <vector>

namespace eda::vhdl::ast {

struct if_statement : position_tagged {
    struct elsif_chunk {
        ast::condition condition;
        ast::sequence_of_statements sequence_of_statements;
    };

    optional<ast::label> label;
    ast::condition if_condition;
    ast::sequence_of_statements then_sequence_of_statements;
    std::vector<elsif_chunk> elseif_chunks;
    ast::sequence_of_statements else_sequence_of_statements;
    optional<ast::label> end_label;
};

}  // namespace eda::vhdl::ast
