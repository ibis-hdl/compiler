//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast.hpp>
#include <ibis/vhdl/parser/grammar_id.hpp>

#include <boost/spirit/home/x3/core.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>  // Note, alone doesn't compile

namespace ibis::vhdl::parser {


//
// recursive parser rule types
//

using configuration_item_type = x3::rule<configuration_item_class, ast::configuration_item>;
using concurrent_statement_type = x3::rule<concurrent_statement_class, ast::concurrent_statement>;
using constraint_type = x3::rule<constraint_class, ast::constraint>;
using sequence_of_statements_type = x3::rule<sequence_of_statements_class, ast::sequence_of_statements>;
using subprogram_declarative_item_type = x3::rule<subprogram_declarative_item_class,ast::subprogram_declarative_item>;

using design_file_type = x3::rule<design_file_class, ast::design_file>;

// start rule
using grammar_type = x3::rule<grammar_class, ast::design_file>;

// clang-format off
using attribute_name_type = x3::rule<attribute_name_class, ast::attribute_name>;
using expression_type = x3::rule<expression_class, ast::expression>;
using function_call_type = x3::rule<function_call_class, ast::function_call>;
using indexed_name_type = x3::rule<indexed_name_class, ast::indexed_name>;
using literal_type = x3::rule<literal_class, ast::literal>;
using name_type = x3::rule<name_class, ast::name>;
using prefix_type = x3::rule<prefix_class, ast::prefix>;
using primary_type = x3::rule<primary_class, ast::primary>;
using range_type = x3::rule<range_class, ast::range>;
using selected_name_type = x3::rule<selected_name_class, ast::selected_name>;
using slice_name_type = x3::rule<slice_name_class, ast::slice_name>;
// clang-format on

}  // namespace ibis::vhdl::parser
