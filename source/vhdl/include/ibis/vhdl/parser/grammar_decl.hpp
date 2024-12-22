//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/vhdl/parser/grammar_type.hpp>

//
// rule declaration
//

namespace ibis::vhdl::parser {

#if !defined(DOXYGEN_DOCUMENTATION_BUILD)

// recursive parser
BOOST_SPIRIT_DECLARE(configuration_item_type)
BOOST_SPIRIT_DECLARE(concurrent_statement_type)
BOOST_SPIRIT_DECLARE(constraint_type)
BOOST_SPIRIT_DECLARE(sequence_of_statements_type)
BOOST_SPIRIT_DECLARE(subprogram_declarative_item)

BOOST_SPIRIT_DECLARE(design_file_type)

// start rule
BOOST_SPIRIT_DECLARE(grammar_type)

// other
BOOST_SPIRIT_DECLARE(attribute_name_type)
BOOST_SPIRIT_DECLARE(expression_type)
BOOST_SPIRIT_DECLARE(function_call_type)
BOOST_SPIRIT_DECLARE(literal_type)
BOOST_SPIRIT_DECLARE(name_type)
BOOST_SPIRIT_DECLARE(prefix_type)
BOOST_SPIRIT_DECLARE(primary_type)
BOOST_SPIRIT_DECLARE(range_type)
BOOST_SPIRIT_DECLARE(selected_name_type)
BOOST_SPIRIT_DECLARE(slice_name_type)

#endif  // !defined(DOXYGEN_DOCUMENTATION_BUILD)

}  // namespace ibis::vhdl::parser
