#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

#include <eda/support/cxx/overloaded.hpp>  // IWYU pragma: keep

namespace eda {

///
/// Runtime setting options
///
/// Example:
/// \code
/// setting config;
///
/// config.set("-Fbool", true);
/// config.set("-Fstrg", std::string{"string"});
/// config.set("-Fvec", std::vector<std::string>{"foo", "bar"});
///
/// setting::option_trigger trigger;
/// trigger.add("-Fbool", {"-fFoo", "-Fbar"});
/// trigger.update(config);
///
/// config.dump(std::cout);
///
/// if (config["-Fbool"]) {
///    std::cout << "Yeah, -Fbool is active\n";
/// }
///
/// if (config.exist("-Fstrg")) {
///    std::cout << "-Fstring: " << config["-Fstrg"].get<std::string>() << '\n';
/// }
/// \endcode
///
/// \see Concept on [Wandbox](https://wandbox.org/permlink/4rfFaViNE5tGZg4v)
///
class settings {
public:
    using option_value =
        std::variant<std::monostate, bool, long, std::string, std::vector<std::string>>;

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

        settings::option_value const& option_value;
    };

public:
    ///
    /// Return the value as std::optional<> of the defined option.
    ///
    /// \param  option_name  The name of the option to lookup in the trimmed form.
    /// \return proxy        If the option has been defined before, the value
    ///                     as reference to optional<string>, otherwise to an
    ///                     empty optional<>.
    ///
    option_value_proxy const operator[](std::string const& option_name) const
    {
        auto iter = map.find(option_name);
        if (iter != map.end()) {
            // debug_print(option_name, iter->second);
            return option_value_proxy{ iter->second };
        }

        return option_value_proxy{ none };
    }

    ///
    /// Lookup the configuration map for writing, the option_name is trimmed,
    /// means the leading chars '--' are removed to get better names. If the
    /// option_name doesn't exist it's inserted, otherwise the a reference
    /// to the stored config_value is returned; hence, it behaves as the std::map[].
    ///
    /// \param  option_name  The name of the option to lookup in the trimmed form.
    /// \param  value        The value to be stored.
    /// \return config_value The value as reference to optional<string>.
    ///
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
    void set(std::string_view option_name, T value)
    {
        map[trim(option_name)].emplace<T>(value);
    }

    ///
    /// Lookup the configuration map for writing, the option_name is trimmed,
    /// means the leading chars '--' are removed to get better names. If the
    /// option_name doesn't exist it's inserted, otherwise the a reference
    /// to the stored config_value is returned; hence, it behaves as the std::map[].
    ///
    /// \param  option_name  The name of the option to lookup in the trimmed form.
    /// \param  value        The value to be stored.
    /// \return config_value The value as reference to optional<string>.
    ///
    template <typename T,
              typename = std::enable_if_t<!std::is_integral_v<std::remove_reference_t<T>>>>
    void set(std::string_view option_name, T&& value)
    {
        using type = std::remove_reference_t<T>;
        map[trim(option_name)].emplace<type>(std::forward<T>(value));
    }

    ///
    /// Check on existence of the option.
    ///
    /// \param  option_name The name of the option to test.
    /// \return true if the option has been defined, otherwise false.
    ///
    bool exist(std::string const& option_name) const { return map.count(option_name) > 0; }

    ///
    /// Dump the configuration stored in sorted form
    /// \param os The ostream to dump.
    /// @return The stream written.
    ///
    std::ostream& dump(std::ostream& os) const;

    ///
    /// Print a settings value
    ///
    /// @param os    The ostream to dump.
    /// @param value The value to render.
    /// @return The stream written.
    ///
    static std::ostream& print(std::ostream& os, settings::option_value const& value);

private:
    static void debug_print(std::string const& option_name, settings::option_value const& value);

private:
    /// Trim leading '--' chars from key.
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

    map_type map;
    static const option_value none;
};

///
/// Settings option trigger.
///
/// Add (secondary) boolean flags to the settings repository if the primary
/// option is set.
///
class settings::option_trigger {
    using trigger_map_type = std::unordered_map<std::string, std::vector<std::string>>;

    trigger_map_type trigger;

public:
    option_trigger() = default;
    ~option_trigger() = default;

    option_trigger(option_trigger const&) = delete;
    option_trigger const& operator=(option_trigger const&) = delete;

    option_trigger(option_trigger&&) = delete;
    option_trigger const& operator=(option_trigger&&) = delete;

public:
    ///
    /// Simplifies depending configuration options, binds the secondary_options
    /// to the primary_option. Only boolean options are possible.
    ///
    /// \param primary_option    The option which triggers depending options.
    /// \param secondary_options The depending options.
    ///
    void add(std::string const& primary_option, std::vector<std::string> const& secondary_options)
    {
        trigger[primary_option] = secondary_options;
    }

    ///
    /// Update the configuration map, if the primary_option is stored in the
    /// config all depending options are added.
    ///
    /// \param config The configuration map.
    ///
    void update(settings& config) const
    {
        for (auto const& [primary_option, secondary_options] : trigger) {
            if (!config.exist(trim(primary_option))) {
                continue;
            }
            for (auto const& option : secondary_options) {
                config.set(option, true);
            }
        }
    }
};

std::ostream& operator<<(std::ostream& os, settings::option_value const& value);

}  // namespace eda
