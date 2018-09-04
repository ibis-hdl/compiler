/*
 * init.hpp
 *
 *  Created on: 07.08.2018
 *      Author: olaf
 */

#ifndef SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_
#define SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_

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
    void register_signal_handlers();
    void user_config_message_color();

private:
    // clang-format off
    eda::settings&                                  setting;
    // clang-format on
};

} // namespace ibis

#endif /* SOURCES_IBIS_INCLUDE_IBIS_INIT_HPP_ */
