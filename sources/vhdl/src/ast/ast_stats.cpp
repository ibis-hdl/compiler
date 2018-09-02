/*
 * ast_stats.cpp
 *
 *  Created on: 15.08.2018
 *      Author: olaf
 */

#include <eda/vhdl/ast/ast_stats.hpp>

#include <eda/vhdl/ast/basic_ast_walker.hpp>

#include <algorithm>
#include <vector>
#include <iostream>


namespace eda { namespace vhdl { namespace ast {

namespace detail {


struct collect_worker
{
    using map_type = std::unordered_map<std::string_view, std::size_t>;
    using set_type = std::unordered_set<std::string_view>;

    collect_worker(map_type& count_map_, set_type& untagged_node_)
    : count_map{ count_map_ }
    , untagged_node{ untagged_node_ }
    {}

    template<typename NodeT>
    void operator()(NodeT const& /*unused*/, std::string_view const& node_name) const {

        ++count_map[node_name];

        if constexpr (!std::is_base_of_v<ast::position_tagged, std::decay_t<NodeT>>) {
            untagged_node.insert(node_name);
        }
    }

    map_type&                           count_map;
    set_type&                           untagged_node;
};


} // namespace detail



ast_stats::ast_stats(ast::design_file const& design_file) {

    using worker = ast::basic_ast_walker<detail::collect_worker>;

    worker collector { count_map, untagged_nodes };
    collector(design_file);
}


auto ast_stats::sort_by_count(bool ascending) const {

    using pair_type = std::pair<map_type::key_type, map_type::mapped_type>;

    auto const ascending_predicate =
            [](pair_type const& lhs, pair_type const& rhs) {
                if (lhs.second != rhs.second) {
                return lhs.second < rhs.second; // sort-by-value
}
                return lhs.first < rhs.first;    // sort-by-key otherwise
            };

    auto const descending_predicate =
            [](pair_type const& lhs, pair_type const& rhs) {
                if (lhs.second != rhs.second) {
                return lhs.second > rhs.second; // sort-by-value
}
                return lhs.first < rhs.first;    // sort-by-key otherwise
            };

    std::vector<pair_type> vec { count_map.begin(), count_map.end() };
    auto const predicate =
            ascending ? ascending_predicate : descending_predicate;
    std::sort(vec.begin(), vec.end(), predicate);

    return vec;
}


std::ostream& ast_stats::print(std::ostream& os) const {
    auto const vec { sort_by_count() };

    std::size_t const max_key_size = [&] {

        std::size_t size {0};
        std::for_each(vec.begin(), vec.end(),
                [&size](auto const& pair) {
                    size = std::max(size, pair.first.size());
                }
        );
        return size;
    }();

    std::string const padding(max_key_size, ' ');
    std::size_t total_count { 0 };

    for (auto const& [key, value] : vec) {
        os << key
        << std::string_view(padding).substr(0, max_key_size - key.size());

        if (untagged_nodes.count(key) != 0) {
            os << " T";    // position_tagged
        }
        else {
            os << "  ";    // not position_tagged
        }

        os << " : " << value << '\n';

        total_count += value;
    }

    os << "\nTotal node count = " << total_count;
    return os;
}


} } } // namespace eda.vhdl.ast

