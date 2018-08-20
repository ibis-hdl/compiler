/*
 * cxx_annotation_cache.cpp
 *
 *  Created on: 20.07.2018
 *      Author: olaf
 */

#include <boost/range/iterator_range.hpp>
#include <vector>
#include <tuple>
#include <optional>

#include <type_traits>
#include <boost/type_traits/is_base_of.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <boost/type_index.hpp>


/*
 * https://wandbox.org/permlink/hNcp4xBtC2HnGc6w
 */

namespace ast {

struct position_tagged
{
    typedef std::size_t                             tag_type;

    static constexpr tag_type MAX_ID = std::numeric_limits<tag_type>::max();

    tag_type pos_id{ MAX_ID };
};

struct node_tagged : position_tagged
{
    int dummy;
};


struct node_none
{
    int dummy;
};

}


template <typename IteratorT, typename ContainerT = std::vector<boost::iterator_range<IteratorT>>>
class position_cache
{
public:

    typedef IteratorT                               iterator_type;
    typedef ContainerT                              container_type;
    typedef typename container_type::value_type     range_type;

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

private:
    container_type                                  positions;
};

template<typename IteratorT>
struct writer {
    typedef IteratorT                               iterator_type;

    writer(position_cache<iterator_type>& position_cache_)
    : cache{ position_cache_ }
    {}

    template <typename NodeT>
    void annotate(NodeT&& node, iterator_type const& first, iterator_type const& last)
    {
        cache.annotate(std::forward<NodeT>(node), first, last);
    }

    position_cache<iterator_type>&                   cache;
};

int main()
{
    using iterator_type = std::string::const_iterator;
    std::string input{ "Hello World" };

    position_cache<iterator_type> cache{};

    ast::node_tagged node_tagged{};
    ast::node_none none{};

    writer w{ cache };

    w.annotate(node_tagged, input.begin(), input.end());
    w.annotate(none, input.begin(), input.end());
}


