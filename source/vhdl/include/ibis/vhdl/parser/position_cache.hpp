#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>
#include <ibis/vhdl/parser/iterator_type.hpp>

#include <ibis/compiler/warnings_off.hpp>  // [-Wsign-conversion]
#include <boost/range/iterator_range_core.hpp>
#include <ibis/compiler/warnings_on.hpp>

#include <iosfwd>
#include <tuple>
#include <type_traits>
#include <vector>
#include <cassert>

namespace ibis::vhdl::parser {

///
/// tag used to get our position cache proxy back from the x3::context inside Spirit.X3 rules
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
///
template <typename IteratorT>
class position_cache {
public:
    using iterator_type = IteratorT;
    using range_type = boost::iterator_range<iterator_type>;
    using position_registry_type = std::vector<range_type>;

    using file_id_type = ast::position_tagged::file_id_type;

private:
    // <filename, contents>
    using file_pair = std::tuple<std::string, std::string>;
    using file_registry_type = std::vector<file_pair>;

public:
    class proxy;

public:
    position_cache() = default;
    ~position_cache() = default;

    position_cache(position_cache const&) = delete;
    position_cache(position_cache&&) = delete;
    position_cache& operator=(position_cache const&) = delete;
    position_cache& operator=(position_cache&&) = delete;

public:
    ///
    /// Create an annotation/position cache proxy.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A proxy object with fixed file_id for convenience.
    ///
    proxy get_proxy(file_id_type file_id);

    std::size_t file_count() const { return file_registry.size(); }
    std::size_t position_count() const { return position_registry.size(); }

public:
    ///
    /// Maps a filename to contents.
    ///
    /// @param filename The file name as is it's shown e.g. by the error handler
    /// @param contents String view holding the file contents
    /// @return An ID which identifies the pair of 'filename' and 'contents' which
    /// can be referred later on using the proxy.
    ///
    /// @note This call makes internally a copy of filename and contents.
    /// @todo Check on use of fs::path as filename argument
    ///
    proxy add_file(std::string_view filename, std::string_view contents)
    {
        std::size_t const file_id = file_registry.size();
        file_registry.emplace_back(filename, contents);
        return get_proxy(file_id_type(file_id));
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
            // std::size_t size isn't enough?, this shouldn't never happen
            assert(position_registry.size() < ast::position_tagged::MAX_ID &&
                   "Insufficient range of numeric IDs for AST tagging");

            node.file_id = file_id;
            node.position_id = position_registry.size();
            position_registry.emplace_back(first, last);
        }
        else {
            // ignored since isn't ast::position_tagged derived
        }
    }

public:
    ///
    /// Get the file name.
    ///
    /// @param file_id ID of actually processed file.
    /// @return The filename as string view.
    ///
    std::string_view file_name(file_id_type file_id) const
    {
        assert(value_of(file_id) < file_registry.size() && "file_id out of range!");
        return std::get<0>(file_registry[value_of(file_id)]);
    }

    ///
    /// Get the file contents.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A string view representing of the file contents.
    ///
    std::string_view file_contents(file_id_type file_id) const
    {
        assert(value_of(file_id) < file_registry.size() && "file_id out of range!");
        return std::get<1>(file_registry[value_of(file_id)]);
    }

    ///
    /// Extract the annotated iterator range from AST tagged node.
    ///
    /// @param node The AST node.
    /// @return boost::iterator_range tagged before by @ref annotate.
    ///
    range_type position_of(ast::position_tagged const& node) const
    {
        return position_registry[node.position_id];
    }

private:
    file_registry_type file_registry;
    position_registry_type position_registry;
};

///
/// AST annotation/position cache proxy.
///
/// This gives the same API as position_cache, but with an ID bound to this proxy
/// to simplify AST tagging and error_handling.
///
/// \note This class is intended to created by the position_cache's get_proxy()
/// function only.
///
template <typename IteratorT>
class position_cache<IteratorT>::proxy {
public:
    proxy(position_cache<IteratorT>& position_cache_, file_id_type file_id_)
        : self{ position_cache_ }
        , file_id{ file_id_ }
    {
    }

public:
    /// Get the id of current <file_name, contents>.
    file_id_type id() const { return file_id; }

    /// Set the current <file_name, contents> to another id.
    void set_id(file_id_type id) const { file_id = id; }

public:
    /// annotate the given node.
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        self.annotate(file_id, node, first, last);
    }

public:
    /// annotated iterator range from AST tagged node.
    range_type position_of(ast::position_tagged const& node) const
    {
        return self.position_of(node);
    }

public:
    /// Get the file name.
    std::string_view file_name() const { return self.file_name(file_id); }

    /// Get the file contents.
    std::string_view file_contents() const { return self.file_contents(file_id); }

    /// Get the iterator (range) of the file contents.
    std::tuple<iterator_type, iterator_type> file_contents_range() const
    {
        auto const contents = file_contents();

        return { contents.cbegin(), contents.cend() };
    }

private:
    position_cache<IteratorT>& self;
    file_id_type mutable file_id;
};

template <typename IteratorT>
typename position_cache<IteratorT>::proxy position_cache<IteratorT>::get_proxy(file_id_type file_id)
{
    return proxy{ *this, file_id };
}

}  // namespace ibis::vhdl::parser

namespace ibis::vhdl::parser {

/// Explicit template instantiation declaration
extern template class position_cache<parser::iterator_type>;

}  // namespace ibis::vhdl::parser
