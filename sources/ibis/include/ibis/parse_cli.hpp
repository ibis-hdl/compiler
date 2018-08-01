/*
 * cli_options.hpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#ifndef SOURCES_IBIS_INCLUDE_IBIS_PARSE_CLI_HPP_
#define SOURCES_IBIS_INCLUDE_IBIS_PARSE_CLI_HPP_

#include <string>
#include <vector>

namespace eda {
    struct configuration;
}

std::vector<std::string> parse_cli(int argc, const char* argv[], eda::configuration& config);



#endif /* SOURCES_IBIS_INCLUDE_IBIS_PARSE_CLI_HPP_ */
