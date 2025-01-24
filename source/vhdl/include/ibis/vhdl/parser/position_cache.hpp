//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <ibis/util/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/range/iterator_range_core.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <iosfwd>
#include <tuple>
#include <type_traits>
#include <vector>
#include <functional>
#include <utility>
#include <cassert>

namespace ibis::vhdl::parser {

///
/// tag used to get a position cache proxy back from the x3::context inside Spirit.X3 rules
///
struct position_cache_tag;  // IWYU pragma: keep

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
// ToDo For historical and convenience reasons the API acts for file_mapper and position_cache,
// fix it later - move it to future vhdl_global_context, accessible via x3::which[] or
// boost::parser::global()
template <typename IteratorT>
class position_cache {
public:
    using iterator_type = std::remove_cv_t<IteratorT>;
    using range_type = boost::iterator_range<iterator_type>;
    using file_id_type = vhdl::ast::position_tagged::file_id_type;
    using position_id_type = vhdl::ast::position_tagged::position_id_type;

private:
    static constexpr auto MAX_ID = ast::position_tagged::MAX_POSITION_ID;

public:
    class proxy;  // FixMe XXX rename current_file(_proxy)

public:
    position_cache(std::reference_wrapper<util::file_mapper> file_mapper_,
                   std::size_t mem_reserve = 4096)
        : file_mapper{ file_mapper_ }
    {
        position_registry.reserve(mem_reserve);
    }

    ~position_cache() = default;

    position_cache(position_cache&&) = default;
    position_cache& operator=(position_cache&&) = default;

    position_cache(position_cache const&) = delete;
    position_cache& operator=(position_cache const&) = delete;

public:
    ///
    /// Create an annotation/position cache proxy.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A proxy object with fixed file_id for convenience.
    ///
    proxy get_proxy(file_id_type file_id);

public:
    std::size_t position_count() const { return position_registry.size(); }

public:
    std::size_t file_count() const { return file_mapper.get().file_count(); }

    ///
    /// Get the file name.
    ///
    /// @param file_id ID of actually processed file.
    /// @return The filename as string view.
    ///
    std::string_view file_name(file_id_type file_id) const
    {
        assert(file_mapper.get().valid_id(file_id) && "file_id out of range!");
        return file_mapper.get().file_name(file_id);
    }

    ///
    /// Get the file contents.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A string view representing of the file contents.
    ///
    std::string_view file_contents(file_id_type file_id) const
    {
        assert(file_mapper.get().valid_id(file_id) && "file_id out of range!");
        return file_mapper.get().file_contents(file_id);
    }

public:
    ///
    /// Annotate the AST node with positional iterators.
    ///
    /// This is called from parser::success_handler to allow expressive error handling. Only
    /// AST nodes that are derived from @ref ast::position_tagged are tagged.
    ///
    /// @param file_id ID of actually processed file.
    /// @param node    The AST node to tag
    /// @param first   Begin of iterator position to tag.
    /// @param last    End  of iterator position to tag.
    ///
    template <typename NodeT>
    void annotate(file_id_type file_id, NodeT& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            // ToDo [C++26] use std::format to print the max ID
            assert(std::cmp_less(position_registry.size(), MAX_ID) &&
                   "Insufficient range of numeric IDs for AST tagging");

            node.file_id = file_id;
            node.position_id = next_id();
            // ToDo OOM error handling (scope_exit would be overkill)
            position_registry.emplace_back(first, last);
        }
        else {
            // ignored since isn't ast::position_tagged derived
            // ToDo: Consider about handling annotating untagged node, nothings, logging, abort()?
        }
    }

public:
    ///
    /// Extract the annotated iterator range from AST tagged node.
    ///
    /// @param node The AST node.
    /// @return boost::iterator_range tagged before by @ref annotate.
    ///
    range_type position_of(ast::position_tagged const& node) const
    {
        assert(valid_id(node.position_id) && "node position_id out of range!");
        return position_registry[node.position_id];
    }

private:
    ///
    /// Check if a given position ID is valid
    ///
    bool valid_id(position_id_type id) const { return std::cmp_less(id, position_registry.size()); }

    ///
    /// Get an ID
    ///
    std::size_t next_id() const { return position_registry.size(); }

private:
    using position_registry_type = std::vector<range_type>;

private:
    std::reference_wrapper<util::file_mapper> file_mapper;
    position_registry_type position_registry;
};

///
/// AST annotation/position cache proxy.
///
/// This gives the same API as position_cache, but with an ID bound to this proxy
/// to simplify AST tagging and error_handling.
///
/// @note This class is intended to created by the position_cache's get_proxy()
/// function only.
///
template <typename IteratorT>
class position_cache<IteratorT>::proxy {
public:
    proxy(std::reference_wrapper<position_cache<IteratorT>> ref_self, file_id_type id)
        : self{ ref_self }
        , file_id{ id }
    {
    }

    proxy() = delete;
    ~proxy() = default;

    proxy(proxy&&) = default;
    proxy& operator=(proxy&&) = default;

    proxy(proxy const&) = default;
    proxy& operator=(proxy const&) = default;

public:
    /// Get the id of current <file_name, contents>.
    file_id_type id() const { return file_id; }

public:
    /// annotate the given node.
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        self.get().annotate(file_id, node, first, last);
    }

public:
    /// annotated iterator range from AST tagged node.
    range_type position_of(ast::position_tagged const& node) const
    {
        return self.get().position_of(node);
    }

public:  // ToDo Fix alienated file_mapper API functions
    /// Get the file name.
    std::string_view file_name() const { return self.get().file_name(file_id); }

    /// Get the file contents.
    std::string_view file_contents() const { return self.get().file_contents(file_id); }

    /// Get the iterator (range) of the file contents.
    std::tuple<iterator_type, iterator_type> file_contents_range() const
    {
        auto contents = file_contents();
        return { contents.cbegin(), contents.cend() };
    }

private:
    std::reference_wrapper<position_cache<IteratorT>> self;
    file_id_type file_id;
};

template <typename IteratorT>
typename position_cache<IteratorT>::proxy position_cache<IteratorT>::get_proxy(file_id_type file_id)
{
    return proxy{ std::ref(*this), file_id };
}

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

/// Explicit template instantiation declaration
// XXX extern template class position_cache<parser::iterator_type>;

}  // namespace ibis::vhdl::parser
