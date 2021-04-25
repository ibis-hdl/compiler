#include <ibis/frontend/init.hpp>
#include <ibis/frontend/signal_handler.hpp>
#include <ibis/frontend/version.hpp>

#include <ibis/buildinfo.hpp>

#include <ibis/settings.hpp>

#include <ibis/color/message.hpp>
#include <ibis/color/facet.hpp>
#include <ibis/color/attribute.hpp>

#include <ibis/platform.hpp>

#include <ibis/util/file/file_loader.hpp>
#include <ibis/util/file/user_home_dir.hpp>
#include <ibis/util/string/icompare.hpp>

#include <ibis/namespace_alias.hpp>  // IWYU pragma: keep

#include <CLI/CLI.hpp>

#include <boost/property_tree/json_parser.hpp>

#include <boost/locale/message.hpp>
#include <boost/locale/format.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/localization_backend.hpp>
#include <boost/locale/time_zone.hpp>

#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <filesystem>
#include <locale>
#include <stdexcept>
#include <system_error>
#include <unordered_map>
#include <iostream>

namespace ibis::frontend {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
init::init(int argc, const char* argv[])
{
    register_signal_handlers();

    parse_cli(argc, argv);

    l10n();

    user_config_message_color();
}

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
void init::parse_cli(int argc, const char* argv[])
{
    using boost::locale::format;
    using boost::locale::translate;

    CLI::App app{ std::string{ IBIS_HDL_VERSION_STR }, std::string{ "ibis" } };

    struct Formatter : public CLI::Formatter {
    };

    auto fmt = std::make_shared<Formatter>();
    fmt->column_width(40);
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
        app.add_flag("--build-info")
            ->description(translate("Show build informations."))
            ;

        //
        // Message option group
        //
        {
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
            group->add_option("--tab-size", cli_parameter.tab_size) // XXX unused in e.g. error_handler.cpp
                ->description(translate("Tabulator size, affects printing source snippet on error printing."))
                ->check(CLI::Range(1, 10))
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
                ->envname("IBIS_LOCALE_DIR")
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
            group->add_option("--ferror-limit", cli_parameter.error_limit) // XXX unused in context.cpp
                ->description(translate("Limit emitting diagnostics, can be disabled with --ferror-limit=0."))
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
        // e.g. not fullfilled requirements
        std::exit(app.exit(e));
    }
    catch (...) {
        std::cerr << translate("Unexpected command line parser error") << '\n';
        std::exit(EXIT_FAILURE);
    }

    // ... and evaluate CLI arguments:

    ibis::settings::reference_type pt = ibis::settings::instance();

    if (app.count("--version") != 0) {
        std::cout << IBIS_HDL_VERSION_STR << '\n';
        std::exit(EXIT_SUCCESS);
    }

    if (app.count("--build-info") != 0) {
        std::cout << ibis::buildinfo{} << '\n';
        std::exit(EXIT_SUCCESS);
    }

    // helper for configure settings from CLI args
    struct setup {
        CLI::App const& app;
        ibis::settings::reference_type pt;
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

        void option(std::string const& cli_arg, std::string const& setting_flag, unsigned option)
        {
            if (app.count(cli_arg) != 0) {
                pt.add(setting_flag, option);
            }
        }

        void option(std::string const& cli_arg, std::string const& setting_flag, std::string option)
        {
            if (app.count(cli_arg) != 0) {
                pt.add(setting_flag, option);
            }
        }

        void option(std::string const& setting_flag, std::vector<std::string> options)
        {
            for (std::string const& item : options) {
                pt.add(setting_flag, item);
            }
        }
    } setup(app, pt);

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

void init::user_config_message_color()
{
    static const std::string_view default_cfg_json{
        R"({
  "message": {
    "failure": {
      "style": {
        "foreground": "red",
        "background": "white",
        "text"      : "bold"
      }
    },
    "error": {
      "style": {
        "foreground": "red",
        "text"      : "bold"
      }
    },
    "warning": {
      "style": {
        "foreground": "yellow"
      }
    },
    "note": {
      "style": {
        "foreground": "green"
      }
    }
  }
})"
    };

    ibis::settings::insert_json(default_cfg_json);

    ibis::settings::reference_type pt = ibis::settings::instance();

    bool const force_color = [&] { return pt.get<bool>("force-color"); }();
    bool const no_color = [&] { return pt.get<bool>("no-color"); }();

    if (no_color && !force_color) {
        // no color wanted - skip further proceeding
        return;
    }

