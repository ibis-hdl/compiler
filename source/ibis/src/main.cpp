#include <ibis/init.hpp>

#include <eda/settings.hpp>
#include <eda/util/file/file_loader.hpp>

#include <eda/color/message.hpp>
#include <eda/color/attribute.hpp>
#include <eda/color/facet.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

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

    constexpr bool test_color = false;

    try {
        util::file_loader file_reader{ std::cerr, setting };

        if constexpr (test_color) {
            std::cerr << color::message::failure("FAILURE") << " Format Test\n";
            std::cerr << color::message::error("ERROR") << " Format Test\n";
            std::cerr << color::message::warning("WARNING") << " Format Test\n";
            std::cerr << color::message::note("NOTE") << " Format Test\n";
        }

        for (auto const& filename : setting["files"].get<std::vector<std::string>>()) {
            auto const contents = file_reader.read_file(filename);
            if (!setting["quiet"]) {
                std::cerr << message::note(translate("processing:")) << " " << filename << '\n';
            }

            // XXX since we aren't functional, simply print the contents

            std::cout << "------------------------------------------------\n"
                      << *contents << '\n'
                      << "------------------------------------------------\n";
        }

        // testing_signal_handler(); // just testing
    }
    catch (std::exception const& e) {
        std::cerr << message::failure(translate("Exception caught:")) << " " << e.what() << '\n';
    }
    catch (...) {
        std::cerr << message::failure(translate("Unexpected exception caught")) << '\n';
    }

    return EXIT_SUCCESS;
}
