/*
 * main.cpp
 *
 *  Created on: 29.07.2018
 *      Author: olaf
 */

// clang-format off
#include <ibis/init.hpp>
#include <eda/settings.hpp>
#include <eda/util/file/file_loader.hpp>
// clang-format on

#include <eda/color/message.hpp>
#include <eda/support/boost/locale.hpp> // IWYU pragma: keep

#include <cstdlib>
#include <exception>
#include <iostream>

extern void testing_signal_handler();

int main(int argc, const char* argv[])
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
    using namespace eda::color;

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
                std::cerr << message::note(translate("processing:")) << " "
                          << filename << '\n';
            }

            // XXX since we aren't functional, simply print the contents

            std::cout << "------------------------------------------------\n"
            		  << *contents << '\n'
            		  << "------------------------------------------------\n";
        }

        // testing_signal_handler(); // just testing
    } catch (std::exception const& e) {
        // clang-format off
        std::cerr << message::failure(translate("Exception caught:")) << " "
                  << e.what() << '\n';
        // clang-format on
    } catch (...) {
        std::cerr << message::failure(translate("Unexpected exception caught")) << '\n';
    }

    return EXIT_SUCCESS;
}
