/*
 * init.cpp
 *
 *  Created on: 07.08.2018
 *      Author: olaf
 */

#include <ibis/init.hpp>
#include <ibis/signal_handler.hpp>
#include <ibis/version.hpp>
#include <ibis/build_info.hpp>

#include <eda/configuration.hpp>
#include <eda/settings.hpp>

#include <eda/color/message.hpp>
#include <eda/util/file/file_reader.hpp>

#include <boost/locale/generator.hpp>
#include <boost/locale/localization_backend.hpp>
#include <eda/support/boost/locale.hpp>

#include <CLI/CLI.hpp>

#include <eda/util/file/file_reader.hpp>
#include <eda/util/file/user_home_dir.hpp>
#include <eda/util/string/icompare.hpp>
// clang-format off
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/pointer.h>
#include <rapidjson/prettywriter.h>
#include <eda/support/RapidJSON/merge.hpp>
// clang-format on

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp> // canonical

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <eda/util/cxx_bug_fatal.hpp>

#include <eda/predef.hpp>

#include <eda/namespace_alias.hpp>


namespace ibis {

init::init(int argc, const char* argv[], eda::settings& setting_)
    : setting{ setting_ }
{
    register_signal_handlers();

    parse_cli(argc, argv);

    l10n();

    user_config_message_color();
}

void init::parse_cli(int argc, const char* argv[])
{
    using boost::locale::format;
    using boost::locale::translate;

    static const char EDA_URL[] = R"(https://github.com/???/ibis)";

    CLI::App app{ EDA_IBIS_VERSION_STR };

    struct Formatter : public CLI::Formatter { };

    auto fmt = std::make_shared<Formatter>();
    fmt->column_width(40);
    app.formatter(fmt);

    app.footer((format(translate("\nReport bugs to {1}")) % EDA_URL).str());

    // defaults
    struct {
        std::vector<std::string> hdl_files;
        std::string hdl_lib_path;

        unsigned verbose = 0;

        unsigned tab_size = 4;
        unsigned error_limit = 20;

        std::string locale_dir;
    } cli_parameter;

    /* Feature Request:
     * from GCC we also know some cli options (f: Flag, m: Mode)
     * \see [What do the -f and -m in gcc/clang compiler options stand for](
     * https://stackoverflow.com/questions/16227501/what-do-the-f-and-m-in-gcc-clang-compiler-options-stand-for),
     * maybe the nomenclature can be used here too. */

    // clang-format off
    try {
        
        /* [CLIUtils/CLI11](https://github.com/CLIUtils/CLI11) is using for pure flags
         * a const string reference argument at add_flags() member which boost.locale's 
         * translate() doesn't provides. A work arround is to use dummy flag 
         * variable to enforce an overload which is aprobiate here. */
        bool dummy{};

        /*
         * Primary Options Group
         */
        app.add_option("files", cli_parameter.hdl_files,
               translate("One or more VHDL file(s)."))
            ->required()
            ->check(CLI::ExistingFile);

        app.add_flag("--version", dummy, // FixMe: set_version_flag()
            translate("Show version."));

        app.add_flag("--build-info", dummy,
            translate("Show build informations."));

        /*
         * Working/Processing flags
         */

        app.add_flag("-a,--analyze", dummy,
            translate("Analyze the design.")); // unused

        /*
         * Message Options Group
         */
        static const std::string message_group{ translate("Message Options") };

        app.add_flag("-q,--quiet", dummy,
              translate("Print less text."))
            ->group(message_group);
            // FixMe: Allow e.g. '-vv' and '--verbose=2' with range check to enums
        app.add_flag("-v,--verbose", cli_parameter.verbose,
              translate("Print more text."))
            ->group(message_group)
            ->excludes("--quiet");
        app.add_flag("--no-color", dummy,
              translate("Don\'t render messages using colors. On output redirection "
                        "no colors are used."))
            ->group(message_group);
        app.add_flag("--force-color", dummy,
              translate("Even on redirected output enforce the rendering of messages "
                        "using colors."))
            ->group(message_group)
            ->excludes("--no-color");
        app.add_option("--tab-size", cli_parameter.tab_size,
              translate("Tabulator size, affects printing source snippet on error printing."), true)
            ->group(message_group)
            ->check(CLI::Range(1u, 10u)); // XXX unused in e.g. error_handler.cpp

        /*
         * Locale Options Group
         */
        static const std::string locale_group{ translate("Locale/Environment Options") };

        app.add_option("--locale-dir", cli_parameter.locale_dir,
              translate("localization catalog data"), true)
            ->group(locale_group)
            ->envname("EDA_LOCALE_DIR")
            ->check(CLI::ExistingDirectory);

        /*
         * Warning Options Group
         */
        static const std::string warning_group{ translate("Warning Options") };

        app.add_flag("--Wall", dummy,
              translate("Warn all."))
            ->group(warning_group); // unused
        app.add_flag("--Wunused", dummy,
              translate("Warn on unused."))
            ->group(warning_group); // unused
        app.add_flag("--Wother", dummy,
              translate("Warn for others."))
            ->group(warning_group); // unused

        // Option to Control Error and Warning Messages Flags
        app.add_option("--ferror-limit", cli_parameter.error_limit,
              translate("Limit emitting diagnostics, can be disabled with --ferror-limit=0."), true)
            ->group(warning_group); // XXX unused in context.cpp

        /*
         * Paths Group
         */
        static const std::string path_group{ translate("Paths") };

        app.add_option("--hdl-lib_path", cli_parameter.hdl_lib_path,
              translate("Path to libraries."))
            ->group(path_group)
            ->envname("EDA_LIBPATH")
            ->take_last()
            ->check(CLI::ExistingDirectory); // unused
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

    /* FixMe: The code below is far away to be practical/useable.
     * The settings class overloaded set() member and hence the C++ 
     * lambda 'set_option' get into compile error with
     * 'map[trim(option_name)].emplace<T>(value);', so the exhausting
     * way is choosen temporary here.  This mix here testing on given
     * command line arguments, using defaults from cli_parameters etc.
     * is a mess ....
     * There is a functor missing for settings flags and options
     * with suplying their defaults.
     * Solution: Maybe use boost.property_tree and reuse settings::option_trigger
     * as option for option dependencies??? */

    if (app.count("--version") != 0u) {
        std::cout << EDA_IBIS_VERSION_STR << '\n';
        std::exit(EXIT_SUCCESS);
    }

    if (app.count("--build-info") != 0u) {
        build_info(std::cout);
        std::exit(EXIT_SUCCESS);
    }

    // helper for configure settings from CLI args
    auto const set_flag = [&](std::string const& flag, bool value = true) {
        if (app.count(flag) != 0u) {
            setting.set(flag, value);
        }
    };

    // secondary triggered option dependencies
    eda::settings::option_trigger triggered_flags;
    triggered_flags.add("--Wall", { "--Wunused", "--Wother" });

    // Primary Options
    setting.set("--files", cli_parameter.hdl_files);

    if (app.count("--hdl-lib_path") != 0u) {
        setting.set("--hdl-lib_path", cli_parameter.hdl_lib_path);
    }

    // Working/Processing flags
    set_flag("--analyze");

    // Message Options
    if (app.count("--verbose") != 0u) {
        setting.set<long>("--verbose", cli_parameter.verbose);
    }

    set_flag("--quiet");
    set_flag("--no-color");
    set_flag("--force-color");
    setting.set<long>("--tab-size", cli_parameter.tab_size);

    // Warning Options
    set_flag("--Wall");
    set_flag("--Wunused");
    set_flag("--Wother");

    // Options to Control Error and Warning Messages Flags
    setting.set<long>("--ferror-limit", cli_parameter.error_limit);

    // Locale Options
    if (app.count("--locale-dir") != 0u) {
        setting.set("--locale-dir", cli_parameter.locale_dir);
    }

    // update all secondary triggered flags
    triggered_flags.update(setting);
}

void init::register_signal_handlers()
{
    ibis::register_signal_handlers();
}

void init::user_config_message_color()
{
    static const char default_cfg_json[] =
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
})";

