#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <iosfwd>

namespace ibis::vhdl::ast {
struct design_file;
}

namespace ibis::vhdl::ast {

class ast_stats {
public:
    ast_stats(ast::design_file const& design_file);

    auto sort_by_count(bool ascending = true) const;

    std::ostream& print(std::ostream& os) const;

private:
    using map_type = std::unordered_map<std::string_view, std::size_t>;
    using set_type = std::unordered_set<std::string_view>;

private:
    map_type count_map;
    set_type untagged_nodes;
};

static inline std::ostream& operator<<(std::ostream& os, ast_stats const& stats)
{
    return stats.print(os);
}

}  // namespace ibis::vhdl::ast
