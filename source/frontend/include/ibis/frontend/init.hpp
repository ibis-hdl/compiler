#pragma once

namespace ibis::frontend {

///
/// @brief Initialize the frontend
///
/// @todo By replacing the old settings class concept (replaced by
/// boost::property_tree approach for now), updating secondary
/// depeneding flags comes more investigative. The idea was like
/// `secondary_flag["--Wall"] = { "--Wunused", "--Wother" }`
/// and an update() does setting up the setting variables. By using
/// boost::property_tree approach, CLI argument names differ from
/// settings name. Which depend flag must be set is only desideable
/// at the end of transforming from all cli arguments into setting
/// variables. At this time the setting variable names are given
/// before. This results into use of these names twice in the
/// source at different places. This looks cumbersome/odd.
///
class init {
public:
    explicit init(int argc, const char* argv[]);

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
};

}  // namespace ibis::frontend
