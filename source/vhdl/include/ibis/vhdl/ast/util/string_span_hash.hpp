#pragma once

#include <ibis/vhdl/ast/util/string_span.hpp>

#include <boost/range/iterator_range_hash.hpp>

namespace std {

template <>
struct hash<ibis::vhdl::ast::string_span> {
    size_t operator()(ibis::vhdl::ast::string_span const& range) const noexcept
    {
        return boost::hash_range(range.begin(), range.end());
    }
};

}  // namespace std
