/*
 * error_reporting.cpp
 *
 *  Created on: 17.03.2017
 *      Author: olaf
 */


#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <eda/vhdl93/parser/grammar_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>

#include <iostream>


BOOST_AUTO_TEST_SUITE( error_reporting )


namespace x3_test {

    namespace x3 = boost::spirit::x3;
    namespace parser = eda::vhdl93::parser;


    template <typename Parser, typename Skipper>
    bool test(
          std::string const& input
        , Parser const& parser_rule
        , Skipper const& skipper
        , bool full_match = true)
    {
        parser::iterator_type iter = input.begin();
        parser::iterator_type const end = input.end();

        parser::error_handler_type error_handler(iter, end, std::cout);

        auto const parser =
            x3::with<x3::error_handler_tag>(std::ref(error_handler))
            [
                parser_rule
            ];

        return boost::spirit::x3::phrase_parse(iter, end, parser, skipper)
               && (!full_match || (iter == end));
    }

    template <typename Parser, typename Skipper, typename Attr>
    bool test_attr(
          std::string const& input
        , Parser const& parser_rule
        , Skipper const& skipper
        , Attr& attr
        , bool full_match = true)
    {
        parser::iterator_type iter = input.begin();
        parser::iterator_type const end = input.end();

        parser::error_handler_type error_handler(iter, end, std::cout);

        auto const parser =
            x3::with<x3::error_handler_tag>(std::ref(error_handler))
            [
                parser_rule
            ];

        bool success = boost::spirit::x3::phrase_parse(iter, end, parser, skipper, attr);

        if (success) {
            if (iter != end) {
                error_handler(iter, "Error! Expecting end of input here: ");
            }
        }

        return success && (!full_match || (iter == end));
    }

    struct cout_redirect {
        cout_redirect( std::streambuf* new_buffer )
            : m_bak( std::cout.rdbuf( new_buffer ) )
        { }

        ~cout_redirect( ) {
            std::cout.rdbuf( m_bak );
        }

    private:
        std::streambuf* m_bak;
    };

    namespace test_parser {

        struct error_report_class;

        typedef x3::rule<error_report_class> error_report_type;

        error_report_type const error_report { "Error Report" };

        auto const error_report_def = +x3::char_("A-Za-z");

        BOOST_SPIRIT_DEFINE(error_report);
    }


} // namespace x3_test



namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

#if 0
BOOST_AUTO_TEST_CASE( simple_report )
{
    using namespace eda::vhdl93;
    using x3_test::test;
    namespace test_parser = x3_test::test_parser;



    std::string const input { "Hello World of 42!" };


    boost::test_tools::output_test_stream output;
    {
        test(input, test_parser::error_report, x3::space);
    }

    BOOST_TEST( output.is_equal("FixMe\n"));
}
#endif

#if 0
BOOST_AUTO_TEST_CASE( get_ast_values )
{
    using namespace eda::vhdl93;
    using x3_test::test;
    namespace test_parser = x3_test::test_parser;

    ast::bit_string_literal l { "111111111111111111111111111111111", ast::bit_string_literal::tag::bin };

    boost::test_tools::output_test_stream output;
    {
        std::cout << l << '\n';
    }

    BOOST_TEST( output.is_equal("FixMe\n"));
}
#endif


BOOST_AUTO_TEST_SUITE_END()