    // bool const quiet = [&] { return pt.get<bool>("quiet"); }();
    bool const verbose = [&] { return pt.get<unsigned>("verbose"); }();

#if 0
    // Old code based on RapidJSON. The idea was to override defaults by user
    // configureable JSON settings file and merge it. The merge algorithm
    // is at <ibis/support/RapidJSON/merge.hpp>.
    // Unfortunately RapidJSON has only a master branch in 2021, v1.1.0
    // is from 2016 and got compile errors using clang-11-win on Windows.
    // Sometimes the master branch compiles, sometimes not. So it's
    // decidet to get rid off RapidJSON and using boost's property_tree,
    // even if merging isn't support still with boost v1.75, see
    // [Future Development: Mathematical relations: ptree difference, union, intersection](
    // https://www.boost.org/doc/libs/1_75_0/doc/html/property_tree/appendices.html)
    // Hopefully, this is solved if the frontend get more usefull.
    using ::ibis::util::file_loader;
    using ::ibis::util::user_home_dir;

    fs::path json_path = user_home_dir({ ".ibis" }) / "config.json";

    file_loader file_reader{ std::cerr, quiet };
    auto const json_txt = file_reader.read_file(json_path);

    if (json_txt) {
        rjson::Document user_config = parse_json((*json_txt).c_str());
        merge(default_config, user_config);
    }
#endif

    using namespace ibis;
    using namespace ibis::color;

    if (verbose) {
        std::cout << message::note("Note:") << " Using message color defaults:\n";
        std::cout << default_cfg_json << '\n';
    }

    auto const get_formatter = [&](std::string_view json_ptr) {
        auto const& child = ibis::settings::instance().get_child(json_ptr.data());
        // pt::write_json(std::cout, child);

        ibis::color::printer format_style;

        auto const update_format = [&](std::string_view attr_name, auto const attribute_getter,
                                       ibis::color::printer& format) {
            auto const attr{ attribute_getter(attr_name) };
            if (attr) {
                format |= *attr;
            }
        };

        for (auto const& x : child) {
            std::string_view const name = x.first.data();        // key
            std::string_view const attr_name = x.second.data();  // value

            if (util::icompare(name, "text")) {
                update_format(attr_name, &color::text_attr, format_style);
                continue;
            }
            if (util::icompare(name, "foreground")) {
                update_format(attr_name, &color::foreground_attr, format_style);
                continue;
            }
            if (util::icompare(name, "background")) {
                update_format(attr_name, &color::background_attr, format_style);
                continue;
            }
        }

        return format_style;
    };

    auto const imbue = [](auto& stream, auto&& facet_ptr) {
        std::locale locale(stream.getloc(), facet_ptr.release());
        stream.imbue(locale);
    };

    auto const failure_format = get_formatter("message.failure.style");
    imbue(std::cerr,
          std::make_unique<message::failure_facet>(failure_format, color::color_off, force_color));

    auto const error_format = get_formatter("message.error.style");
    imbue(std::cerr,
          std::make_unique<message::error_facet>(error_format, color::color_off, force_color));

    auto const warning_format = get_formatter("message.warning.style");
    imbue(std::cerr,
          std::make_unique<message::warning_facet>(warning_format, color::color_off, force_color));

    auto const note_format = get_formatter("message.note.style");
    imbue(std::cerr,
          std::make_unique<message::note_facet>(note_format, color::color_off, force_color));
}

void init::l10n()
{
    using namespace boost::locale;
    using namespace ibis;
    using namespace std::literals;

    // [Using Localization Backends](
    //  https://www.boost.org/doc/libs/1_68_0/libs/locale/doc/html/using_localization_backends.html)
    localization_backend_manager l10n_backend = localization_backend_manager::global();

    if constexpr (ibis::build_platform == platform::Win32) {
        l10n_backend.select(static_cast<std::string>("winapi"));
    }
    else {
        l10n_backend.select(static_cast<std::string>("std"));
    }

    generator gen_{ l10n_backend };
    localization_backend_manager::global(l10n_backend);

    generator gen{};

    ibis::settings::reference_type pt = ibis::settings::instance();

    fs::path const l10n_path = [&] {
        boost::optional<std::string> path = pt.get_optional<std::string>("locale-dir");
        if (path) {
            return fs::path{ path.get() };
        }
        return ::ibis::util::user_home_dir({ ".ibis", "l10n" });
    }();

    std::error_code ec;
    auto lc_path = fs::canonical(l10n_path, ec);

    unsigned const verbose_level = [&] { return pt.get<unsigned>("verbose"); }();

    if (ec) {
        if (verbose_level > 1) {
            // FixMe: notice or warning level for those message
            std::cerr << R"(locale directory ')" << l10n_path.string() << R"( failure: )"
                      << ec.message() << std::endl;
        }
        return;
    }

    if (verbose_level > 2) {
        std::cout << "LC_PATH = " << lc_path.make_preferred().string() << std::endl;
    }

    gen.add_messages_path(lc_path.make_preferred().string());
    gen.add_messages_domain("ibis");

    std::locale locale = gen("");
    std::locale::global(locale);
    std::cout.imbue(locale);
    std::cerr.imbue(locale);
}

}  // namespace ibis::frontend
