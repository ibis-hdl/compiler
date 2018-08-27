/*
 * settings.cpp
 *
 *  Created on: 01.08.2018
 *      Author: olpetzol
 */

#include <eda/settings.hpp>

#include <eda/util/string/icompare.hpp>
#include <eda/support/cxx/overloaded.hpp>
#include <vector>

#include <iostream>


namespace eda {


void settings::dump(std::ostream& os) const
{
	using key_type = map_type::key_type;
	using value_type = map_type::mapped_type;
	using pair_type = std::pair<key_type, value_type>;
	using vector_type = std::vector<pair_type>;

	vector_type vec{map.begin(), map.end()};

	std::sort(vec.begin(), vec.end(), [](pair_type const& p1, pair_type const& p2) {
        return util::icompare_less(p1.first, p2.first);
        });

    os << "(settings [N=" << vec.size() << "]\n";
    for (auto const& [option_name, val] : vec) {
        os << "    " << option_name << ": ";
		std::visit(util::overloaded {
			[&os](std::monostate) { os << "N/A"; },
			[&os](bool v) { os << std::boolalpha << v; },
			[&os](long v) { os << v; },
			[&os](std::string const& v) { os <<v; },
			[&os](std::vector<std::string> const& v) {
				for (auto const& e : v) {
					os << e << ", ";
				}
			},
		}, val);
        os << "\n";
    }
    os << ")\n";
}


const settings::option_value settings::none;


} // namespace eda
