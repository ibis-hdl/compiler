#pragma once

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>
//#include <boost/range/iterator_range.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/iterator_range_io.hpp>

namespace ibis::vhdl::ast::numeric_convert::detail {

template <typename RangeType>
static auto filter_range(RangeType const& range)
{
    struct separator_predicate {
        bool operator()(char x) { return '_' != x; }
    };

    return boost::make_iterator_range(
        boost::make_filter_iterator(separator_predicate{}, range.begin(), range.end()),
        boost::make_filter_iterator(separator_predicate{}, range.end()));
}

}  // namespace ibis::vhdl::ast::numeric_convert::detail
