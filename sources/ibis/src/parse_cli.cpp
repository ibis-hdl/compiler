/*
 * cli_options.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

// https://wandbox.org/permlink/0NrHlKXbw77zAOn0

#include <docopt.h>
#include <eda/configuration.hpp>

#include <eda/util/file/file_reader.hpp>
#include <eda/support/boost/locale.hpp>

#include <algorithm>
#include <iterator>

#include <iostream>


static const char VERSION_STR[] = "EDA/ibis 0.0.1";


static const char USAGE[] =
R"(EDA/ibis

    Usage:
      ibis [-q|-v] [-a]
           [--Wall --Wunused --Wother] <file> ...
      ibis (-h | --help)
      ibis --version

    Arguments:
      <file>        One or more file(s).

    Options:
      -a --analyse  Analyse.
      -q --quiet    Print less text [default: false].
      -v --verbose  Print more text [default: false].
      -h --help     Show this screen.
      --version     Show version.

    Warnings:
      --Wall        Warn all.
      --Wunused     Warn on unused.
      --Wother      Warn for others.
)";


bool set_options(std::string const& key, docopt::value const& value, eda::configuration& config)
{
	auto const match = [](std::string const& key_, const char* primary) {
		return key_.compare(primary) == 0;
	};

    auto const trim = [](std::string const& key) {
        return eda::configuration::trim(key);
    };

	auto const set_bool = [&](auto const& key_, auto const& value_) {
    	assert(value_.isBool());
    	if (value_.asBool()) {
    		config.map[trim(key_)] = "true";
    	}
	};

#if 0 // avoid unused warning
	auto const set_string = [&](auto const& key_, auto const& value_) {
    	assert(value_.isString());
    	if (!value_.asString().empty()) {
    		config.map[trim(key_)] = value_.asString();
    	}
	};
#endif

	//std::cout << "cli option: " << key << " : " << value << "\n";

    if (match(key, "--analyse")) {
    	set_bool(key, value);
    }

    if (match(key, "--quiet")) {
    	set_bool(key, value);
    }

    if (match(key, "--verbose")) {
    	set_bool(key, value);
    }

    return true;
}


std::vector<std::string> source_files_(std::vector<std::string> const& file_list);


std::vector<std::string> parse_cli(int argc, const char* argv[], eda::configuration& config)
{
    using namespace docopt;

    using boost::locale::format;
    using boost::locale::translate;

    std::vector<std::string> const args{argv + 1, argv + argc};

#if 0
    auto const print_args = [](std::ostream& os, std::vector<std::string> const& args) {
		os << "----------- " << args.size() << " user command line argument(s) ---------\n";
		std::copy(args.begin(), args.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        os << "-----------------------------------------------------\n";
    };

    print_args(std::cout, args);
#endif

    try {
        std::map<std::string, value> arg_map = docopt_parse(USAGE, args);

        for (auto const& [key, value] : arg_map) {
        	if (!set_options(key, value, config)) {
                std::cout << USAGE << std::endl;
                std::exit(EXIT_FAILURE);
        	}
        }

        eda::option_trigger trigger;
        trigger.add("--Wall", { "--Wunused", "--Wother" });
        trigger.update(config);

        return source_files_(arg_map["<file>"].asStringList());
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


std::vector<std::string> source_files_(std::vector<std::string> const& file_list)
{
	using boost::locale::translate;

    if (file_list.empty()) { // paranoia
        std::cerr << translate("No source files given.\n");
        std::exit(EXIT_FAILURE);
	}

	using eda::util::file_loader;
	file_loader file_check{ std::cerr };

	// early check too avoid aborting due to missing/duplicate files later on
	if (!file_check.unique_files(file_list)) {
		// immediately exit, no usage info wanted by caller
		std::exit(EXIT_FAILURE);
	}


	return file_list;
}

