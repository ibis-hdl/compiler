/*
 * settings.hpp
 *
 *  Created on: 01.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_COMMON_INCLUDE_EDA_SETTINGS_HPP_
#define SOURCES_COMMON_INCLUDE_EDA_SETTINGS_HPP_

#include <eda/support/cxx/overloaded.hpp>

#include <iosfwd>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace eda {

/**
 * Runtime setting options
 *
 * Example:
 * \code
 * setting config;
 *
 * config.set("-Fbool", true);
 * config.set("-Fstrg", std::string{"string"});
 * config.set("-Fvec", std::vector<std::string>{"foo", "bar"});
 *
 * setting::option_trigger trigger;
 * trigger.add("-Fbool", {"-fFoo", "-Fbar"});
 * trigger.update(config);
 *
 * config.dump(std::cout);
 *
 * if (config["-Fbool"]) {
 *     std::cout << "Yeah, -Fbool is active\n";
 * }
 *
 * if (config.exist("-Fstrg")) {
 *     std::cout << "-Fstring: " << config["-Fstrg"].get<std::string>() << '\n';
 * }
 * \endcode
 *
 * \see Concept on [Wandbox](https://wandbox.org/permlink/4rfFaViNE5tGZg4v)
 */
class settings {
public:
    using option_value = std::variant<
        std::monostate,
        bool,
        long,
        std::string,
        std::vector<std::string>>;

public:
    settings() = default;
    ~settings() = default;

    settings(settings const&) = delete;
    settings const& operator=(settings const&) = delete;

    settings(settings&&) = delete;
    settings const& operator=(settings&&) = delete;

public:
    class option_trigger;

    struct option_value_proxy {
        option_value_proxy(settings::option_value const& option_value_)
            : option_value{ option_value_ }
        {
        }

        option_value_proxy() = delete;
        ~option_value_proxy() = default;

        option_value_proxy(option_value_proxy const&) = delete;
        option_value_proxy& operator=(option_value_proxy const&) = delete;

        option_value_proxy(option_value_proxy&&) = delete;
        option_value_proxy& operator=(option_value_proxy&&) = delete;

        operator bool() const
        {
            // clang-format off
            return std::visit(util::overloaded{
                // <long> is (implicit converted) handled as boolean, as intended
                [](bool option) { return option; },
                [](std::string const& option) { return !option.empty(); },
                [](std::vector<std::string> const& option) { return !option.empty(); },
                [](std::monostate) { return false; },
            }, this->option_value);
            // clang-format on
        }

        template <typename T>
        T const& get() const
        {
            // bad_variant_access thrown on invalid accesses to the value
            return std::get<T>(option_value);
        }

        // clang-format off
        settings::option_value const&               option_value;
        // clang-format on
    };

public:
    /**
     * Return the value as std::optional<> of the defined option.
     *
     * \param  option_name  The name of the option to lookup in the trimmed form.
     * \return proxy        If the option has been defined before, the value
     *                      as reference to optional<string>, otherwise to an
     *                      empty optional<>.
     */
    option_value_proxy const operator[](std::string const& option_name) const
    {
        // const_cast<> required to get the intended API behavior (don't insert
        // a key if not found as the default behavior of std::map)
        auto map_ = const_cast<map_type&>(this->map);
        if (exist(option_name)) {
            return option_value_proxy{ map_[option_name] };
        }

        return option_value_proxy{ none };
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
    template <typename T>
    void set(std::string_view option_name, T&& value)
    {
        using type = std::remove_reference_t<T>;
        map[trim(option_name)].emplace<type>(std::forward<T>(value));
        //map[trim(option_name)] = std::forward<type>(value);
    }

    /**
     * Check on existence of the option.
     *
     * \param  option_name The name of the option to test.
     * \return true if the option has been defined, otherwise false.
     */
    bool exist(std::string const& option_name) const
    {
        return map.count(option_name) > 0;
    }

    /**
     * Dump the configuration stored in sorted form
     * \param os The ostream to dump.
     */
    void dump(std::ostream& os) const;

private:
    /** Trim leading '--' chars from key. */
    static inline std::string trim(std::string_view key)
    {
        // FixMe: C++20 starts_with()
        std::string_view const prefix{ "--" };
        if (key.substr(0, prefix.size()) == prefix) {
            return std::string{ key.substr(prefix.size()) };
        }
        return std::string{ key };
    }

private:
    using map_type = std::unordered_map<std::string, option_value>;

    // clang-format off
    map_type                                        map;
    static const option_value                       none;
    // clang-format on
};

/**
 * Settings option trigger.
 *
 * Add (secondary) boolean flags to the settings repository if the primary
 * option is set.
 */
class settings::option_trigger {
    using trigger_map_type = std::unordered_map<
        std::string, std::vector<std::string>>;

    trigger_map_type trigger;

public:
    option_trigger() = default;
    ~option_trigger() = default;

    option_trigger(option_trigger const&) = delete;
    option_trigger const& operator=(option_trigger const&) = delete;

    option_trigger(option_trigger&&) = delete;
    option_trigger const& operator=(option_trigger&&) = delete;

public:
    /**
     * Simplifies depending configuration options, binds the secondary_options
     * to the primary_option. Only boolean options are possible.
     *
     * \param primary_option    The option which triggers depending options.
     * \param secondary_options The depending options.
     */
    void add(std::string const& primary_option, std::vector<std::string> const& secondary_options)
    {
        trigger[primary_option] = secondary_options;
    }

    /**
     * Update the configuration map, if the primary_option is stored in the
     * config all depending options are added.
     *
     * \param config The configuration map.
     */
    void update(settings& config) const
    {
        for (auto const & [ primary_option, secondary_options ] : trigger) {
            if (!config.exist(trim(primary_option))) {
                continue;
            }
            for (auto const& option : secondary_options) {
                config.set(option, true);
            }
        }
    }
};

} // namespace eda

#endif /* SOURCES_COMMON_INCLUDE_EDA_SETTINGS_HPP_ */
