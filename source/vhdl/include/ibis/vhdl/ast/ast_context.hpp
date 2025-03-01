//
// Copyright (c) 2017-2025 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>

#include <functional>
#include <type_traits>

namespace ibis::vhdl::ast {

template <typename IteratorT>
class ast_context {  // ToDo rename to current_file_context ???
public:
    using iterator_type = std::remove_cv_t<IteratorT>;
    using file_id_type = ibis::util::file_mapper::file_id_type;
    using iterator_range_type =
        typename ibis::vhdl::parser::position_cache<iterator_type>::iterator_range_type;

private:
    using current_file_type = util::file_mapper::current_file;
    using position_cache_type = ibis::vhdl::parser::position_cache<iterator_type>;

    current_file_type current_file;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init]) - default ctor is deleted
    std::reference_wrapper<position_cache_type> ref_position_cache;

public:
    ast_context() = delete;

    ast_context(current_file_type current_file,
                std::reference_wrapper<position_cache_type> position_cache)
        : current_file{ current_file }
        , ref_position_cache{ position_cache }
    {
    }

public:
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_cv_t<NodeT>>) {
            // OOM error handling/strategy missing, push_back()/emplace_back() may fail, even if
            // uncertainly
            node.file_id = current_file.file_id();
            node.position_id = ref_position_cache.get().iterator_range_id(first, last);
        }
        else {
            // Subclassing of the x3 parser rule tag class determines the call of on_success() of
            // this parser rule/class. However, the NodeT class is not derived from position_tagged
            // and therefore cannot be tagged. Hence, there is a discrepancy between the intention
            // to tag using the X3 rule and this (unprepared) node.
            // ToDo Consider to abort due to discrepancy between parser rule and node properties.
        }
    }

    iterator_range_type position_of(ast::position_tagged const& node) const
    {
        return ref_position_cache.get().position_of(node);
    }

public:
    file_id_type file_id() const { return current_file.file_id(); };
    std::string_view file_name() const { return current_file.file_name(); }
    std::string_view file_contents() const { return current_file.file_contents(); }
};

}  // namespace ibis::vhdl::ast
