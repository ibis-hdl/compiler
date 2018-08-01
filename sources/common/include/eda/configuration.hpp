/*
 * configuration.hpp
 *
 *  Created on: 01.08.2018
 *      Author: olpetzol
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_CONFIGURATION_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_CONFIGURATION_HPP_

#include <unordered_map>
#include <string>
#include <optional>
#include <vector>
#include <iosfwd>


namespace eda {


/**
 * Runtime configuration options
 *
 * Example:
 * \code
 * configuration config;
 * option_trigger trigger;
 *
 * trigger.add("-Wall", { "-Wunused", "-Wother" });
 * trigger.update(config);
 * config.dump(std::cout);
 *
 *  auto const o = config("-Wall");
 *  std::cout << Warning All: ";
 *  if (o) { std::cout << "<< *o << "\n"; }
 '  else  {  std::cout << "" << "false\n";}
 * \endcode
 *
 * \see [Wandbox](https://wandbox.org/permlink/0NrHlKXbw77zAOn0)
 */
struct configuration
{
    typedef std::optional<std::string> config_value;

    std::unordered_map<std::string, config_value> map;
    static const config_value none;

    config_value const& operator[](std::string const& option_name) {
        if (map.count(option_name) > 0) {
            return map[option_name];
        }
        else {
            return none;
        }
    }

    void dump(std::ostream& os) const;

    /** Trim leading '--' chars from key to get better hashs. */
    static  inline
    std::string trim(std::string const& key) {
        // FixMe: C++20 starts_with()
        std::string const prefix{ "--" };
        if(key.substr(0, prefix.size()) == prefix) {
            return key.substr(prefix.size());
        }
        return key;
    };
};


struct option_trigger
{
    std::unordered_map<std::string, std::vector<std::string>> triggers;

    void add(std::string const& primary_option, std::vector<std::string> const& secondary_options) {
        triggers[primary_option] = secondary_options;
    }

    void update(configuration& config);
};


} // namespace eda


#endif /* SOURCES_COMMON_INCLUDE_EDA_CONFIGURATION_HPP_ */
