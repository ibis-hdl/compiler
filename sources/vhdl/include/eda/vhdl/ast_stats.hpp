/*
 * ast_stats.hpp
 *
 *  Created on: 15.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STATS_HPP_
#define SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STATS_HPP_

#include <eda/vhdl/ast_fwd.hpp>

#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <iosfwd>


namespace eda { namespace vhdl { namespace ast {


class ast_stats
{
public:
	ast_stats(ast::design_file const& design_file);

	auto sort_by_count(bool ascending = true) const;

    std::ostream& print(std::ostream& os) const;

private:
    typedef std::unordered_map<std::string_view, std::size_t> map_type;
    typedef std::unordered_set<std::string_view> 	set_type;

private:
    map_type 										count_map;
    set_type 										untagged_nodes;
};


static inline
std::ostream& operator<<(std::ostream& os, ast_stats const& stats) {
    return stats.print(os);
}


} } } // namespace eda.vhdl.ast



#endif /* SOURCES_VHDL_INCLUDE_EDA_VHDL_AST_STATS_HPP_ */
