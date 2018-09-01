/*
 * main.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

#include <ibis/init.hpp>
#include <eda/settings.hpp>
#include <eda/util/file/file_reader.hpp>

#include <eda/color/message.hpp>
#include <eda/support/boost/locale.hpp>             // IWYU pragma: keep

#include <cstdlib>
#include <exception>
#include <iostream>


extern void testing_signal_handler();



int main(int argc, const char *argv[])
{
    using boost::locale::format;
    using boost::locale::translate;

    eda::settings setting;

    ibis::init init(argc, argv, setting);

    if (setting["verbose"]) {
        setting.dump(std::cout);
        std::cout << '\n';
    }

    using namespace eda;

    try {
        util::file_loader file_reader{ std::cerr, setting };

#if 0
        std::cerr << color::message::failure("FAILURE") <<  " Format Test\n";
        std::cerr << color::message::error("ERROR") <<  " Format Test\n";
        std::cerr << color::message::warning("WARNING") <<  " Format Test\n";
        std::cerr << color::message::note("NOTE") <<  " Format Test\n";
#endif

        for (auto const& filename : setting["files"].get<std::vector<std::string>>()) {
            auto const contents = file_reader.read_file(filename);
            if (!setting["quiet"]) {
                std::cerr << color::message::note(translate("processing:")) << " " << filename << '\n';
            }
            std::cout << "------------------------------------------------\n";
            std::cout << *contents;
            std::cout << "\n------------------------------------------------\n";
            std::time_t t = file_reader.timesstamp(filename);
            std::cout << "timestamp: " << t << '\n';
            std::cout << "------------------------------------------------\n";
        }

        //testing_signal_handler(); // just testing
    }
    catch(std::exception const& e) {
        std::cerr << color::message::failure(translate("Exception caught:"))
                  << " " << e.what()
                  << '\n';
    }
    catch(...) {
        std::cerr << color::message::failure(translate("Unexpected exception caught"))
                  << '\n';
    }

    return EXIT_SUCCESS;
}

