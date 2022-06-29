//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

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
