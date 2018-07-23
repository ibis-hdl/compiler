/*
 * testing_parser.hpp
 *
 *  Created on: 29.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_HPP_
#define SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_HPP_

#include <boost/test/output_test_stream.hpp>

#include <eda/vhdl/parser/skipper.hpp>
#include <eda/vhdl/parser/grammar_decl.hpp>
#include <eda/vhdl/parser/parser_config.hpp>

#include <eda/vhdl/ast_printer.hpp>

#include <testsuite/namespace_alias.hpp>


namespace testsuite { namespace vhdl_parser { namespace util {


template <
    typename AttrType = x3::unused_type
>
struct testing_parser
{
    typedef AttrType                                attribute_type;

    template <typename ParserType>
    std::tuple<bool, std::string>
    operator()(std::string const &input, ParserType const &parser_rule,
               fs::path const &filename = "", bool full_match = true)
    {
        attribute_type                              attr;
        btt::output_test_stream                     output;

        parser::position_cache<parser::iterator_type> position_cache(input);
        parser::error_handler_type error_handler(output, position_cache,
                                                 filename.generic_string() + ".input");

        auto const parser =
            x3::with<parser::error_handler_tag>(std::ref(error_handler)) [
                  parser_rule
            ];

        parser::iterator_type iter = input.begin();
        parser::iterator_type end  = input.end();

        /* using different iterator_types causes linker errors, see e.g.
         * [linking errors while separate parser using boost spirit x3](
         *  https://stackoverflow.com/questions/40496357/linking-errors-while-separate-parser-using-boost-spirit-x3) */
        static_assert(std::is_same<decltype(iter), parser::iterator_type>::value
                   && std::is_same<decltype(end),  parser::iterator_type>::value,
                      "iterator types must be the same"
        );

        bool parse_ok = false;

        try {
            parse_ok = x3::phrase_parse(iter, end, parser, parser::skipper, attr);

            if (parse_ok) {
                if (iter != end) {
                    error_handler(iter, "Test Suite Full Match Error! "
                                        "Unparsed input left:\n"
                                        + std::string(iter, end));
                }
                else {
                    ast::printer print(output);
                    print.verbose_symbol = true;
                    print.verbose_variant = true;
                    print(attr);
                }
            }
        } catch(x3::expectation_failure<parser::iterator_type> const& e) {
            error_handler(e.where(), "Test Suite caught expectation_failure! Expecting "
                          + e.which() + " here: '"
                          + std::string(e.where(), input.end()) + "'\n"
                          );
        }

        return std::make_tuple(
            parse_ok && (!full_match || (iter == end)),
            output.str()
        );
    }

};



} } } // namespace testsuite.vhdl_parser.util



#endif /* SOURCES_VHDL_TEST_INCLUDE_TESTSUITE_VHDL_PARSER_TESTING_PARSER_HPP_ */
