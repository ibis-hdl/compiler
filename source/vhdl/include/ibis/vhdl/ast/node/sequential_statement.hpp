//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast/util/variant.hpp>

#include <ibis/vhdl/ast/util/nullary.hpp>
#include <ibis/vhdl/ast/node/assertion_statement.hpp>
#include <ibis/vhdl/ast/node/exit_statement.hpp>
#include <ibis/vhdl/ast/node/next_statement.hpp>
#include <ibis/vhdl/ast/node/null_statement.hpp>
#include <ibis/vhdl/ast/node/procedure_call_statement.hpp>
#include <ibis/vhdl/ast/node/report_statement.hpp>
#include <ibis/vhdl/ast/node/return_statement.hpp>
#include <ibis/vhdl/ast/node/signal_assignment_statement.hpp>
#include <ibis/vhdl/ast/node/variable_assignment_statement.hpp>
#include <ibis/vhdl/ast/node/wait_statement.hpp>

namespace ibis::vhdl::ast {

struct if_statement;
struct case_statement;
struct loop_statement;

///
/// Ast node cyclic dependency as:
///
/// \dot
/// digraph sequential_statement  {
///  sequential_statement -> if_statement [ label=<<i>forward</i>>];
///  if_statement         -> sequence_of_statements;
///
///  sequential_statement -> case_statement [ label=<<i>forward</i>>];
///  case_statement       -> sequence_of_statements;
///
///  sequential_statement -> loop_statement [ label=<<i>forward</i>>];
///  loop_statement       -> sequence_of_statements;
///
///  sequence_of_statements -> sequential_statement
/// }
/// \enddot
///
using sequential_statement =
    variant<nullary, wait_statement, assertion_statement, report_statement,
            signal_assignment_statement, variable_assignment_statement, procedure_call_statement,
            forward_ast<if_statement>, forward_ast<case_statement>, forward_ast<loop_statement>,
            next_statement, exit_statement, return_statement, null_statement>;

}  // namespace ibis::vhdl::ast
