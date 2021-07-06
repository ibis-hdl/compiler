#pragma once

#include <ibis/vhdl/ast/util/position_tagged.hpp>

#include <iosfwd>
#include <optional>
#include <tuple>
#include <type_traits>
#include <vector>

#include <boost/range/iterator_range.hpp>

#include <ibis/util/cxx_bug_fatal.hpp>

namespace ibis::vhdl::parser {

///
/// tag used to get our position cache proxy from the x3::context
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
template <typename IteratorT>
class position_cache {
public:
    using iterator_type = IteratorT;
    using position_container_type = std::vector<boost::iterator_range<iterator_type>>;

    using range_type = typename position_container_type::value_type;

    using file_id_type = ast::position_tagged::file_tag_type;

private:
    // <filename, contents>
    using file_pair = std::tuple<std::string, std::string>;
    using file_container_type = std::vector<file_pair>;

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

    std::size_t file_count() const { return files.size(); }
    std::size_t position_count() const { return positions.size(); }

public:
    ///
    /// Maps a filename to contents.
    ///
    /// @param filename The file name as is it's shown e.g. by the error handler
    /// @param contents Optional a string holding the file contents
    /// @return An ID which identifies the pair of 'filename' and 'contents' which
    ///        can be referred later on using the proxy.
    ///
    /// @note This call makes internally a copy of filename and contents.
    /// @todo Check on use of fs::path as filename argument
    ///
    proxy add_file(std::string_view filename, std::string_view contents)
    {
        std::size_t const file_id = files.size();
        files.emplace_back(filename, contents);
        return get_proxy(file_id_type(file_id));
    }

public:
    ///
    /// Annotate the AST node with positional iterators.
    ///
    /// This is called from parser::success_handler to allow expressive error handling. Only
    /// AST nodes that are derived from ```ast::position_tagged``` are tagged.
    ///
    /// @param file_id ID of actually processed file.
    /// @param node    The AST node to tag
    /// @param first   Begin of iterator position to tag.
    /// @param last    End  of iterator position to tag.
    ///
    /// @todo maybe better throw range_exception since it's an implementation
    /// limitation.
    template <typename NodeT>
    void annotate(file_id_type file_id, NodeT& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            cxx_assert(positions.size() < ast::position_tagged::MAX_ID,
                       "Insufficient range of numeric IDs for AST tagging");

            node.file_id = file_id;
            node.pos_id = positions.size();
            positions.emplace_back(first, last);
        }
        else {
            // ignored since isn't tagged
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
        assert(value_of(file_id) < files.size() && "file_id out of range!");
        return std::get<0>(files[value_of(file_id)]);
    }

    ///
    /// Get the file contents.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A string view representing the file contents.
    ///
    std::string_view file_contents(file_id_type file_id) const
    {
        assert(value_of(file_id) < files.size() && "file_id out of range!");
        return std::get<1>(files[value_of(file_id)]);
    }

    ///
    /// Get the iterator (range) of the file contents.
    ///
    /// @param file_id ID of actually processed file.
    /// @return A pair of iterators pointing to begin and end of the file contents.
    ///
    std::tuple<iterator_type, iterator_type> range(file_id_type file_id) const
    {
        auto const contents = file_contents(file_id);

        return { contents.cbegin(), contents.cend() };
    }

    ///
    /// Extract the iterator range from AST tagged node.
    ///
    /// @param node The AST node.
    /// @return boost::iterator_range tagged before by \ref annotate. If the node not tagged an
    /// empty iterator_range is returned. To distinguish between they are packed into an optional.
    ///
    template <typename NodeT>
    std::optional<range_type> position_of(NodeT const& node) const
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            return positions[node.pos_id];
        }

        return {};
    }

public:
    ///
    /// Return the line number of a given iterator position. The position must
    /// be within the position cache range.
    ///
    /// @param file_id ID of actually processed file.
    /// @param pos Iterator position where to gather the line number.
    /// @param tab_sz The tab size, required to calculate the column number.
    /// @return The line number.
    ///
    std::tuple<std::size_t, std::size_t> line_column_number(  // --
        file_id_type file_id, iterator_type const& pos, std::size_t tab_sz) const;

    ///
    /// Return an iterator to the begin of the line. White spaces are skipped.
    /// The position must be within the position cache range.
    /// \note For this, the pos_iter is modified.
    ///
    /// @param file_id ID of actually processed file.
    /// @param pos Iterator position pointing to a line of interest.
    /// @return Iterator position pointing to the begin of line.
    ///
    iterator_type get_line_start(file_id_type file_id, iterator_type& pos) const;

    ///
    /// Print the line where the iterator points to until end-of-line.
    ///
    /// @param file_id ID of actually processed file.
    /// @param first Iterator position pointing to a line of interest.
    /// @return String representing the source line.
    ///
    /// FixMe: Starting with Spirit V3.0.7 (Boost V1.74.0) dependence on Boost.Locale
    /// is ceased (replace locale::conv::utf_to_utf with x3::to_utf8)
    std::string_view current_line(file_id_type file_id, iterator_type const& first) const;

private:
    file_container_type files;
    position_container_type positions;
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
    template <typename NodeT>
    std::optional<range_type> position_of(NodeT const& node) const
    {
        return self.position_of(node);
    }

public:
    std::string_view file_name() const { return self.file_name(file_id); }
    std::string_view file_contents() const { return self.file_contents(file_id); }
    std::tuple<IteratorT, IteratorT> range() const { return self.range(file_id); }

public:
    std::tuple<std::size_t, std::size_t> line_column_number(iterator_type const& pos, std::size_t tab_sz) const
    {
        return self.line_column_number(file_id, pos, tab_sz);
    }

    iterator_type get_line_start(iterator_type& pos_iter) const
    {
        return self.get_line_start(file_id, pos_iter);
    }

    std::string_view current_line(iterator_type const& start) const
    {
        return self.current_line(file_id, start);
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
