//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <range/v3/view/filter.hpp>

#include <format>

namespace ibis::vhdl::ast::numeric_convert::detail {

///
/// Filter separators from numeric string
///
/// @tparam RangeType
/// @param range The range (string) to be filter
/// @return auto a filtered view object
///
/// @note filter returns elements for which the predicate is true so one'll need to invert the
/// check to get the desired result.
/// Also read [Why must a std::ranges::filter_view object be non-const for querying its elements?](
///  https://stackoverflow.com/questions/67667318/why-must-a-stdrangesfilter-view-object-be-non-const-for-querying-its-element)
///
/// Concept @see [godbolt.org](https://godbolt.org/z/5Mv6zbhEM)
///
/// @code{.cpp}
/// ...
/// template<typename IterT> bool foo(IterT first, IterT last) {
///     for( ; first != last; ++first) { std::cout << *first;  }
///     return true;
/// }
///
/// int main() {
///     using namespace ranges;
///
///     auto const input = "007_42"sv;
///     std::cout << std::format("{}\n", input);
///
///     auto /*const*/ input_f = input | views::filter([](char chr) { return chr != '_'; });
///     foo(input_f.begin(), input_f.end());
/// }
/// @endcode
///
template <typename RangeType>
static inline auto filter_range(RangeType const& range)
{
    using namespace ranges;

    return range | views::filter([](char chr) { return chr != '_'; });
}

}  // namespace ibis::vhdl::ast::numeric_convert::detail
