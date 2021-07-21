#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <vector>
#include <iosfwd>

namespace ibis::vhdl::ast {
struct design_unit;
using design_file = std::vector<ast::design_unit>;
}  // namespace ibis::vhdl::ast

namespace ibis::vhdl::ast {

class ast_stats {
public:
    ast_stats(ast::design_file const& design_file);

    auto sort_by_count(bool ascending = true) const;

    std::ostream& print_on(std::ostream& os) const;

private:
    using map_type = std::unordered_map<std::string_view, std::size_t>;
    using set_type = std::unordered_set<std::string_view>;

private:
    map_type count_map;
    set_type untagged_nodes;
};

inline std::ostream& operator<<(std::ostream& os, ast_stats const& stats)
{
    return stats.print_on(os);
}

}  // namespace ibis::vhdl::ast
