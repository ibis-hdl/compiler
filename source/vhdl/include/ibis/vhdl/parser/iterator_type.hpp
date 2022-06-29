//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string_view>

namespace ibis::vhdl::parser {

///
/// Basic type used by the parser
///
/// std::string_view isn't a first citizen of Spirit.X3; from time to time
/// problems rises. To avoid they until std::string_view is fully supported
/// boost::range_iterator<IteratorType> exposed by x3::raw[] directive is used.
/// Unfortunately, the IteratorType is required up to the top level rule which
/// would required excessive rewrites of the grammar rules.
/// The simple work-around is to define it 'globally', since it must be of the
/// same type as of the x3::parse function.
/// For the concrete problem behind \see StackOverflow
/// [Spirit.X3 using string_view and member named 'insert' compiler error](
/// https://stackoverflow.com/questions/50310015/spirit-x3-using-string-view-and-member-named-insert-compiler-error?answertab=active#tab-top)
///
using char_type = char;

using iterator_type = std::basic_string_view<char_type>::const_iterator;

}  // namespace ibis::vhdl::parser
