/*
 * main.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <ibis/parse_env.hpp>
#include <ibis/parse_cli.hpp>
#include <eda/configuration.hpp>

#include <eda/util/infix_ostream_iterator.hpp>
#include <eda/util/file/file_reader.hpp>

#include <eda/color/message.hpp>

#include <iostream>
#include <memory>


extern bool register_signal_handlers();
extern void testing_signal_handler();


int main(int argc, const char *argv[])
{
	eda::configuration config;

	parse_env(config);
	auto const sources = parse_cli(argc, argv, config);

	if (config("verbose")) {
		config.dump(std::cout);
		std::cout << "processing: ";
		std::copy(sources.begin(), sources.end(),
				  eda::util::infix_ostream_iterator<std::string>(std::cout, ", "));
		std::cout << "\n";
	}

    eda::util::file_loader file_reader{ std::cerr };

    try {
        bool want_decoration = true;

        if (want_decoration) {
            using failure_facet = eda::color::message::failure_facet;

            std::unique_ptr<failure_facet> facet = std::make_unique<failure_facet>("[", "]");
            // configure the object ...

            std::locale locale(std::locale(), facet.release());
            std::cerr.imbue(locale);
        }

        for (auto const filename : sources) {
            auto const contents = file_reader.read_file(filename);
            std::cout << "------------------------------------------------\n";
            std::cout << contents;
            std::cout << "\n------------------------------------------------\n";
            std::time_t t = file_reader.timesstamp(filename);
            std::cout << "timestamp: " << t << "\n";
            std::cout << "------------------------------------------------\n";
        }

        if (!register_signal_handlers()) {
            std::cout << "Failed to install signal handlers\n";
            return EXIT_FAILURE;
        }

        testing_signal_handler(); // just testing
    }
    catch(std::exception const& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }
    catch(...) {
        std::cerr << "Unexpected exception caught\n";
    }

    return EXIT_SUCCESS;
}