    bool const force_color = [&] { return setting["force-color"]; }();

    if (setting["no-color"] && !force_color) {
        // no color wanted - skip further proceeding
        return;
    }

    bool const quiet = [&] { return setting["quiet"]; }();
    bool const verbose = [&] { return setting["verbose"]; }();

    using namespace eda;
    using namespace eda::color;
    namespace rjson = rapidjson;

    auto const parse_json = [&quiet](char const json[]) {
        rjson::Document document;
        if (document.Parse(json).HasParseError()) {
            if (!quiet) {
                // clang-format off
                std::cerr << message::error("Error:")
                          << " parsing JSON configuration file: "
                          << rjson::GetParseError_En(document.GetParseError())
                          << "(offset " << document.GetErrorOffset() << ")\n";
                // clang-format on
            }
        }
        return document;
    };

    auto const print_json = [](rjson::Document const& doc) {
        rjson::StringBuffer buffer;
        rjson::PrettyWriter<rjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        std::cerr << buffer.GetString() << std::endl;
    };

    rjson::Document default_config = parse_json(default_cfg_json);

    // load user settings if exists and merge them into defaults
    using ::eda::util::file_loader;
    using ::eda::util::user_home_dir;

    fs::path json_path = user_home_dir({ ".eda" }) / "config.json";

