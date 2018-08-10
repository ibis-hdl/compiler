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

#include <eda/compiler/warnings_off.hpp>
#include <docopt.h>
#include <eda/compiler/warnings_on.hpp>

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


init::init(int argc, const char* argv[], eda::settings& setting_)
: setting{ setting_ }
{
	register_signal_handlers();

	parse_env();
	parse_cli(argc, argv);

	user_config_message_color();
}


void init::parse_env()
{
    auto const getenv = [](std::string const& key) {
        char const* val = std::getenv( key.c_str() );
        return val == nullptr ? std::string{} : std::string(val);
    };

    // pure ENV name used for configuration
    auto const set_option = [&](std::string const& env_name) {
        std::string const env_var{ getenv(env_name) };
        if (!env_var.empty()) {
        	setting.set(env_name) = env_var;
        }
    };

    // key used for configuration to allow overriding them on command line
    auto const set_option_key = [&](std::string const& env_name, std::string const& key_name) {
        std::string const env_var{ getenv(env_name) };
        if (!env_var.empty()) {
        	setting.set(key_name) = env_var;
        }
    };

    set_option("HOME");
    set_option_key("EDA_LIBPATH", "libpath");	// overridable by cmd line
}


static const char VERSION_STR[] = "EDA/ibis 0.0.1";
static const char USAGE[] =
R"(EDA/ibis

Usage:
  ibis [-a] [-q|-v]
       [--libpath=<path>]
       [--no-color | --force-color]
       [--Wall --Wunused --Wother] 
       <file> ...
  ibis (-h | --help)
  ibis --version

Arguments:
  <file>                One or more file(s).

Settings:
  --libpath=<path>      Path to libraries.

Options:
  -a --analyse          Analyse.
  -h --help             Show this screen.
  --version             Show version.

Message Options:
  -q --quiet            Print less text.
                        [default: false]
  -v --verbose          Print more text.
                        [default: false]
  --no-color            Don't render messages using colors. On output 
                        redirection no colors are used.
                        [default: false]
  --force-color         Even on redirected output enforce the rendering of 
                        messages using colors. On Windows, ANSII support must 
                        be compiled into.
                        [default: false]

Warning Options:
  --Wall                Warn all.
  --Wunused             Warn on unused.
  --Wother              Warn for others.
)";
// ------+---------+---------+---------+---------+---------+---------+---------| 80

void init::parse_cli(int argc, const char* argv[])
{
    using namespace docopt;

    using boost::locale::format;
    using boost::locale::translate;

    std::vector<std::string> const args{argv + 1, argv + argc};

#if 0
    auto const print_args = [](std::ostream& os, std::vector<std::string> const& args) {
		os << "(command line user argument(s) [N=" << args.size() << "]\n";
		std::copy(args.begin(), args.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        os << ")\n";
    };

    print_args(std::cout, args);
#endif

    try {
        std::map<std::string, value> arg_map = docopt_parse(USAGE, args);

        for (auto const& [key, value] : arg_map) {
        	if (!eval_doccpp_option(key, value)) {
                std::cout << USAGE << std::endl;
                std::exit(EXIT_FAILURE);
        	}
        }

        // set secondary triggered options
        eda::settings::option_trigger trigger;

        trigger.add("--Wall", { "--Wunused", "--Wother" });
        trigger.update(setting);
    }
    catch (DocoptExitHelp const&) {
        std::cout << USAGE << std::endl;
        std::exit(EXIT_SUCCESS);
    }
    catch (DocoptExitVersion const&) {
        std::cout << VERSION_STR << std::endl;
        std::exit(EXIT_SUCCESS);
    }
    catch (DocoptLanguageError const& error) {
        std::cerr << format(translate(
                     "Command line arguments could not be parsed: {1}\n"))
                      % error.what();
        std::cout << USAGE << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (DocoptArgumentError const& error) {
        std::cerr << format(translate(
                     "DocOpt++ argument error: {1}\n"))
                      % error.what();
        std::cout << USAGE << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


bool init::eval_doccpp_option(std::string const& key, docopt::value const& value)
{
	//std::cout << "eval docopt++ option: " << key << " : " << value << "\n";

	auto const match = [](std::string const& key_, std::initializer_list<const char*> primary) {
		return std::any_of(primary.begin(), primary.end(),
		                   [&](const char* other){ return key_.compare(other) == 0; });
	};

	auto const set_bool = [&](auto const& key_, auto const& value_) {
    	if (value_ && !value_.asBool()) {
    		return;
    	}
    	setting.set(key_) = "true";
	};

	auto const set_string = [&](auto const& key_, auto const& value_) {
    	if (!value_ || !value_.isString()) {
    		return;
    	}
    	setting.set(key_) = value_.asString();
	};

	// Analyze and set options

    if (match(key, { "<file>" })) {

    	std::vector<std::string> const& file_list = value.asStringList();

    	using eda::util::file_loader;
    	file_loader file_check{ std::cerr, setting };

    	// early check to avoid aborting due to missing/duplicate files later on
    	if (!file_check.unique_files(file_list)) {
    		// immediately exit, no usage info wanted by caller
    		std::exit(EXIT_FAILURE);
    	}

    	// XXX variant required !!!
    	// config.set(key) = file_list;
    	sourcefile_list = file_list;
    }

    if (match(key, { "--analyse" })) {
    	set_bool(key, value);
    }

    if (match(key, { "--quiet", "--verbose" })) {
    	set_bool(key, value);
    }

    if (match(key, { "--libpath" })) {
        set_string(key, value);
    }

    if (match(key, { "--no-color" })) {
    	set_bool(key, value);
    }

    if (match(key, { "--force-color" })) {
#if BOOST_OS_WINDOWS && !EDA_ON_WINDOWS_USE_ANSII_COLOR
    	if (!value.asBool()) {
    		return true;
    	}

    	using eda::color::message::warning;
    	std::cerr << warning("Warning: Using Window's Console I/O prevents "
    			             "redirection of colored messages")
    			  << "; ignore '--force-color'"
				  << "\n";
#else
    	set_bool(key, value);
#endif
    }

    if (match(key, { "--Wall", "--Wunused", "--Wother" })) {
        set_bool(key, value);
    }

    return true;
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


} // namespace ibis

