//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <boost/range/iterator_range_core.hpp>

#include <iosfwd>
#include <tuple>
#include <vector>
#include <functional>
#include <utility>
#include <type_traits>
#include <cassert>

namespace ibis::vhdl::parser {

///
/// tag used to get a position cache proxy back from the x3::context inside Spirit.X3 rules
///
struct annotator_tag;  // IWYU pragma: keep

// Todo Consider renaming to iterator_position_mapper (according file_mapper)
///
/// AST annotation/position cache
///
/// Mainly acts as manager to map file names to there string contents. These
/// properties are own, hence it's save to refer to them as long the instance
/// exist.
///
/// The class owns the filename and there contents as std::string.
///
/// @note parts of source is based on [../x3/support/utility/error_reporting.hpp](
/// https://github.com/boostorg/spirit/blob/develop/include/boost/spirit/home/x3/support/utility/error_reporting.hpp)
/// and [../x3/support/ast/position_tagged.hpp](
/// https://github.com/boostorg/spirit/blob/develop/include/boost/spirit/home/x3/support/ast/position_tagged.hpp)
///
template <typename IteratorT>
class position_cache {
public:
    using iterator_type = std::remove_cv_t<IteratorT>;
    using file_id_type = vhdl::ast::position_tagged::file_id_type;
    using position_id_type = vhdl::ast::position_tagged::position_id_type;
    using iterator_range_type = boost::iterator_range<iterator_type>;

private:
    std::vector<iterator_range_type> position_registry;

public:
    class annotator;

public:
    position_cache() = default;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    explicit position_cache(std::size_t mem_reserve) { position_registry.reserve(mem_reserve); }

    ~position_cache() = default;

    position_cache(position_cache&&) = default;
    position_cache& operator=(position_cache&&) = default;

    // not copyable, there must be only one position cache in the app
    position_cache(position_cache const&) = delete;
    position_cache& operator=(position_cache const&) = delete;

public:
    ///
    /// Store the iterator range for later use and return an identifier to map this id back to
    /// iterator range.
    ///
    /// @param first begin of tagged iterator range.
    /// @param last end of tagged iterator range.
    /// @return position_id_type The id mapped to the iterator range stored.
    ///
    position_id_type iterator_range_id(iterator_type first, iterator_type last)
    {
        auto position_id = next_id();
        position_registry.push_back({ first, last });  // OOM alert!
        return position_id;
    }

public:
    ///
    /// Extract the annotated iterator range from AST tagged node.
    ///
    /// @param node The AST node.
    /// @return boost::iterator_range tagged before by @ref annotate.
    ///
    iterator_range_type position_of(ast::position_tagged const& node) const
    {
        assert(valid_id(node.position_id) && "node position_id out of range!");
        return position_registry[node.position_id];
    }

public:
    std::size_t position_count() const { return position_registry.size(); }

private:
    ///
    /// Check if a given position ID is valid
    ///
    bool valid_id(position_id_type id) const { return std::cmp_less(id, position_registry.size()); }

    ///
    /// Get an ID
    ///
    position_id_type next_id() const
    {
        assert(std::cmp_less(position_registry.size(), ast::position_tagged::MAX_POSITION_ID) &&
               "Insufficient range of numeric IDs for AST tagging");

        return position_id_type{ position_registry.size() };
    }
};

}  // namespace ibis::vhdl::parser