    file_loader file_reader{ std::cerr, setting };
    auto const json_txt = file_reader.read_file(json_path);

    if (json_txt) {
        rjson::Document user_config = parse_json((*json_txt).c_str());
        merge(default_config, user_config);
    } else {
        /* nothing */
    }

    if (verbose) {
        std::cerr << message::note("Note:") << " Using message color defaults:\n";
        print_json(default_config);
    }

    auto const get_formatter = [&](char const json_ptr[]) {

        eda::color::printer format;

        if (rjson::Value* style = rjson::GetValueByPointer(default_config, rjson::Pointer(json_ptr))) {
            for (auto const& object : style->GetObject()) {
                auto const name = object.name.GetString();
                auto const attr_name = object.value.GetString();

                // clang-format off
                auto const update_format = [&](char const attr_name[], auto const attribute_getter) {
                    auto const attr{ attribute_getter(attr_name) };
                    if (attr) {
                        format |= *attr;
                        if (verbose) {
                            std::cerr << message::note("NOTE:") << " using "
                                      << json_ptr << "/" << name << " = " << attr_name << '\n';
                        }
                    } else {
                        if (!quiet) {
                            std::cerr << message::warning("WARNING:") << " Ignore invalid "
                                      << json_ptr << "/" << name << " = " << attr_name << '\n';
                        }
                    }
                };
                // clang-format on

                if (util::icompare(name, "text")) {
                    update_format(attr_name, &color::text_attr);
                    continue;
                }
                if (util::icompare(name, "foreground")) {
                    update_format(attr_name, &color::foreground_attr);
                    continue;
                }
                if (util::icompare(name, "background")) {
                    update_format(attr_name, &color::background_attr);
                    continue;
                }
            }
        }
        return format;
    };

    auto const imbue = [](auto& stream, auto&& facet_ptr) {
        std::locale locale(stream.getloc(), facet_ptr.release());
        stream.imbue(locale);
    };

    // clang-format off
    auto const failure_format = get_formatter("/message/failure/style");
    imbue(std::cerr, std::make_unique<message::failure_facet>(
        failure_format,
        color::color_off,
        force_color)
    );

    auto const error_format = get_formatter("/message/error/style");
    imbue(std::cerr, std::make_unique<message::error_facet>(
        error_format,
        color::color_off,
        force_color)
    );

    auto const warning_format = get_formatter("/message/warning/style");
    imbue(std::cerr, std::make_unique<message::warning_facet>(
        warning_format,
        color::color_off,
        force_color)
    );

    auto const note_format = get_formatter("/message/note/style");
    imbue(std::cerr, std::make_unique<message::note_facet>(
        note_format,
        color::color_off,
        force_color)
    );
    // clang-format on
}

void init::l10n()
{
    using namespace boost::locale;
    using namespace eda;

#if (BOOST_OS_WINDOWS)
    const char backend_str[] = "winapi";
#else
    const char backend_str[] = "std";
#endif

    // [Using Localization Backends](
    //  https://www.boost.org/doc/libs/1_68_0/libs/locale/doc/html/using_localization_backends.html)
    localization_backend_manager l10n_backend = localization_backend_manager::global();
    l10n_backend.select(backend_str);
    generator gen_{ l10n_backend };
    localization_backend_manager::global(l10n_backend);

    generator gen{};

    auto const l10n_path = [this] {
        if (setting["locale-dir"]) {
            return fs::path{ setting["locale-dir"].get<std::string>() };
        } else {
            return ::eda::util::user_home_dir({ ".eda", "l10n" });
        }
    }();

    boost::system::error_code ec;
    auto lc_path = fs::canonical(l10n_path, ec);

    long const verbose = [&] { return setting["verbose"].get<long>(); }();

    if (ec) {
        if (verbose > 1) {
            // FixMe: notice or warning level for those message
            std::cerr << R"(locale directory ')" << l10n_path.string()
                      << R"( failure: )" << ec.message() << std::endl;
            }
        return;
    }
    else {
        if (verbose > 2) {
            std::cout << "LC_PATH = " 
                      << lc_path.make_preferred().string() << std::endl;
        }
    }

    gen.add_messages_path(lc_path.make_preferred().string());
    gen.add_messages_domain("eda");

    std::locale locale = gen("");
    std::locale::global(locale);
    std::cout.imbue(locale);
    std::cerr.imbue(locale);
}

} // namespace ibis
