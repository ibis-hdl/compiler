//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-only
//

#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <ibis/vhdl/ast/node/label.hpp>
#include <ibis/vhdl/ast/node/sensitivity_list.hpp>
#include <ibis/vhdl/ast/node/process_declarative_part.hpp>
#include <ibis/vhdl/ast/node/sequence_of_statements.hpp>

#include <ibis/vhdl/ast/util/optional.hpp>

namespace ibis::vhdl::ast {

using process_statement_part = ast::sequence_of_statements;

struct process_statement : position_tagged {
    optional<ast::label> label;
    optional<ast::keyword_token> postponed;
    ast::sensitivity_list sensitivity_list;
    ast::process_declarative_part declarative_part;
    ast::process_statement_part statement_part;
    optional<ast::keyword_token> end_postponed;
    optional<ast::label> end_label;

    process_statement()
        : postponed{}
        , end_postponed{}
    {
    }
};

}  // namespace ibis::vhdl::ast
