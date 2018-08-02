/*
 * options.cpp
 *
 *  Created on: 01.08.2018
 *      Author: olpetzol
 */

#include <eda/configuration.hpp>

#include <eda/util/string/icompare.hpp>
#include <vector>

#include <iostream>


namespace eda {


void configuration::dump(std::ostream& os) const
{
	using key_type = map_type::key_type;
	using value_type = map_type::mapped_type;
	using pair_type = std::pair<key_type, value_type>;
	using vector_type = std::vector<pair_type>;

	vector_type vec{};
	vec.reserve(map.size());
	vec.insert(vec.begin(), map.begin(), map.end());

	std::sort(vec.begin(), vec.end(), [](pair_type const& p1, pair_type const& p2) {
        return util::icompare_less(p1.first, p2.first);
        });

    os << "(configuration [N=" << vec.size() << "]\n";
	for (auto const& [option_name, val] : vec) {
		if (val) {
			os << "    (" << option_name << " = " << *val << ")\n";
		}
		else {
			os << "    (" << option_name << " = " << "Invalid Value" << ")\n";
		}
	}
    os << ")\n";
}


void configuration::option_trigger::update(configuration& config)
{
    for(auto [primary_option, secondary_options] : trigger) {

    	// add to map only if primary_option is given
    	if (!config(trim(primary_option))) {
    		continue;
    	}

    	for(auto option : secondary_options) {
            config[option] = "true";
        }
    }
}


const configuration::config_value configuration::none;

} // namespace eda