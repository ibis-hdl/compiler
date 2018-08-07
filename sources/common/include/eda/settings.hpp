/*
 * settings.hpp
 *
 *  Created on: 01.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SETTINGS_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SETTINGS_HPP_

#include <unordered_map>
#include <string>
#include <optional>
#include <vector>
#include <iosfwd>

#include <iostream>

namespace eda {


/**
 * Runtime setting options
 *
 * Example:
 * \code
 * settings config;
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
 * \see Concept on [Wandbox](https://wandbox.org/permlink/0NrHlKXbw77zAOn0)
 */
class settings
{
public:
    typedef std::optional<std::string> 				option_value;

    class option_trigger;

public:
    settings() = default;
    settings(settings const&) = delete;
    settings const& operator=(settings const&) = delete;

public:
	/**
	 * Return the value as std::optional<> of the defined option.
	 *
	 * \param  option_name  The name of the option to lookup in the trimmed form.
	 * \return config_value If the option has been defined before, the value
	 *                      as reference to optional<string>, otherwise to an
	 *                      empty optional<>.
	 */
    option_value const& operator()(std::string const& option_name) const {

    	map_type& map_ = const_cast<map_type&>(this->map);

        if (exist(option_name)) {
            return map_[option_name];
        }
        return none;
    }


    /**
     * Lookup the configuration map for writing, the option_name is trimmed,
     * means the leading chars '--' are remove to get better hashes. If the
     * option_name doesn't exist it's inserted, otherwise the a reference
     * to the stored config_value is returned.
     * Hence, it behaves as the std::map[].
     *
     * \param  option_name  The name of the option to lookup in the trimmed form.
     * \return config_value The value as reference to optional<string>.
     */
    option_value& operator[](std::string const& option_name) {

        return map[trim(option_name)];
    }


    /**
     * Check on existence of the option.
     *
     * \param  option_name The name of the option to test.
     * \return true if the option has been defined, otherwise false.
     */
    bool exist(std::string const& option_name) const {
    	return map.count(option_name) > 0;
    }

    /**
     * Dump the configuration stored in sorted form
     * \param os The ostream to dump.
     */
    void dump(std::ostream& os) const;

private:
    /** Trim leading '--' chars from key. */
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
    typedef std::unordered_map<std::string, option_value> map_type;
    map_type                                        map;
    static const option_value                       none;
};


class settings::option_trigger
{
    std::unordered_map<std::string, std::vector<std::string>> trigger;

public:
    option_trigger() = default;
    option_trigger(option_trigger const&) = delete;
    option_trigger const& operator=(option_trigger const&) = delete;

public:
    /**
     * Simplifies depending configuration options, binds the secondary_options
     * to the primary_option. Only boolean options are possible.
     *
     * \param primary_option    The option which triggers depending options.
     * \param secondary_options The depending options.
     */
    void add(std::string const& primary_option, std::vector<std::string> const& secondary_options) {
        trigger[primary_option] = secondary_options;
    }

    /**
     * Update the configuration map, if the primary_option is stored in the
     * config all depending options are added.
     *
     * \param config The configuration map.
     */
    void update(settings& config);
};


} // namespace eda


#endif /* SOURCES_COMMON_INCLUDE_EDA_SETTINGS_HPP_ */
