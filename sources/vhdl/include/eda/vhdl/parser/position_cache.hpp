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
    void annotate(NodeT&& node, iterator_type first, iterator_type last)
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            std::cout << "position_cache::annotate<"
                      << boost::typeindex::type_id<decltype(node)>().pretty_name()
                      << "> with ID = "
                      << positions.size() << "\n";

            /* ToDo: maybe better throw range_exception since it's an implementation
             * limitation. */
            assert(positions.size() < ast::position_tagged::MAX_ID &&
                   "Insufficient range of numeric IDs for AST tagging");
            node.pos_id = positions.size();
            positions.emplace_back( first, last );
        }
        else { /* ignore */ }
    }

public:
    template <typename NodeT>
    range_type position_of(NodeT const& node) const
    {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            std::cout << "position_of<tagged>("
                      << boost::typeindex::type_id<decltype(node)>().pretty_name()
                      << ")\n";
            return positions[node.pos_id];
        }
        else {
            std::cout << "position_of<**NOT**tagged>("
                      << boost::typeindex::type_id<decltype(node)>().pretty_name()
                      << ")\n";
            return range_type{};
        }
    }

public:
    std::tuple<iterator_type, iterator_type> iterator_range() const
    {
        return std::tuple{ std::begin(range), std::cend(range) };
    }

    iterator_type first() const       { return std::begin(range); }
    iterator_type const& last() const { return std::cend(range); }

private:
    container_type                                  positions;
    range_type                                      range;
};


}}} // namespace eda.vhdl.parser


#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_PARSER_POSITION_CACHE_HPP_ */
