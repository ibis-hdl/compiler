//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/parser/grammar.hpp>
#include <ibis/vhdl/parser/grammar_def.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

namespace ibis::vhdl {

parser::grammar_type const& grammar() { return ibis::vhdl::parser::grammar_entry; }

}  // namespace ibis::vhdl::parser

//
// The Spirit X3 grammar instance
//
namespace ibis::vhdl::parser {

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)
BOOST_SPIRIT_INSTANTIATE(grammar_type, iterator_type, context_type)
#endif

}  // namespace ibis::vhdl::parser
