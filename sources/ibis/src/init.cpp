/*
 * init.cpp
 *
 *  Created on: 07.08.2018
 *      Author: olaf
 */

#include <ibis/init.hpp>

#include <eda/settings.hpp>
#include <eda/configuration.hpp>

#include <eda/util/file/file_reader.hpp>
#include <eda/color/message.hpp>

#include <eda/support/boost/locale.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/localization_backend.hpp>

#include <CLI/CLI11.hpp>

#include <eda/util/file/user_home.hpp>
#include <eda/util/file/file_reader.hpp>
#include <eda/util/string/icompare.hpp>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/error/en.h>
#include <eda/support/RapidJSON/merge.hpp>

#include <boost/filesystem/path.hpp>

#include <cstdlib>
#include <memory>
#include <optional>
#include <string_view>
#include <algorithm>

#include <eda/util/cxx_bug_fatal.hpp>

#include <eda/namespace_alias.hpp>


extern bool register_gdb_signal_handler();


namespace ibis {


static const char VERSION_STR[] = "EDA/ibis 0.0.1";
static const char EDA_URL[] = "https://github.com/eda/ibis";


init::init(int argc, const char* argv[], eda::settings& setting_)
: setting{ setting_ }
{
    register_signal_handlers();

    parse_cli(argc, argv);

    l10n();

    user_config_message_color();
}

struct Formatter : public CLI::Formatter { };


void init::parse_cli(int argc, const char* argv[])
{
    using namespace docopt;

    using boost::locale::format;
    using boost::locale::translate;

    CLI::App app{VERSION_STR};

    auto fmt = std::make_shared<Formatter>();
    fmt->column_width(40);
    app.formatter(fmt);

    app.footer((format(translate(
		"\n"
		"Report bugs to {1}")) % EDA_URL).str());

    // defaults
	std::vector<std::string> files;
	std::string lib_path;

	struct {
		unsigned tab_size = 4;
		unsigned error_limit = 20;
	} preset;

	// As idea \see
	// [What do the -f and -m in gcc/clang compiler options stand for](
    // https://stackoverflow.com/questions/16227501/what-do-the-f-and-m-in-gcc-clang-compiler-options-stand-for)

    try {
		// Primary Options
		app.add_option("files", files,
			translate("One or more VHDL file(s)."))
			->required()
			->check(CLI::ExistingFile);

		app.add_flag("--version",
			translate("Show version."));

		// Working/Processing flags
		app.add_flag("-a,--analyze",
			translate("Analyze the design.")); // XXX preventive added, unused

		app.add_option("--lib-path", lib_path,
			translate("Path to libraries."))
			->group("Paths")
			->envname("EDA_LIBPATH")->take_last()
			->check(CLI::ExistingDirectory); // XXX preventive added, unused

		// Message Options
		app.add_flag("-q,--quiet",
			translate("Print less text."))
			->group("Message Options");
		app.add_flag("-v,--verbose",
			translate("Print more text."))
			->group("Message Options")
			->excludes("--quiet");
		app.add_flag("--no-color",
			translate("Don\'t render messages using colors. On output redirection "
					  "no colors are used."))
			->group("Message Options");
		app.add_flag("--force-color",
			translate("Even on redirected output enforce the rendering of messages "
					  "using colors."))
			->group("Message Options")
			->excludes("--no-color");
		app.add_option("--tab-size", preset.tab_size,
			translate("Tabulator size, affects printing source snippet on error printing."), true)
			->group("Message Options")
			->check(CLI::Range(1u, 10u)); // XXX unused in misc. error_handler.cpp

		// Warning Options
		app.add_flag("--Wall",
			translate("Warn all."))
			->group("Warning Options");
		app.add_flag("--Wunused",
			translate("Warn on unused."))
			->group("Warning Options");
		app.add_flag("--Wother",
			translate("Warn for others."))
			->group("Warning Options");

		// Options to Control Error and Warning Messages Flags
		app.add_option("--ferror-limit", preset.error_limit,
			translate("Limit emitting diagnostics, can be disabled with --ferror-limit=0."), true)
			->group("Error/Warning Message Control Options"); // XXX unused in context.cpp

		// Locale Options


    }
    catch(CLI::Error const& e) {
    	std::cerr << translate("Internal CLI11 parser code error. Please fill a bug report")
    			  << std::endl;
    	std::exit(app.exit(e));
    }

    // CLI parse
    try {
        app.parse(argc, argv);
    } catch (CLI::ParseError const& e) {
        std::exit(app.exit(e));
    }

    if (app.count("--version")) {
        std::cout << VERSION_STR << "\n";
        std::exit(EXIT_SUCCESS);
    }

    // .. and evaluate
    auto const set_flag = [&](std::string const& flag, bool value = true) {
        if (app.count(flag)) {
            setting.set(flag, value);
        }
    };

    // secondary triggered options
    eda::settings::option_trigger trigger_flags;
    trigger_flags.add("--Wall", { "--Wunused", "--Wother" });

    // Primary Options
    setting.set("--files", files);
    if (!lib_path.empty()) {  setting.set("--lib-path", lib_path); }

    // Working/Processing flags
    set_flag("--analyze");

    // Message Options
    set_flag("--quiet");
    set_flag("--verbose");
    set_flag("--no-color");
    set_flag("--force-color");
    setting.set<long>("--tab-size", preset.tab_size);

    // Warning Options
    set_flag("--Wall");
    set_flag("--Wunused");
    set_flag("--Wother");

	// Options to Control Error and Warning Messages Flags
    setting.set<long>("--ferror-limit", preset.error_limit);


    // update triggered flags
    trigger_flags.update(setting);
}


void init::register_signal_handlers()
{
#if defined(EDA_WITH_GDB_STACKTRACE) && (BOOST_OS_LINUX)
    using failure = eda::color::message::failure;

    if (!register_gdb_signal_handler()) {
        std::cerr << failure("Failed to install signal handlers") << "\n";
        std::exit(EXIT_FAILURE);
    }
#endif
}


/*
 * FixMe: - change path to .eda/config/message.json to prevent "mega" JSON files
 *        - setup message colors
 */
void init::user_config_message_color()
{
    bool const force_color = [&] {
        if (setting["force-color"]) return true;
        return false;
    }();

    if (setting["no-color"] && !force_color) {
        // no color wanted - skip further proceeding
        return;
    }

    bool const quiet = [&] {
        if (setting["quiet"]) return true;
        return false;
    }();

    bool const verbose = [&] {
        if (setting["verbose"]) return true;
        return false;
    }();


    static const char default_cfg_json[] = R"({
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

    using namespace eda;
    namespace rjson = rapidjson;

    auto const parse_json = [&quiet](char const* json) { // maybe throw to get path printed??
        rjson::Document document;
        if (document.Parse(json).HasParseError()) {
            if (!quiet) {
                std::cerr << eda::color::message::error("Error:")
                          << " parsing JSON configuration file: "
                          << rjson::GetParseError_En(document.GetParseError())
                          << "(offset " << document.GetErrorOffset() << ")\n";
            }
        }
        return document;
    };

    rjson::Document config = parse_json(default_cfg_json);

    // load user settings if exists and merge them into defaults

    fs::path json_path = util::user_home({".eda"}) / "config.json";

    util::file_loader file_reader{ std::cerr, setting };
    auto const json_txt = file_reader.read_file(json_path);

    if (json_txt) {
        rjson::Document user_config = parse_json((*json_txt).c_str());
        merge(config, user_config);
    }
    else{ /* nothing */ }

    if (verbose) {
        std::cerr << eda::color::message::note("Note:")
                  << " Using message color defaults:\n";
        auto const print_json = [](auto const& doc) {
            rjson::StringBuffer str_buff;
            rjson::PrettyWriter<rjson::StringBuffer> writer(str_buff);
            doc.Accept(writer);
            ::puts(str_buff.GetString());
        };
        print_json(config);
    }

    auto const get_formatter = [&](char const json_ptr[]) {

        using namespace eda::color::message;
        eda::color::printer format;

        if (rjson::Value* style = rjson::GetValueByPointer(config, rjson::Pointer(json_ptr))) {
            for (auto const& object : style->GetObject()) {
                auto const name = object.name.GetString();
                auto const attr_name = object.value.GetString();

                auto const update_format = [&](char const attr_name[], auto const attribute_getter) {
                    auto const attr{ attribute_getter(attr_name) };
                    if (attr) {
                        format |= *attr;
                        if (verbose) {
                            std::cerr << note("NOTE:") << " using "
                                       << json_ptr << "/" << name << " = " << attr_name << "\n";
                        }
                    }
                    else{
                        if (!quiet) {
                            std::cerr << warning("WARNING:") << " Ignore invalid "
                                      << json_ptr << "/" << name << " = " << attr_name << "\n";
                        }
                    }
                };

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

    auto const failure_format = get_formatter("/message/failure/style");
    imbue(std::cerr, std::make_unique<color::message::failure_facet>(
        failure_format,
        color::color_off,
        force_color)
    );

    auto const error_format = get_formatter("/message/error/style");
    imbue(std::cerr, std::make_unique<color::message::error_facet>(
        error_format,
        color::color_off,
        force_color)
    );

    auto const warning_format = get_formatter("/message/warning/style");
    imbue(std::cerr, std::make_unique<color::message::warning_facet>(
        warning_format,
        color::color_off,
        force_color)
    );

    auto const note_format = get_formatter("/message/note/style");
    imbue(std::cerr, std::make_unique<color::message::note_facet>(
        note_format,
        color::color_off,
        force_color)
    );
}


void init::l10n()
{
    // [Using Localization Backends](
    //  https://www.boost.org/doc/libs/1_56_0/libs/locale/doc/html/using_localization_backends.html)
    using namespace boost::locale;

    char const LC_PATH[]   = "~/.eda/l10n";
    char const LC_DOMAIN[] = "eda";

	localization_backend_manager l10n_backend = localization_backend_manager::global();
    l10n_backend.select("std");
    generator gen(l10n_backend);
    localization_backend_manager::global(l10n_backend);

    gen.add_messages_path(LC_PATH);
    gen.add_messages_domain(LC_DOMAIN);
    std::locale::global(gen(""));
    std::cout.imbue(std::locale());
    std::cerr.imbue(std::locale());
}

} // namespace ibis

