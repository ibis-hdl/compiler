#include <ibis/frontend/init.hpp>

#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/ast.hpp>

#include <ibis/vhdl/ast/ast_printer.hpp>

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

    using namespace ibis;
    using namespace ibis::color;

    namespace parser = ibis::vhdl::parser;
    namespace ast = ibis::vhdl::ast;

    try {
        ibis::frontend::init init(argc, argv);

        bool const quiet = [&] { return ibis::settings::instance().get<bool>("quiet"); }();
        unsigned const verbose_level = [&] {
            return ibis::settings::instance().get<unsigned>("verbose");
        }();

        if (verbose_level > 1) {
            ibis::settings::dump(std::cout);
            std::cout << '\n';
        }

        constexpr bool test_color = false;

        util::file_loader file_reader{ std::cerr };

        if constexpr ((test_color)) {
            std::cerr << color::message::failure("FAILURE") << " Format Test\n";
            std::cerr << color::message::error("ERROR") << " Format Test\n";
            std::cerr << color::message::warning("WARNING") << " Format Test\n";
            std::cerr << color::message::note("NOTE") << " Format Test\n";
        }

        // Quick & Dirty main() function to test the parser from command line
        parser::position_cache<parser::iterator_type> position_cache;
        parser::parse parse{ std::cout };
        parser::context ctx;

        for (auto const& child : settings::instance().get_child("hdl-files")) {
            std::string_view const hdl_file = child.second.data();
            // FixMe: Throw on read_file(), no optional!!
            auto const contents = file_reader.read_file(hdl_file);
            if (!quiet) {
                std::cout << message::note(                             // --
                                 (format(translate("processing: {1}"))  // --
                                  % hdl_file)
                                     .str())
                          << '\n';
            }

            // render the source with lines numbers (quick & dirty solution)
            uint16_t line_no = 1;
            std::istringstream iss(*contents);
            std::cout << "------------------- input ----------------------\n";
            for (std::string line; std::getline(iss, line, '\n'); line_no++) {
                std::cout << std::setfill(' ') << std::setw(3) << line_no << " | "  // --
                          << line << '\n';
            }
            std::cout << "------------------------------------------------\n";

            // prepare to parse
            auto position_cache_proxy = position_cache.add_file(hdl_file, *contents);

            ast::design_file design_file;

            parse(position_cache_proxy, ctx, design_file);

            if (!quiet) {
                ast::printer ast_printer{ std::cout };
                ast_printer.verbose_symbol = true;
                ast_printer.verbose_variant = false;
                ast_printer(design_file);
            }
        }

        // FixMe: plural_count copy & paste from context.cpp, make it re-useable
        auto const plural_count = [](size_t count) {
            if (count > std::numeric_limits<int>::max()) {
                return std::numeric_limits<int>::max();
            }
            return static_cast<int>(count);
        };

        std::cout << message::note(          // --
                         (format(translate(  // --
                              "processed {1} file", "processed {1} files",
                              plural_count(position_cache.file_count())))  // --
                          % position_cache.file_count())
                             .str())
                  << '\n';
        if (!ctx.issue_free()) {
            std::cout << vhdl::failure_status(ctx) << '\n';
        }

        // testing_signal_handler(); // just testing
    }
    catch (boost::spirit::x3::expectation_failure<vhdl::parser::iterator_type> const& e) {
        // This shouldn't be happen!
        std::cerr << message::failure(                                                       // --
                         (format(translate(                                                  // --
                              "caught unhandled Boost.Spirit X3 expectation_failure: {1}"))  // --
                          % e.what())
                             .str())
                  << '\n';
    }
    catch (std::exception const& e) {
        std::cerr << message::failure(                   // --
                         (format(translate(              // --
                              "Exception caught: {1}"))  // --
                          % e.what())
                             .str())
                  << '\n';
    }
    catch (...) {
        std::cerr << message::failure(translate("Unexpected exception caught")) << '\n';
    }

    return EXIT_SUCCESS;
}
