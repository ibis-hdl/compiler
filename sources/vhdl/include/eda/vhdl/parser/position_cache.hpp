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


namespace mpl = boost::mpl;

/*
 * Annotation and Error handling
 *
 * ToDo: Documentation
 * ToDO: Use std::is_same_of or std::is_convertible
 * ToDo: Use functor (or similar) for algorithm working on position_cache, so
 *       position_cache doesn't depend on algorithm nor error_handler
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
    // This will catch all nodes except those inheriting from position_tagged
    template <typename NodeT>
    void annotate(NodeT&, iterator_type, iterator_type, mpl::false_)
    {  }

    // This will catch all nodes inheriting from position_tagged
    void annotate(ast::position_tagged& node, iterator_type first, iterator_type last, mpl::true_)
    {
        std::cout << "position_cache::annotate<"
                  << boost::typeindex::type_id<decltype(node)>().pretty_name()
                  << "> with ID = "
                  << positions.size() << "\n";

        /* ToDo: maybe better throw range_exception since it's an implementation
         * limitation. */
        cxx_assert(positions.size() < ast::position_tagged::MAX_ID,
                   "Insufficient range of numeric IDs for AST tagging");
        node.pos_id = positions.size();
        positions.push_back( {first, last} );
    }

    template <typename NodeT>
    void annotate(NodeT& node, iterator_type first, iterator_type last)
    {
        annotate(node, first, last, boost::is_base_of<ast::position_tagged, NodeT>{});
    }

public:
    // This will catch all nodes inheriting from position_tagged
    range_type position_of(ast::position_tagged const& node) const
    {
        std::cout << "position_of(ast::position_tagged const& node) const" << "\n";
        return positions[node.pos_id];
    }

    // This will catch all nodes except those inheriting from position_tagged
    // returns an empty position
    template <typename NodeT>
    range_type position_of(NodeT const&) const
    {
        std::cout << "position_of(NodeT const&) const" << "\n";
        return range_type{};
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
