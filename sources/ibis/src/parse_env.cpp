/*
 * parse_env.cpp
 *
 *  Created on: 01.08.2018
 *      Author: olaf
 */

#include <eda/configuration.hpp>

#include <eda/support/boost/locale.hpp>

#include <cstdlib>


void parse_env(eda::configuration& config)
{
    auto const getenv = [](std::string const& key) {
        char * val = std::getenv( key.c_str() );
        return val == NULL ? std::string{} : std::string(val);
    };

    // pure ENV name used for configuration
    auto const set_option = [&](std::string const& env_name) {
        std::string const env_var{ getenv(env_name) };
        if (!env_var.empty()) {
            config[env_name] = env_var;
        }
    };

    // key used for configuration to allow overriding them on command line
    auto const set_option_key = [&](std::string const& env_name, std::string const& key_name) {
        std::string const env_var{ getenv(env_name) };
        if (!env_var.empty()) {
            config[key_name] = env_var;
        }
    };

    set_option("HOME");
    set_option_key("EDA_LIBPATH", "libpath");
}
