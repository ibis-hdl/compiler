/*
 * cli_options.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <docopt.h>

#include <ibis/global_options.hpp>

#include <algorithm>
#include <iterator>

#include <iostream>


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

static const char VERSION_STR[] = "EDA/ibis 0.0.1";


void parse_cli(int argc, const char* argv[])
{
    using namespace docopt;

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

            std::cout << key << '"' << ": " << value << "\n";

            if (std::string{"file"}.compare(key)) {
                for (auto const& source : value.asStringList()) {
                    ibis::global_options.source_files.push_back(source);
                }
            }
        }
    }
    catch (DocoptExitHelp const&) {
        std::cout << USAGE << std::endl;
        std::exit(0);
    }
    catch (DocoptExitVersion const&) {
        std::cout << VERSION_STR << std::endl;
        std::exit(0);
    }
    catch (DocoptLanguageError const& error) {
        std::cerr << "Command line arguments could not be parsed" << std::endl;
        std::cerr << error.what() << std::endl;
        std::cout << USAGE << std::endl;
        std::exit(-1);
    }
    catch (DocoptArgumentError const& error) {
        std::cerr << error.what();
        std::cout << std::endl;
        std::cout << USAGE << std::endl;
        std::exit(-1);
    }
}
