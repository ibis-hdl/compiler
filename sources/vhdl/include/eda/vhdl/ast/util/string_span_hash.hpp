/*
 * string_span_hash.hpp
 *
 *  Created on: 26.06.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_STRING_SPAN_HASH_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_STRING_SPAN_HASH_HPP_

#include <eda/vhdl/ast/util/string_span.hpp>

#include <boost/range/iterator_range_hash.hpp>

namespace std {

template <> struct hash<eda::vhdl::ast::string_span> {
    size_t operator()(eda::vhdl::ast::string_span const& range) const noexcept
    {
        return boost::hash_range(range.begin(), range.end());
    }
};

} // namespace std

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_UTIL_STRING_SPAN_HASH_HPP_ */
