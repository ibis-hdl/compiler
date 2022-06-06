//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/concurrent_statement.hpp>
#include <ibis/vhdl/ast/node/condition.hpp>
#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/sequence_of_statements.hpp>
#include <ibis/vhdl/ast/util/optional.hpp>
#include <vector>

namespace ibis::vhdl::ast {

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

}  // namespace ibis::vhdl::ast
