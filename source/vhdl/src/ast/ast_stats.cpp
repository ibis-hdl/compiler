//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/vhdl/ast/ast_stats.hpp>

#include <ibis/vhdl/ast/basic_ast_walker.hpp>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ranges>
#include <string_view>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace ibis::vhdl::ast {
class position_tagged;
}

namespace ibis::vhdl::ast {

namespace detail {

class stats_worker {
public:
    using map_type = std::unordered_map<std::string_view, std::size_t>;
    using set_type = std::unordered_set<std::string_view>;

private:
    std::reference_wrapper<map_type> ref_count_map;
    std::reference_wrapper<set_type> ref_untagged_node;

public:
    stats_worker(map_type& count_map, set_type& untagged_nodes)
        : ref_count_map{ std::ref(count_map) }
        , ref_untagged_node{ std::ref(untagged_nodes) }
    {
    }

    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& node, std::string_view node_name) const
    {
        ++ref_count_map.get()[node_name];

        if constexpr (!std::is_base_of_v<ast::position_tagged, std::decay_t<NodeT>>) {
            ref_untagged_node.get().insert(node_name);
        }
    }
};

}  // namespace detail

ast_stats::ast_stats(ast::design_file const& design_file)
{
    using stats_walker = ast::basic_ast_walker<detail::stats_worker>;

    stats_walker stats_collector{ count_map, untagged_nodes };
    stats_collector(design_file);
}

// ToDo sort order - use enum sort::{ascending, descending}
auto ast_stats::sort_by_count(bool ascending) const
{
    using pair_type = std::pair<map_type::key_type, map_type::mapped_type>;

    auto const predicate = [](bool ascending_) {
        auto const ascending_predicate = [](pair_type const& lhs, pair_type const& rhs) {
            if (lhs.second != rhs.second) {
                return lhs.second < rhs.second;  // sort-by-value
            }
            return lhs.first < rhs.first;  // sort-by-key otherwise
        };

        auto const descending_predicate = [](pair_type const& lhs, pair_type const& rhs) {
            if (lhs.second != rhs.second) {
                return lhs.second > rhs.second;  // sort-by-value
            }
            return lhs.first < rhs.first;  // sort-by-key otherwise
        };

        if (ascending_) {
            return std::function<bool(pair_type const&, pair_type const&)>{ ascending_predicate };
        }

        return std::function<bool(pair_type const&, pair_type const&)>{ descending_predicate };
    }(ascending);

    std::vector<pair_type> vec{ begin(count_map), end(count_map) };
    std::ranges::sort(vec, predicate);

    return vec;
}

// ToDo [C++20] use std::format, or as member format_to()
std::ostream& ast_stats::print_on(std::ostream& os) const
{
    auto const vec{ sort_by_count() };

    std::size_t const max_key_size = std::ranges::max(  // --
        vec | std::views::transform([](auto const& pair) {
            return pair.first.size();  // count_map's key
        }));

    std::string const padding(max_key_size, ' ');
    std::size_t total_count{ 0 };

    for (auto const& [key, value] : vec) {
        os << key << std::string_view(padding).substr(0, max_key_size - key.size());

        if (untagged_nodes.contains(key)) {
            os << " T";  // position_tagged
        }
        else {
            os << "  ";  // not position_tagged
        }

        os << " : " << value << '\n';

        total_count += value;
    }

    os << "\nTotal node count = " << total_count;
    return os;
}

}  // namespace ibis::vhdl::ast
