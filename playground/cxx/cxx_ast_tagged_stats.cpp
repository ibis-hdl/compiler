/*
 * cxx_ast_tagged_stats.cpp
 *
 *  Created on: 21.07.2018
 *      Author: olaf
 */

#include <iostream>

#include <optional>
#include <string_view>
#include <map>
#include <vector>
#include <algorithm>

namespace ast {

struct position_tagged { };

struct foo : position_tagged { };
struct bar { };
struct baz : position_tagged { };

} // namespace ast



struct tag_data
{
    typedef std::map<std::string_view, std::size_t> map_type;
    typedef map_type::iterator                      iterator_type;
    typedef map_type::value_type                    value_type;

    void tagged(std::string_view const& node_name) {
        ++tagged_map[node_name];
    }

    void untagged(std::string_view const& node_name) {
        ++untagged_map[node_name];
    }

    // Todo: - tag dispatch {ascending, descending} sorted
    //       - variadic template to allow sort(tagged, untagged)
    auto sort(map_type const& map) const {
#if 0
        // XXX doesn't compile
        typedef map_type::value_type pair_type;
#else
        // ok, compiles with mutable keys
        typedef std::pair<map_type::key_type, map_type::mapped_type> pair_type;
#endif
        std::vector<pair_type> vec;
        vec.reserve(map.size());

        std::copy(map.begin(), map.end(),
                  std::back_inserter<std::vector<pair_type>>(vec));

        std::sort(vec.begin(), vec.end(),
                  [](pair_type const& lhs, pair_type const& rhs) {
                        if (lhs.second != rhs.second)
                            return lhs.second < rhs.second; // sort-by-value
                        return lhs.first < rhs.first;       // sort-by-key otherwise
                  });
        return vec;
    }

    map_type                                        tagged_map;
    map_type                                        untagged_map;
};


struct tagged_visitor
{
    tagged_visitor(tag_data& data_)
    : data{ data_ }
    { }

    template<typename NodeT>
    void count(NodeT const&, std::string_view const& node_name) const {
        if constexpr (std::is_base_of_v<ast::position_tagged, std::remove_reference_t<NodeT>>) {
            data.tagged(node_name);
        }
        else {
            data.untagged(node_name);
        }
    }

    void operator()(ast::foo const& node) const {
        static char const symbol[]{ "foo" };
        count(node, symbol);
    }
    void operator()(ast::bar const& node) const {
        static char const symbol[]{ "bar" };
        count(node, symbol);
    }
    void operator()(ast::baz const& node) const  {
        static char const symbol[]{ "baz" };
        count(node, symbol);
    }

    tag_data&                              data;
};

struct tagged_stats
{
    tagged_stats(tag_data& data)
    : data{ data }
    { }

    void print_map(tag_data::map_type& map) const {
        auto const sorted = data.sort(map);
        for (auto const& node : sorted) {
            std::cout << node.first << ": " << node.second << "\n";
        }
    }

    void tagged() const {
        std::cout << "Tagged:\n";
        print_map(data.tagged_map);
        std::cout << "\n";
    }

    void untagged() const {
        std::cout << "UnTagged:\n";
        print_map(data.untagged_map);
        std::cout << "\n";
    }

    tag_data&                              data;
};

struct statistic
{
    statistic()
    : visitor{ map }
    , stats{ map }
    { }

    template<typename NodeT>
    void operator()(NodeT const& node) const {
        visitor(node);
    }

    void print() const {
        stats.tagged();
        stats.untagged();
    }

    tag_data                                map;
    tagged_visitor                          visitor;
    tagged_stats                            stats;
};


int main()
{
    ast::foo foo;
    ast::bar bar;
    ast::baz baz;

    statistic stats;
    stats(foo);
    stats(foo);
    stats(bar);
    stats(baz);
    stats.print();
}
