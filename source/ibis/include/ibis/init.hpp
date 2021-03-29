#pragma once

namespace eda {
class settings;
}

namespace ibis {

class init {
public:
    explicit init(int argc, const char* argv[], eda::settings& setting_);

    init() = delete;
    ~init() = default;

    init(init const&) = delete;
    init& operator=(init const&) = delete;

    init(init&&) = delete;
    init& operator=(init&&) = delete;

private:
    void parse_cli(int argc, const char* argv[]);
    void l10n();
    static void register_signal_handlers();
    void user_config_message_color();

private:
    eda::settings& setting;
};

}  // namespace ibis
