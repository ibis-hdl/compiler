/*
 * init.cpp
 *
 *  Created on: 07.08.2018
 *      Author: olaf
 */

#include <ibis/init.hpp>

#include <eda/configuration.hpp>

#include <eda/util/file/file_reader.hpp>
#include <eda/color/message.hpp>

#include <eda/support/boost/locale.hpp>

#include <docopt.h>

#include <cstdlib>
#include <memory>


extern bool register_gdb_signal_handler();


namespace ibis {


init::init(int argc, const char* argv[], eda::configuration& config_)
: config{ config_ }
{
	parse_env();
	parse_cli(argc, argv);

	set_color_messages();
	register_signal_handlers();
}


void init::parse_env()
{
    auto const getenv = [](std::string const& key) {
        char const* val = std::getenv( key.c_str() );
        return val == NULL ? std::string{} : std::string(val);
    };

    // pure ENV name used for configuration
    auto const set_option = [&](std::string const& env_name) {
        std::string const env_var{ getenv(env_name) };
        if (!env_var.empty()) {
            config[env_name] = env_var;
        }
    };

    // key used for configuration to allow overriding them on command line
    auto const set_option_key = [&](std::string const& env_name, std::string const& key_name) {
        std::string const env_var{ getenv(env_name) };
        if (!env_var.empty()) {
            config[key_name] = env_var;
        }
    };

    set_option("HOME");
    set_option_key("EDA_LIBPATH", "libpath");
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
  -q --quiet            Print less text [default: false].
  -v --verbose          Print more text [default: false].
  -h --help             Show this screen.
  --version             Show version.

Color Options:
  --no-color            Don't render messages using colors. On output 
                        redirection no colors are used.
  --force-color         Even on redirected output enforce the rendering 
                        of messages using colors.

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
        eda::configuration::option_trigger trigger;

        trigger.add("--Wall", { "--Wunused", "--Wother" });
        trigger.update(config);
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
    	config[key_] = "true";
	};

	auto const set_string = [&](auto const& key_, auto const& value_) {
    	if (!value_ || !value_.isString()) {
    		return;
    	}
    	config[key_] = value_.asString();
	};

	// Analyze and set options

    if (match(key, { "<file>" })) {

    	std::vector<std::string> const& file_list = value.asStringList();

    	using eda::util::file_loader;
    	file_loader file_check{ std::cerr };

    	// early check too avoid aborting due to missing/duplicate files later on
    	if (!file_check.unique_files(file_list)) {
    		// immediately exit, no usage info wanted by caller
    		std::exit(EXIT_FAILURE);
    	}

    	// XXX variant required !!!
    	// config[key] = file_list;
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

    if (match(key, { "--no-color", "--force-color" })) {
    	set_bool(key, value);
    }

    if (match(key, { "--Wall", "--Wunused", "--Wother" })) {
        set_bool(key, value);
    }

    return true;
}


void init::set_color_messages()
{
    bool const force_color = [&] {
        if (config("force-color")) return true;
        return false;
    }();

    if (config("no-color") && !force_color) {
        // no color wanted
        return;
    }

    auto const imbue = [](auto& stream, auto&& facet_ptr) {
        std::locale locale(std::locale(), facet_ptr.release());
        stream.imbue(locale);
    };

    using namespace eda::color;
    using namespace eda::color::message;

    /* black, red, green, yellow, blue, magenta,_cyan, white */
    // prototypes
    auto const note_format    = fg::green;
    auto const warning_format = fg::yellow;
    auto const error_format   = fg::magenta | text::bold;
    auto const failure_format = fg::red     | text::bold | bg::white;

    imbue(std::cerr, std::make_unique<note_facet>(
        note_format, color_off, force_color)
    );
    imbue(std::cerr, std::make_unique<warning_facet>(
        warning_format, color_off, force_color)
    );
    imbue(std::cerr, std::make_unique<error_facet>(
        error_format, color_off, force_color)
    );
    imbue(std::cerr, std::make_unique<failure_facet>(
        failure_format, color_off, force_color)
    );
}

void init::register_signal_handlers()
{
#if defined(EDA_WITH_GDB_STACKTRACE)
    using failure = eda::color::message::failure;

    if (!register_gdb_signal_handler()) {
        std::cerr << failure("Failed to install signal handlers") << "\n";
        std::exit(EXIT_FAILURE);
    }
#endif
}


} // namespace ibis

