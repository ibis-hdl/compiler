/*
 * position_cache.hpp
 *
 *  Created on: 18.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/util/cxx_bug_fatal.hpp>

#include <boost/range/iterator_range.hpp>
#include <vector>
#include <tuple>
#include <optional>
#include <type_traits>

#include <boost/core/ignore_unused.hpp>

//#include <eda/util/pretty_typename.hpp>


namespace eda { namespace vhdl { namespace parser {


/**
 * AST annotation/position cache
 */
template <typename IteratorT, typename ContainerT = std::vector<boost::iterator_range<IteratorT>>>
class position_cache
{
public:

    typedef IteratorT                               iterator_type;
    typedef ContainerT                              container_type;
    typedef typename container_type::value_type     range_type;

public:
    position_cache(std::string const& range)
    : begin{ std::move(range.begin()) }
    , end{ std::move(range.end()) }
    { }

public:
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            /* ToDo: maybe better throw range_exception since it's an implementation
             * limitation. */
            cxx_assert(positions.size() < ast::position_tagged::MAX_ID,
                      "Insufficient range of numeric IDs for AST tagging");

            node.pos_id = positions.size();
            positions.emplace_back(first, last);
        }
        else { // ignore
        	// ... but make gcc happy
        	boost::ignore_unused(first);
        	boost::ignore_unused(last);
        }
    }

public:
    template <typename NodeT>
    // XXX make optional<range_type> ???
    range_type position_of(NodeT const& node) const
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            return positions[node.pos_id];
        }
        else {
            return range_type{};
        }
    }
public:
    /**
     * Return the line number of a given iterator position. The position must
     * be within the position cache range.  */
    std::size_t line_number(iterator_type const& pos) const;

    /**
     * Return an iterator to the begin of the line. White spaces are skipped.
     * For this, the ´pos_iter´ is modified.
     * The position must be within the position cache range. */
    iterator_type get_line_start(iterator_type& pos_iter) const;

    /**
     * Print the line where the iterator points to until end-of-line. */
    std::string current_line(iterator_type const& start) const;

private:
    container_type                                  positions;
    iterator_type const                             begin;
    iterator_type const                             end;
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_ */
