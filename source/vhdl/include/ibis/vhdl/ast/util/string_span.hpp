//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/range/iterator_range_core.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <ibis/vhdl/parser/iterator_type.hpp>

#include <string_view>

namespace ibis::vhdl::ast {

//
// Hot Fix
//
// This is required to work with 'string_view', later version of Spirit.X3
// as 1.64. Note the hard coded iterator type!!, \see
// [Spirit.X3 using string_view and member named 'insert' compiler error](
//  https://stackoverflow.com/questions/50310015/spirit-x3-using-string-view-and-member-named-insert-compiler-error?answertab=active#tab-top)
//
using string_span = boost::iterator_range<parser::iterator_type>;

//
// Helper function to handle string_span node elements into an C++ standard
// conformance way.
//
inline std::string_view as_string_view(ast::string_span const& string_span)
{
    return std::string_view{ &string_span.front(), string_span.size() };
}

}  // namespace ibis::vhdl::ast
