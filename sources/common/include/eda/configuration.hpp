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
class configuration
{
public:
    typedef std::optional<std::string> config_value;

    class option_trigger;

public:
    configuration() = default;
    configuration(configuration const&) = delete;
    configuration const& operator=(configuration const&) = delete;

public:
    config_value const& operator[](std::string const& option_name) const {

        map_type& map_ = const_cast<map_type&>(this->map);

        if (map.count(option_name) > 0) {
            return map_[option_name];
        }
        return none;
    }


    config_value& operator[](std::string const& option_name) {
        return map[option_name];
    }


    void dump(std::ostream& os) const;


    /** Trim leading '--' chars from key to get better hashes. */
    static  inline
    std::string trim(std::string const& key) {

        // FixMe: C++20 starts_with()
        std::string const prefix{ "--" };
        if(key.substr(0, prefix.size()) == prefix) {
            return key.substr(prefix.size());
        }
        return key;
    };

private:
    typedef std::unordered_map<std::string, config_value> map_type;
    map_type                                        map;
    static const config_value                       none;
};


class configuration::option_trigger
{
    std::unordered_map<std::string, std::vector<std::string>> triggers;

public:
    option_trigger() = default;
    option_trigger(option_trigger const&) = delete;
    option_trigger const& operator=(option_trigger const&) = delete;

public:

    void add(std::string const& primary_option, std::vector<std::string> const& secondary_options) {
        triggers[primary_option] = secondary_options;
    }

    void update(configuration& config);
};


} // namespace eda


#endif /* SOURCES_COMMON_INCLUDE_EDA_CONFIGURATION_HPP_ */
