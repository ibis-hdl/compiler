/*
 * cli_options.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <docopt.h>

#include <ibis/global_options.hpp>

#include <eda/support/boost/locale.hpp>
#include <eda/util/cxx_bug_fatal.hpp>

#include <algorithm>
#include <iterator>

#include <iostream>


static const char VERSION_STR[] = "EDA/ibis 0.0.1";


static const char USAGE[] =
R"(EDA/ibis

    Usage:
      ibis <file>...

      ibis (-h | --help)            # cool
      ibis --version

    Options:
      -h --help     Show this screen.
      --version     Show version.
)";


template<typename ValueT>
bool set_global_options(std::string const& key, ValueT const& value)
{
	auto const match = [](std::string const& key_, const char* primary) {
		return key_.compare(primary) == 0;
	};


    if (match(key, "<file>")) {
        for (auto filename : value.asStringList()) {
            ibis::global_options.source_files.emplace_back(filename);
        }
    }

    return true;
}


void parse_cli(int argc, const char* argv[])
{
    using namespace docopt;

    using boost::locale::format;
    using boost::locale::translate;

    std::vector<std::string> const args{argv + 1, argv + argc};

#if 0 // CLI argc/argv debug option
    std::cout << "debug: got " << (argc - 1) << " user command line argument(s)\n"
              << "-----------------------------------------------------\n";
    std::copy(args.begin(), args.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout << "-----------------------------------------------------\n";
#endif

    try {
        std::map<std::string, value> arg_map = docopt_parse(USAGE, args);

        for (auto const& [key, value] : arg_map) {
            //std::cout << '"' << key << '"' << ": " << value << "\n";
        	if (!set_global_options(key, value)) {
                std::cout << USAGE << std::endl;
                std::exit(EXIT_FAILURE);
        	}
        }
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
