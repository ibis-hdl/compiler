/*
 * position_cache.hpp
 *
 *  Created on: 18.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_

#include <eda/vhdl/ast/util/position_tagged.hpp>
#include <eda/utils/cxx_bug_fatal.hpp>

#include <boost/range/iterator_range.hpp>
#include <vector>
#include <tuple>
#include <optional>
#include <type_traits>

#include <eda/utils/pretty_typename.hpp>


namespace eda { namespace vhdl { namespace parser {


/*
 * Annotation and Error handling
 *
 * ToDo: Documentation
 */
template <typename IteratorT, typename ContainerT = std::vector<boost::iterator_range<IteratorT>>>
class position_cache
{
public:

    typedef IteratorT                               iterator_type;
    typedef ContainerT                              container_type;
    typedef typename container_type::value_type     range_type;

public:
    position_cache(std::string const& range_)
    : range{ std::begin(range_), std::end(range_) }
    { }

    position_cache(iterator_type first, iterator_type last)
    : range{ std::move(first), std::move(last) }
    { }

public:
    template <typename NodeT>
    void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            std::cout << "position_cache::annotate<"
                      << utils::pretty_typename<NodeT>{}
                      << "> with ID = "
                      << positions.size() << "\n";

            /* ToDo: maybe better throw range_exception since it's an implementation
             * limitation. */
            cxx_assert(positions.size() < ast::position_tagged::MAX_ID,
                      "Insufficient range of numeric IDs for AST tagging");

            node.pos_id = positions.size();
            positions.emplace_back( first, last );
        }
        else { /* ignore */ }
    }

public:
#if 1
    template <typename NodeT>
    range_type position_of(NodeT const& node) const
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            std::cout << "position_of<tagged>("
                      << utils::pretty_typename<NodeT>{}
                      << ")\n";
            return positions[node.pos_id];
        }
        else {
            std::cout << "position_of<**NOT**tagged>("
                      << utils::pretty_typename<NodeT>{}
                      << ")\n";
            return range_type{};
        }
    }
#else
    template <typename NodeT>
    std::optional<std::tuple<iterator_type, iterator_type>>
    position_of(NodeT const& node) const
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            std::cout << "position_of<tagged>("
                      << utils::pretty_typename<NodeT>{}
                      << ")\n";
            // assert(node.pos_id != ast::position_tagged::MAX_ID)
            // assert(node.pos_id <= positions.size());
            auto const& range = positions[node.pos_id];
            return { range.begin(), range.end()) };
        }
        else {
            std::cout << "position_of<**NOT**tagged>("
                      << utils::pretty_typename<NodeT>{}
                      << ")\n";
            return {};
        }
    }
#endif
public:
    std::tuple<iterator_type, iterator_type> iterator_range() const
    {
        return std::tuple{ range.begin(), range.end() };
    }

    iterator_type first() const       { return range.begin(); }
    iterator_type const& last() const { return range.end(); }

private:
    container_type                                  positions;
    range_type                                      range;
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_ */
