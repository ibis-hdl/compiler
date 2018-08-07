/*
 * main.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <ibis/init.hpp>
#include <eda/configuration.hpp>

//#include <eda/util/infix_ostream_iterator.hpp>
#include <eda/util/file/file_reader.hpp>

#include <eda/color/message.hpp>

#include <iostream>


extern void testing_signal_handler();



int main(int argc, const char *argv[])
{
	eda::configuration setting;

	ibis::init init(argc, argv, setting);

	if (setting("verbose")) {
		setting.dump(std::cout);
		std::cout << "\n";
	}

	namespace msg = eda::color::message;

    try {
        eda::util::file_loader file_reader{ std::cerr };

        using failure = msg::failure;

        std::cerr << failure("TEST") << " message\n";

        for (auto const& filename : init.file_list()) {
            auto const contents = file_reader.read_file(filename);
            if (setting("verbose")) {
            	std::cout << "processing: " << filename << "\n";
            }
            std::cout << "------------------------------------------------\n";
            std::cout << contents;
            std::cout << "\n------------------------------------------------\n";
            std::time_t t = file_reader.timesstamp(filename);
            std::cout << "timestamp: " << t << "\n";
            std::cout << "------------------------------------------------\n";
        }

        testing_signal_handler(); // just testing
    }
    catch(std::exception const& e) {
        using failure = msg::failure;
        std::cerr << failure("Exception caught:") << " " << e.what() << "\n";
    }
    catch(...) {
        using failure = msg::failure;
        std::cerr << failure("Unexpected exception caught") << "\n";
    }

    return EXIT_SUCCESS;
}

