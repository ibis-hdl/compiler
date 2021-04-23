#include <ibis/vhdl/ast/ast_stats.hpp>

#include <ibis/vhdl/ast/basic_ast_walker.hpp>

#include <functional>
#include <utility>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

namespace ibis::vhdl::ast {
struct position_tagged;
}

namespace ibis::vhdl::ast {

namespace detail {

class collect_worker {
public:
    using map_type = std::unordered_map<std::string_view, std::size_t>;
    using set_type = std::unordered_set<std::string_view>;

    collect_worker(map_type& count_map_, set_type& untagged_node_)
        : count_map{ count_map_ }
        , untagged_node{ untagged_node_ }
    {
    }

    template <typename NodeT>
    void operator()([[maybe_unused]] NodeT const& node, std::string_view node_name) const
    {
        ++count_map[node_name];

        if constexpr (!std::is_base_of_v<ast::position_tagged, std::decay_t<NodeT>>) {
            untagged_node.insert(node_name);
        }
    }

private:
    map_type& count_map;
    set_type& untagged_node;
};

}  // namespace detail

ast_stats::ast_stats(ast::design_file const& design_file)
{
    using worker = ast::basic_ast_walker<detail::collect_worker>;

    worker collector{ count_map, untagged_nodes };
    collector(design_file);
}

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

    // FixMe: Conside use of std::set since it's sorted by C++ std.
    std::vector<pair_type> vec{ count_map.begin(), count_map.end() };
    std::sort(vec.begin(), vec.end(), predicate);

    return vec;
}

std::ostream& ast_stats::print(std::ostream& os) const
{
    auto const vec{ sort_by_count() };

    std::size_t const max_key_size = [&] {
        std::size_t size{ 0 };
        std::for_each(vec.begin(), vec.end(),
                      [&size](auto const& pair) { size = std::max(size, pair.first.size()); });
        return size;
    }();

    std::string const padding(max_key_size, ' ');
    std::size_t total_count{ 0 };

    for (auto const& [key, value] : vec) {
        os << key << std::string_view(padding).substr(0, max_key_size - key.size());

        if (untagged_nodes.count(key) != 0) {
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
