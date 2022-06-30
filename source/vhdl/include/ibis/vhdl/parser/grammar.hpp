//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/ast.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/spirit/home/x3.hpp>
#include <ibis/util/compiler/warnings_on.hpp>
#include <boost/spirit/home/x3/nonterminal/rule.hpp>

namespace ibis::vhdl::parser {

struct design_file_class;
using design_file_type = boost::spirit::x3::rule<design_file_class, ast::design_file>;

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

parser::design_file_type const& grammar();

}  // namespace ibis::vhdl::parser
