//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/frontend/init.hpp>
#include <ibis/frontend/signal_handler.hpp>
#include <ibis/frontend/version.hpp>

#include <ibis/settings.hpp>

#include <ibis/platform.hpp>

#include <ibis/util/file/file_loader.hpp>
#include <ibis/util/file/user_home_dir.hpp>
#include <ibis/util/icompare.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <ibis/util/compiler/warnings_off.hpp>  // -Wimplicit-int-float-conversion
#include <CLI/CLI.hpp>
#include <ibis/util/compiler/warnings_on.hpp>

#include <boost/locale/message.hpp>
#include <boost/locale/format.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/localization_backend.hpp>
#include <boost/locale/time_zone.hpp>

#include <cstdlib>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <locale>
#include <system_error>
#include <iostream>

namespace ibis::frontend {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
init::init(int argc, const char* argv[])
{
    register_signal_handlers();

    parse_cli(argc, argv);

    l10n();
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,readability-convert-member-functions-to-static)
void init::parse_cli(int argc, const char* argv[])
{
    using boost::locale::format;
    using boost::locale::translate;

    static constexpr std::size_t cli_column_width = 80;

    CLI::App app{ std::string{ IBIS_HDL_VERSION_STR }, std::string{ "ibis" } };

    struct Formatter : public CLI::Formatter {};

    auto fmt = std::make_shared<Formatter>();
    fmt->column_width(cli_column_width);
    app.formatter(fmt);

    app.footer((format(translate("\nReport bugs to {1}")) % IBIS_HDL_HOMEPAGE_URL).str());

    // options and defaults
    struct {
        // --- primary options group ---
        std::vector<std::string> hdl_files;
        std::string hdl_lib_path;

        // --- message options group ---
        unsigned verbose_level = 0;
        unsigned tab_size = 4;

        // --- locale options group ---
        std::string locale_dir;

        // --- warning options group ---
        unsigned error_limit = 20;
    } cli_parameter;

    // Feature Request:
    // from GCC we also know some cli options (f: Flag, m: Mode)
    // \see [What do the -f and -m in gcc/clang compiler options stand for](
    // https://stackoverflow.com/questions/16227501/what-do-the-f-and-m-in-gcc-clang-compiler-options-stand-for),
    // maybe the nomenclature can be used here too.

    // clang-format off
    try {

        //
        // Primary option group
        //
        app.add_option("hdl_files", cli_parameter.hdl_files)
            ->description(translate("One or more VHDL file(s)."))
            ->required()
            ->check(CLI::ExistingFile)
            ;
        app.add_flag("--version") // FixMe: set_version_flag() @CLI11 v1.10
            ->description(translate("Show version."))
            ;

        //
        // Message option group
        //
        {
            static constexpr int MAX_TAB_SIZE = 10;

            auto* group = app.add_option_group(translate("Message Options"), // --
                translate("Options regards to messages."));

            group->add_flag("-q,--quiet")
                ->description(translate("Print less text."))
                ;
                // FixMe: Allow e.g. '-vv' and '--verbose=2' with range check to enums
            group->add_flag("-v,--verbose", cli_parameter.verbose_level)
                ->description(translate("Print more text."))
                ->excludes("--quiet")
                ;
            group->add_flag("--no-color")
                ->description(translate("Don\'t render messages using colors. On output redirection "
                                        "no colors are used."))
                ;
            group->add_flag("--force-color")
                ->description(translate("Even on redirected output enforce the rendering of messages "
                                        "using colors."))
                ->excludes("--no-color")
                ;
            group->add_option("--tab-size", cli_parameter.tab_size) // ToDo: unused in e.g. diagnostic_handler.cpp
                ->description(translate("Tabulator size, affects printing source snippet on error printing."))
                ->check(CLI::Range(1, MAX_TAB_SIZE))
                ;
        }

        //
        // Locale option group
        //
        {
            auto* group = app.add_option_group(translate("Locale/Environment Options"), // --
                translate("Path to locale etc."));

            group->add_option("--locale-dir", cli_parameter.locale_dir)
                ->description(translate("localization catalog data"))
                ->envname("IBIS_HDL_LOCALE_DIR")
                ->check(CLI::ExistingDirectory)
                ;
        }

        //
        // Working/Processing flags
        //

        app.add_flag("-a,--analyze") // unused
            ->description(translate("Analyze the design."));

        //
        // Warning option group
        //
        {
            auto* group = app.add_option_group(translate("Warning Options"),  // --
                translate("Level of warnings"));

            group->add_flag("--Wall") // unused
                ->description(translate("Warn all."))
                ;
            group->add_flag("--Wunused") // unused
                ->description(translate("Warn on unused."))
                ;
            group->add_flag("--Wother") // unused
                ->description(translate("Warn for others."))
                ;
            // Option to Control Error and Warning Messages Flags
            // FixMe: unused in context.cpp, also CLI11's range check should use treshold_counter::MAX
            group->add_option("--ferror-limit", cli_parameter.error_limit) // --
                ->description(translate("Limit emitting diagnostics, can be disabled with --ferror-limit=0."))
                ->check(CLI::Range(0, std::numeric_limits<std::int32_t>::max()))
                ;
        }

        //
        // Paths Group
        //
        {
            auto* group = app.add_option_group(translate("Paths"), // --
                translate("Important path settings"));

            group->add_option("--hdl-lib-path", cli_parameter.hdl_lib_path) // unused
                ->description(translate("Path to libraries."))
                ->envname("IBIS_LIBPATH")
                ->take_last()
                ->check(CLI::ExistingDirectory)
                ;
        }
    }
    // clang-format on
    catch (CLI::Error const& e) {
        std::cerr << translate("Internal command line parser error") << '\n';
        std::exit(app.exit(e));
    }
    catch (...) {
        std::cerr << translate("Unexpected CLIUtils/CLI11 error") << '\n';
        std::exit(EXIT_FAILURE);
    }

    // parse CLI arguments ...
    try {
        app.parse(argc, argv);
    }
    catch (CLI::ParseError const& e) {
        // e.g. not fulfilled requirements
        std::exit(app.exit(e));
    }
    catch (...) {
        std::cerr << translate("Unexpected command line parser error") << '\n';
        std::exit(EXIT_FAILURE);
    }

    // ... and evaluate CLI arguments:

    ibis::settings::reference_type ptree = ibis::settings::instance();

    if (app.count("--version") != 0) {
        std::cout << IBIS_HDL_VERSION_STR << '\n';
        std::exit(EXIT_SUCCESS);
    }

    // quick&dirty helper for configure settings from CLI args
    class setup {
        // NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
        CLI::App const& app;
        ibis::settings::reference_type pt;
        // NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
    public:
        setup(CLI::App const& app_, ibis::settings::reference_type pt_)
            : app{ app_ }
            , pt{ pt_ }
        {
        }

        void flag(std::string const& cli_arg, std::string const& setting_flag)
        {
            pt.put(setting_flag, app.count(cli_arg) != 0);
        }

        void option(std::string const& setting_flag, unsigned option)
        {
            pt.put(setting_flag, option);
        }

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        void option(std::string const& cli_arg, std::string const& setting_flag, unsigned option)
        {
            if (app.count(cli_arg) != 0) {
                pt.add(setting_flag, option);
            }
        }

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        void option(std::string const& cli_arg, std::string const& setting_flag,
                    std::string const& option)
        {
            if (app.count(cli_arg) != 0) {
                pt.add(setting_flag, option);
            }
        }

        void option(std::string const& setting_flag, std::vector<std::string> const& options)
        {
            for (std::string const& item : options) {
                pt.add(setting_flag, item);
            }
        }
    } setup(app, ptree);

    //
    // Primary option group
    //
    setup.option("hdl-files.file", cli_parameter.hdl_files);

    //
    // Message option group
    //
    setup.flag("--quiet", "quiet");
    setup.option("verbose", cli_parameter.verbose_level);  // note, CLI11 flag
    setup.flag("--no-color", "no-color");
    setup.flag("--force-color", "force-color");
    setup.option("tab-size", cli_parameter.tab_size);

    //
    // Locale option group
    //
    setup.option("--locale-dir", "locale.dir", cli_parameter.locale_dir);

    //
    // Working/Processing flags
    //
    setup.flag("--analyze", "analyze");

    //
    // Warning option group
    //

    setup.flag("--Wunused", "warning.unused");
    setup.flag("--Wother", "warning.other");

    setup.flag("--Wall", "warning.all");

    // ToDo: secondary triggered option dependencies, lhs is the primary
    // secondary_flag["--Wall"] = { "--Wunused", "--Wother" };

    setup.option("--ferror-limit", "f.error_limit", cli_parameter.error_limit);

    //
    // Paths Group
    //
    setup.option("--hdl-lib-path", "hdl-lib.path", cli_parameter.hdl_lib_path);

    // ibis::settings::dump(std::cout);
}

void init::register_signal_handlers() { frontend::register_signal_handlers(); }

void init::l10n()
{
    using namespace boost::locale;
    using namespace ibis;
    using namespace std::literals::string_view_literals;

    // [Using Localization Backends](
    //  https://www.boost.org/doc/libs/1_68_0/libs/locale/doc/html/using_localization_backends.html)
    localization_backend_manager l10n_backend = localization_backend_manager::global();

    if constexpr (ibis::platform == platform::Windows) {
        l10n_backend.select(static_cast<std::string>("winapi"));
    }
    else {
        l10n_backend.select(static_cast<std::string>("std"));
    }

    generator const gen_{ l10n_backend };
    localization_backend_manager::global(l10n_backend);

    generator gen{};

    ibis::settings::reference_type ptree = ibis::settings::instance();

    fs::path const l10n_path = [&] {
        boost::optional<std::string> path = ptree.get_optional<std::string>("locale-dir");
        if (path) {
            return fs::path{ path.get() };
        }
        return ::ibis::util::user_home_dir({ ".ibis", "l10n" });
    }();

    std::error_code ec;
    auto lc_path = fs::canonical(l10n_path, ec);

    unsigned const verbose_level = [&] { return ptree.get<unsigned>("verbose"); }();

    if (ec) {
        if (verbose_level > 1) {
            // FixMe: notice or warning level for those message
            std::cerr << R"(locale directory ')" << l10n_path.string() << R"( failure: )"
                      << ec.message() << '\n';
        }
        return;
    }

    if (verbose_level > 2) {
        std::cout << "LC_PATH = " << lc_path.make_preferred().string() << '\n';
    }

    gen.add_messages_path(lc_path.make_preferred().string());
    gen.add_messages_domain("ibis");

    std::locale const locale = gen("");
    std::locale::global(locale);
    std::cout.imbue(locale);
    std::cerr.imbue(locale);
}

}  // namespace ibis::frontend
