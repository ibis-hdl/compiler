#pragma once

#include <boost/test/tools/output_test_stream.hpp>

#include <ibis/vhdl/parser/skipper.hpp>
#include <ibis/vhdl/parser/grammar_decl.hpp>
#include <ibis/vhdl/parser/parser_config.hpp>

#include <ibis/vhdl/ast/ast_printer.hpp>
#include <ibis/util/pretty_typename.hpp>

#include <iostream>
#include <filesystem>

#include <testsuite/namespace_alias.hpp>

namespace testsuite::vhdl::parser::util {

template <typename AttrType = x3::unused_type>
struct testing_parser {
    using attribute_type = AttrType;

    template <typename ParserType>
    std::tuple<bool, std::string> operator()(std::string const &input,
                                             ParserType const &parser_rule,
                                             fs::path const &filename = "", bool full_match = true)
    {
        parser::position_cache<parser::iterator_type> position_cache;
        std::size_t const id = position_cache.add_file(filename.generic_string() + ".input", input);

        btt::output_test_stream output;

        parser::error_handler_type error_handler{ output, position_cache.handle(id) };

        auto const parser =
            x3::with<parser::error_handler_tag>(std::ref(error_handler))[parser_rule];

        auto [iter, end] = position_cache.range(id);

        // using different iterator_types causes linker errors, see e.g.
        // [linking errors while separate parser using boost spirit x3](
        //  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3)
        //
        static_assert(std::is_same_v<decltype(iter), parser::iterator_type>,
                      "iterator types must be the same");

        if constexpr (false) {
            std::cerr << "##### get testing_parser<"
                      << ibis::util::pretty_typename<decltype(iter)>{} << ">\n";
            std::cerr << "##### expect testing_parser<"
                      << ibis::util::pretty_typename<parser::iterator_type>{} << ">\n";
        }

        bool parse_ok = false;
        attribute_type attr;

        try {
            parse_ok = x3::phrase_parse(iter, end, parser, parser::skipper, attr);

            if (parse_ok) {
                if (iter != end) {
                    error_handler(iter,
                                  "Test Suite Full Match Error! "
                                  "Unparsed input left:\n" +
                                      std::string(iter, end));
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
            error_handler(e.where(), "Test Suite caught expectation_failure! Expecting " +
                                         e.which() + " here: '" +
                                         std::string(e.where(), input.end()) + "'\n");
        }

        return std::tuple{ parse_ok && (!full_match || (iter == end)), output.str() };
    }
};

}  // namespace testsuite::vhdl::parser::util
