/*
 * position_cache.hpp
 *
 *  Created on: 18.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_POSITION_CACHE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_POSITION_CACHE_HPP_

#include <eda/vhdl/ast/util/position_tagged.hpp>

#include <iosfwd>
#include <optional>
#include <tuple>
#include <type_traits>
#include <vector>

#include <boost/range/iterator_range.hpp>
#include <boost/core/ignore_unused.hpp>

#include <eda/util/cxx_bug_fatal.hpp>

namespace eda {
namespace vhdl {
namespace ast {

/**
 * AST annotation/position cache
 *
 * Mainly acts as manager to map file names to there string contents. These
 * properties are own, hence it's save to refer to them as long the instance
 * exist.
 */
template <typename IteratorT> class position_cache {
public:
    using iterator_type = IteratorT;
    using position_container_type = std::vector<boost::iterator_range<iterator_type>>;

    using range_type = typename position_container_type::value_type;

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
    position_cache& operator=(position_cache const&) = delete;

    position_cache(position_cache&&) = delete;
    position_cache& operator=(position_cache&&) = delete;

public:
    /**
     * Create an annotation/position cache proxy.
     *
     * @param file_id ID of actually processed file.
     * @return A proxy object with fixed file_id for convenience.
     */
    proxy handle(std::size_t file_id);

    std::size_t file_count() const { return files.size(); }
    std::size_t position_count() const { return positions.size(); }

public:
    /**
     * Maps a filename to contents.
     *
     * @param filename The file name as is it's shown e.g. by the error handler
     * @param contents Optional a string holding the file contents
     * @return An ID which identifies the pair of 'filename' and 'contents' which
     *         can be referred later on using the proxy.
     */
    std::size_t add_file(std::string filename, std::string contents = std::string{})
    {
        std::size_t const file_id = files.size();
        files.emplace_back(std::move(filename), std::move(contents));
        return file_id;
    }

public:
    /**
     * Annotate the AST node with positional iterators.
     *
     * @param file_id ID of actually processed file.
     * @param node    The AST node to tag
     * @param first      Begin of iterator position to tag.
     * @param last    End  of iterator position to tag.
     */
    template <typename NodeT>
    void annotate(std::size_t file_id, NodeT& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            /* ToDo: maybe better throw range_exception since it's an implementation
             * limitation. */
            cxx_assert(positions.size() < ast::position_tagged::MAX_ID,
                "Insufficient range of numeric IDs for AST tagging");

            node.file_id = file_id;
            node.pos_id = positions.size();
            positions.emplace_back(first, last);
        } else { // ignore
            // ... but make gcc quiet
            boost::ignore_unused(file_id);
            boost::ignore_unused(first);
            boost::ignore_unused(last);
        }
    }

public:
    /**
     * Get the file name.
     *
     * @param file_id ID of actually processed file.
     * @return The filename as std::string.
     */
    std::string const& file_name(std::size_t file_id) const
    {
        return std::get<0>(files.at(file_id));
    }

    /**
     * Get the file contents.
     *
     * @param file_id ID of actually processed file.
     * @return A const reference to a string representing the file contents.
     */
    std::string const& file_contents(std::size_t file_id) const
    {
        return std::get<1>(files.at(file_id));
    }

    /**
     * Get the file contents.
     *
     * @param file_id ID of actually processed file.
     * @return A reference to a string representing the file contents.
     */
    std::string& file_contents(std::size_t file_id)
    {
        // clang-format off
        return std::get<1>(files.at(file_id));
        // clang-format on
    }

    /**
     * Get the iterator (range) of the file contents.
     *
     * @param file_id ID of actually processed file.
     * @return A pair of iterators pointing to begin and end of the file contents.
     */
    std::tuple<iterator_type, iterator_type> range(std::size_t file_id) const
    {
        auto const make_range = [](std::string const& contents) {
            return std::tuple<iterator_type, iterator_type>{ contents.begin(), contents.end() };
        };

        return make_range(file_contents(file_id));
    }

    /**
     * Extract the iterator range from AST tagged node.
     *
     * @param node The AST node.
     * @return boost::iterator_range tagged before by \ref annotate. If the node
     *         not tagged an empty iterator_range is return. To distinguish
     *         between they are packed into an optional.
     */
    template <typename NodeT> std::optional<range_type> position_of(NodeT const& node) const
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            return positions[node.pos_id];
        }

        return {};
    }

public:
    /**
     * Return the line number of a given iterator position. The position must
     * be within the position cache range.
     *
     * @param file_id ID of actually processed file.
     * @param pos Iterator position where to gather the line number.
     * @return The line number.
     */
    std::size_t line_number(std::size_t file_id, iterator_type const& pos) const;

    /**
     * Return an iterator to the begin of the line. White spaces are skipped.
     * The position must be within the position cache range.
     * \note For this, the pos_iter is modified.
     *
     * @param file_id ID of actually processed file.
     * @param pos Iterator position pointing to a line of interest.
     * @return Iterator position pointing to the begin of line.
     */
    iterator_type get_line_start(std::size_t file_id, iterator_type& pos) const;

    /**
     * Print the line where the iterator points to until end-of-line.
     *
     * @param file_id ID of actually processed file.
     * @param first Iterator position pointing to a line of interest.
     * @return String representing the source line.
     */
    std::string current_line(std::size_t file_id, iterator_type const& first) const;

private:
    // clang-format off
    file_container_type                             files;
    position_container_type                         positions;
    // clang-format on
};

/**
 * AST annotation/position cache proxy.
 *
 * This gives the same API as position_cache, but with an ID bound to this proxy
 * to simplify AST tagging and error_handling.
 *
 * \note This class is intended to created by the position_cache's handle()
 * function only.
 */
template <typename IteratorT> class position_cache<IteratorT>::proxy {
public:
    proxy(position_cache<IteratorT>& position_cache_, std::size_t file_id_)
        : self{ position_cache_ }
        , file_id{ file_id_ }
    {
    }

public:
    std::size_t id() const { return file_id; }

public:
    template <typename NodeT> void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        self.annotate(file_id, node, first, last);
    }

public:
    template <typename NodeT> std::optional<range_type> position_of(NodeT const& node) const
    {
        return self.position_of(node);
    }

public:
    std::string const& file_name() const { return self.file_name(file_id); }
    std::string const& file_contents() const { return self.file_contents(file_id); }
    std::tuple<IteratorT, IteratorT> range() const { return self.range(file_id); }

public:
    std::size_t line_number(iterator_type const& pos) const
    {
        return self.line_number(file_id, pos);
    }

    iterator_type get_line_start(iterator_type& pos_iter) const
    {
        return self.get_line_start(file_id, pos_iter);
    }

    std::string current_line(iterator_type const& start) const
    {
        return self.current_line(file_id, start);
    }

private:
    // clang-format off
    position_cache<IteratorT>&                      self;
    std::size_t const                               file_id;
    // clang-format on
};

template <typename IteratorT>
typename position_cache<IteratorT>::proxy position_cache<IteratorT>::handle(std::size_t file_id)
{
    return proxy{ *this, file_id };
}

} // namespace ast
} // namespace vhdl
} // namespace eda

#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_POSITION_CACHE_HPP_ */
