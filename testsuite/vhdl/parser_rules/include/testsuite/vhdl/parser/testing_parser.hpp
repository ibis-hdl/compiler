//
// Copyright (c) 2017-2022 Olaf (<ibis-hdl@users.noreply.github.com>).
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <boost/test/tools/output_test_stream.hpp>

#include <ibis/vhdl/parser/skipper.hpp>
#include <ibis/vhdl/parser/grammar_decl.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

#include <ibis/util/file_mapper.hpp>
#include <ibis/vhdl/parser/position_cache.hpp>
#include <ibis/vhdl/parser/diagnostic_handler.hpp>
#include <ibis/vhdl/parser/context.hpp>
#include <ibis/vhdl/ast/ast_context.hpp>

#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/util/pretty_typename.hpp>
#include <ibis/util/get_iterator_pair.hpp>
#include <ibis/literals.hpp>

#include <iostream>
#include <filesystem>

#include <testsuite/namespace_alias.hpp>

namespace testsuite {
namespace fs = std::filesystem;
}

namespace testsuite::vhdl::parser::util {

template <typename AttrType = x3::unused_type>
struct testing_parser {
    using attribute_type = AttrType;

    template <typename ParserType>
    std::tuple<bool, std::string> operator()(std::string_view input, ParserType const &parser_rule,
                                             std::string_view filename,
                                             bool full_match = true) const
    {
        using namespace ibis::literals::memory;
        using iterator_type = parser::iterator_type;

        ibis::util::file_mapper file_mapper{};
        auto current_file = file_mapper.add_file(filename, input);
        parser::position_cache<iterator_type> position_cache{ 1_KiB };
        ibis::vhdl::ast::ast_context<iterator_type> ast_context{ current_file,
                                                                 std::ref(position_cache) };

        btt::output_test_stream output;
        parser::context vhdl_ctx;

        // clang-format off
        parser::diagnostic_handler_type diagnostic_handler{
            output, std::ref(ast_context), std::ref(vhdl_ctx)
        };
        // clang-format on

        // clang-format off
        auto const parser =
            x3::with<parser::annotator_tag>(std::ref(ast_context))[
                x3::with<parser::diagnostic_handler_tag>(std::ref(diagnostic_handler))[
                    parser_rule
                ]
            ];
        // clang-format on

        auto [iter, end] = ibis::util::get_iterator_pair(ast_context.file_contents());

        // using different iterator_types causes linker errors, see e.g.
        // [linking errors while separate parser using boost spirit x3](
        //  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3)
        //
        static_assert(std::is_same_v<                                                     // --
                          std::remove_reference_t<decltype(iter)>, parser::iterator_type  // --
                          >,
                      "iterator types must be the same");

        if constexpr ((false)) {
            std::cerr << "##### testing_parser iterator type<"
                      << ibis::util::pretty_typename<decltype(iter)>{}  // --
                      << ", "                                           // --
                      << ibis::util::pretty_typename<parser::iterator_type>{} << ">\n";
        }

        bool parse_ok = false;
        attribute_type attr;

        try {
            // FixMe: Instantiation of phrase_parse() takes the 99% of the time here
            // Even use of parser::skipper() helper doesn't change it.
            parse_ok = x3::phrase_parse(iter, end, parser, parser::skipper, attr);

            if (parse_ok) {
                if (iter != end) {
                    diagnostic_handler.parser_error(
                        iter, "Test Suite Full Match Error! Unparsed input left!");
                }
                else {
                    ast::printer print(output);
                    print.verbose_symbol = true;
                    print.verbose_variant = true;
                    print(attr);
                }
            }
        }
        catch (x3::expectation_failure<parser::iterator_type> const &e) {
            // Note: Don't use the documentation/stackoverflow.com idiom
            //   std::string(e.where(), input.end())
            // below for the error message. The chances are high, that this isn't the right error
            // position iterator - we relay on positions_cache file-iterator mapping knowledge here!
            // Otherwise it will crash there with: class std::length_error: string too long
            diagnostic_handler.parser_error(
                e.where(),
                "Test Suite caught *unexpected* expectation failure! Expecting "  // --
                    + e.which() + "\n");

            std::cerr << output.str() << '\n';
        }

        return std::tuple{ parse_ok && (!full_match || (iter == end)), output.str() };
    }
};

}  // namespace testsuite::vhdl::parser::util
