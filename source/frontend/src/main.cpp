//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <ibis/frontend/init.hpp>

#include <ibis/vhdl/parser/parse.hpp>
#include <ibis/vhdl/ast.hpp>

#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/vhdl/diagnostic_formatter.hpp>

#include <ibis/settings.hpp>
#include <ibis/util/file/file_loader.hpp>
#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/message.hpp>

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

using boost::locale::format;
using boost::locale::translate;

namespace parser = ibis::vhdl::parser;
namespace ast = ibis::vhdl::ast;

using namespace ibis;

// render the source with lines numbers (quick & dirty solution)
void render_source(std::string const& contents)
{
    std::istringstream iss(contents);
    auto line_no{ 1UL };
    std::cout << std::format("{:-^80}\n", " input ");
    for (std::string line; std::getline(iss, line, '\n');) {
        using ibis::vhdl::number_gutter;
        std::cout << std::format("{}| {}\n", number_gutter{ line_no++ }, line);
    }
    std::cout << std::format("{:-^80}\n", "");
}

///
/// @brief The App, used as test driver at this state.
///
/// @param argc CLI argument count.
/// @param argv CLI argument value array.
/// @return int Exit code of the application.
///
int main(int argc, const char* argv[])
{
    using iterator_type = parser::iterator_type;

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

        /*
         * Quick & Dirty main() function to test the parser from command line
         */

        // instantiate functions required for parsing inside hdl-files loop
        util::file_loader file_reader{ std::cerr };
        util::file_mapper file_mapper{};
        parser::position_cache<iterator_type> position_cache{};
        parser::parse parse{ std::cout };
        parser::context ctx;

        // iterate over property_tree::path by using API get_child()
        for (auto const& child : settings::instance().get_child("hdl-files")) {
            std::string_view const hdl_file = child.second.data();

            auto const file_expected = file_reader.read_file(hdl_file);
            if (!file_expected) {
                auto const ec = file_expected.error();
                ibis::error(format(translate("Error loading file \"{1}\" ({2})"))  // --
                            % hdl_file % ec.message());
                return EXIT_FAILURE;
            }
            if (!quiet) {
                ibis::note((format(translate("processing: {1}")) % hdl_file));
            }

            auto file_contents{ file_expected.value() };

            render_source(file_contents);

            // prepare to parse
            auto current_file = file_mapper.add_file(hdl_file, std::move(file_contents));
            ast::design_file design_file;

            parse(std::move(current_file), position_cache, ctx, design_file);

            if (!quiet) {
                ast::printer ast_printer{ std::cout };
                ast_printer.verbose_symbol = true;
                ast_printer.verbose_variant = false;
                ast_printer(design_file);
            }
        }

        // Fix for Clang '-Weverything' diagnostic at format(translate("...", count)):
        //     warning: implicit conversion loses integer precision: 'const size_t'
        //     (aka 'const unsigned long') to 'int' [-Wshorten-64-to-32]
        // To avoid references by Clang's '-Weverything' diagnostics a plural form lambda function
        // for count value is applied. The underlying problem is that file count are of 64-bit type
        // size_t.
        // See [Boost.locale Plural Forms](
        // https://www.boost.io/doc/libs/1_87_0/libs/locale/doc/html/messages_formatting.html)
        auto const plural_count = [&]() {
            auto const count = file_mapper.file_count();
            // pessimistic/worst case scenario - count (std::Size_t) of files bigger than INT_MAX
            if (count > std::numeric_limits<int>::max()) {
                return std::numeric_limits<int>::max();
            }
            return static_cast<int>(count);
        }();

        ibis::note(                                                                        // --
            (format(translate("processed {1} file", "processed {1} files", plural_count))  // --
             % file_mapper.file_count()));

        // print error/warning state if any (failure_status takes care on it)
        std::cout << vhdl::failure_status(ctx) << '\n';

        return EXIT_SUCCESS;
    }
    catch (boost::spirit::x3::expectation_failure<vhdl::parser::iterator_type> const& e) {
        // This shouldn't be happen!
        ibis::failure(                                                                       // --
            (format(translate("caught unhandled Boost.Spirit X3 expectation_failure: {1}"))  // --
             % e.what()));
    }
    catch (std::exception const& e) {
        ibis::failure(                                     // --
            (format(translate("Exception caught: {1}\n"))  // --
             % e.what()));
    }
    catch (...) {
        ibis::failure(translate("Unexpected exception caught"));
    }

    return EXIT_FAILURE;
}
