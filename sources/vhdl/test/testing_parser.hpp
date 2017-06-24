/*
 * testing_parser.hpp
 *
 *  Created on: 29.03.2017
 *      Author: olaf
 */

#ifndef SOURCES_VHDL_TEST_TESTING_PARSER_HPP_
#define SOURCES_VHDL_TEST_TESTING_PARSER_HPP_

#include <boost/test/output_test_stream.hpp>
#include <eda/vhdl/ast_printer.hpp>
#include <eda/vhdl/parser/grammar_def.hpp>
#include <eda/vhdl/parser/parser_config.hpp>


namespace x3_test {

namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl::parser;
namespace ast    = eda::vhdl::ast;


template <
    typename AttrType = x3::unused_type
>
struct testing_parser
{
    typedef AttrType                    attribute_type;

    template <typename ParserType>
    std::tuple<bool, std::string>
    operator()(
        std::string const &input,
        ParserType const &parser_rule,
        bool full_match = true
        )
    {
        attribute_type  attr;
        btt::output_test_stream output;

        parser::iterator_type iter = input.begin();
        parser::iterator_type const end = input.end();

        parser::error_handler_type error_handler(iter, end, output);

        auto const parser =
            x3::with<x3::error_handler_tag>(std::ref(error_handler))
            [
                  parser_rule
            ];

        bool success = false;

        try {
            success = x3::phrase_parse(iter, end, parser, parser::skipper, attr);

            if (success) {
                if (iter != end) {
                    error_handler(iter, "Error! Expecting end of input here: ");
                }
                else {
                    ast::printer print(output);
                    print.verbose_symbol = true;
                    print.verbose_variant = true;
                    print(attr);
                }
            }
        } catch(x3::expectation_failure<parser::iterator_type> const& e) {
            /* ToDo: Some investigating is required here - BNF and X3. Both
             * message creations differs in the point of concrete failure. My
             * guess is the first approach of error printing is correct, but
             * BNF must be studied carefully. A testing use case for this is
             * 'expression_failure/expression_failure_003' with enabled expectation
             * point at term rule (term_def):
             * 'In line 2:
             * Error! Expecting end of input here:
             * -5 mod -3
             * ___^_
             * vs.
             * 'In line 2:
             * Error! Expecting factor here:
             * -5 mod -3
             * _______^_
             * (or alternative 'Error! Expecting factor at ' -3') if enabled
             */
#if 1
            output << "Error! Expecting " << e.which()
                   << " at '" << std::string(e.where(), input.end()) << "'\n";
#else
            error_handler(e.where(), "Error! Expecting " + e.which() + " here: ");
#endif
        }

        return std::make_tuple(
            success && (!full_match || (iter == end)),
            output.str()
        );
    }
};


} // namespace x3_test



#endif /* SOURCES_VHDL_TEST_TESTING_PARSER_HPP_ */
