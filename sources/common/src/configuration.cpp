/*
 * options.cpp
 *
 *  Created on: 01.08.2018
 *      Author: olpetzol
 */

#include <eda/configuration.hpp>

#include <iostream>


namespace eda {


void configuration::dump(std::ostream& os) const
{
    os << "(configuration\n";
	for (auto const& [option_name, val] : map) {
		os << "    (" << option_name << " = " << *val << ")\n";
	}
    os << ")\n";
}


void configuration::option_trigger::update(configuration& config)
{
    auto const trim = [](std::string const& key) {
        return configuration::trim(key);
    };

    for(auto [primary_option, secondary_options] : triggers) {

    	config.map[trim(primary_option)] = "true";

    	for(auto option : secondary_options) {
            config.map[trim(option)] = "true";
        }
    }
}


const configuration::config_value configuration::none;

} // namespace eda
