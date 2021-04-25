#include <ibis/frontend/init.hpp>

#include <ibis/settings.hpp>
#include <ibis/util/file/file_loader.hpp>

#include <ibis/color/message.hpp>
#include <ibis/color/attribute.hpp>
#include <ibis/color/facet.hpp>

#include <boost/locale/format.hpp>
#include <boost/locale/message.hpp>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

extern void testing_signal_handler();

///
/// @brief The App, used as test driver at this state.
///
/// @param argc CLI argument count.
/// @param argv CLI argument value array.
/// @return int Exist code of the application.
///
/// @todo An exception may be thrown in function 'main' which should
/// not throw exceptions [clang-tidy(bugprone-exception-escape)]
int main(int argc, const char* argv[])
{
    using boost::locale::format;
    using boost::locale::translate;

    // FixMe: try/catch block
    ibis::frontend::init init(argc, argv);

    bool const quiet = [&] { return ibis::settings::instance().get<bool>("quiet"); }();
    unsigned const verbose_level = [&] {
        return ibis::settings::instance().get<unsigned>("verbose");
    }();

    if (verbose_level > 1) {
        ibis::settings::dump(std::cout);
        std::cout << '\n';
    }

    using namespace ibis;
    using namespace ibis::color;

    constexpr bool test_color = true;

    try {
        util::file_loader file_reader{ std::cerr, quiet };

        if constexpr (test_color) {
            std::cerr << color::message::failure("FAILURE") << " Format Test\n";
            std::cerr << color::message::error("ERROR") << " Format Test\n";
            std::cerr << color::message::warning("WARNING") << " Format Test\n";
            std::cerr << color::message::note("NOTE") << " Format Test\n";
        }

        for (auto const& child : settings::instance().get_child("hdl-files")) {
            std::string_view const hdl_file = child.second.data();
            auto const contents = file_reader.read_file(hdl_file);
            if (!quiet) {
                std::cerr << message::note(translate("processing:")) << " " << hdl_file << '\n';
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
