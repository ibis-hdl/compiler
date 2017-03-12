/*
 * basic_production_rules.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>

#include <eda/vhdl93/parser_config.hpp>
#include <eda/vhdl93/grammar_def.hpp>

#include <iostream>
#include <boost/optional/optional_io.hpp>

BOOST_AUTO_TEST_SUITE( basic_productions )


namespace x3_test {

    namespace parser = eda::vhdl93::parser;


    template <typename Parser, typename Skipper>
    bool test(
          std::string const& input
        , Parser const& parser
        , Skipper const& skipper
        , bool full_match = true)
    {
        parser::iterator_type iter = input.begin();
        parser::iterator_type const end = input.end();

        return boost::spirit::x3::phrase_parse(iter, end, parser, skipper)
               && (!full_match || (iter == end));
    }

    template <typename Parser, typename Skipper, typename Attr>
    bool test_attr(
          std::string const& input
        , Parser const& parser
        , Skipper const& skipper
        , Attr& attr
        , bool full_match = true)
    {
        parser::iterator_type iter = input.begin();
        parser::iterator_type const end = input.end();

        return boost::spirit::x3::phrase_parse(iter, end, parser, skipper, attr)
               && (!full_match || (iter == end));
    }

}


namespace x3 = boost::spirit::x3;


BOOST_AUTO_TEST_CASE( string_literal )
{
	using namespace eda::vhdl93;
	using x3_test::test_attr;

    std::vector<std::pair<std::string, std::string>> const pass_test_cases {
        std::make_pair("\"Both S and Q equal to 1\"",
                "Both S and Q equal to 1"),
        std::make_pair("\"Characters such as $, %, and } are allowed in string literals.\"",
                "Characters such as $, %, and } are allowed in string literals."),
        std::make_pair("\"& ' ( ) * + , - . / : ; < = > | [ ]\"",
                "& ' ( ) * + , - . / : ; < = > | [ ]"),
        std::make_pair("\"Quotation: \"\"REPORT...\"\" is also allowed\"",
                "Quotation: \"REPORT...\" is also allowed"),
        std::make_pair("%see \"LRM 13.10\", it's legal VHDL%",
                "see \"LRM 13.10\", it's legal VHDL"),
        std::make_pair("%Quotation: %%REPORT...%% is also allowed%",
                "Quotation: %REPORT...% is also allowed"),
        };

    std::vector<std::string> const fail_test_cases {
        "\"Both S and Q equal to 1", // missing closing '"'
        };

    uint n = 0;
	for(auto const& str : pass_test_cases) {
	    BOOST_TEST_CONTEXT("test case #" << n++ << " to pass") {
	        std::string const& input = str.first;
	        std::string const& gold = str.second;
	        std::string attr;
            BOOST_TEST_INFO("input = '" << input << "'");
	        BOOST_TEST(test_attr(input, parser::string_literal, x3::space, attr));
	        BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
	        BOOST_TEST(gold.compare(attr) == 0);
	    }
	}

	n = 0;
    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("test case #" << n++ << " to fail") {
            std::string attr;
            BOOST_TEST_INFO("input = '" << str << "'");
            BOOST_TEST(!test_attr(str, parser::string_literal, x3::space, attr));
        }
    }
}


BOOST_AUTO_TEST_CASE( integer )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    std::vector<std::pair<std::string, uint32_t>> const pass_test_cases {
        std::make_pair("0", 0),
        std::make_pair("1", 1),
        std::make_pair("1_000", 1000),
        std::make_pair("42_666_4711", 426664711),
        std::make_pair("4_294_967_295", 4294967295) // uint32::max
    };

    std::vector<std::string> const fail_test_cases {
        "4_294_967_296", // greater uint32::max
        "4_294_967_295_0",
        "4_294_967_295_00",
        "_42",
        //"42_",  // FixMe: This test shouldn't pass!
        };

    uint n = 0;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("test case #" << n++ << " to pass") {
            std::string const& input = str.first;
            uint32_t const gold = str.second;
            uint32_t attr;
            BOOST_TEST_INFO("input = '" << input << "'");
            BOOST_TEST(test_attr(input, parser::integer, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(gold == attr);
        }
    }

    n = 0;
    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("test case #" << n++ << " to fail") {
            uint32_t attr;
            BOOST_TEST_INFO("input = '" << str << "'");
            BOOST_TEST(!test_attr(str, parser::integer, x3::space, attr));
        }
    }
}


BOOST_AUTO_TEST_CASE( based_literal )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    typedef ast::based_literal attribute_type;

    std::vector<std::pair<std::string, ast::based_literal>> const pass_test_cases {
        // Integer literals of value 255:
        std::make_pair("2#1111_1111#",
                attribute_type { 2, "11111111", boost::optional<std::string>(), 1}),
        std::make_pair("16#FF#",
                attribute_type { 16, "FF", boost::optional<std::string>(), 1}),
        std::make_pair("016#0FF#",
                attribute_type { 16, "0FF", boost::optional<std::string>(), 1}),
        // Integer literals of value 224
        std::make_pair("16#E#E1",
                attribute_type { 16, "E", boost::optional<std::string>(), 1}),
        std::make_pair("2#1110_0000#",
                attribute_type { 2, "11100000", boost::optional<std::string>(), 1}),
        // Real literals of value 4095.0
        std::make_pair("16#F.FF#E+2",
                 attribute_type { 16, "F", std::string("FF"), 2}),
        std::make_pair("2#1.1111_1111_111#E11",
                 attribute_type { 2, "1", std::string("11111111111"), 11}),
    };

    uint n = 0;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("test case #" << n++ << " to pass") {
            std::string const& input = str.first;
            attribute_type const gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input = '" << input << "'");
            BOOST_TEST(test_attr(input, parser::based_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(gold.base == attr.base);
            BOOST_TEST(gold.integer_part == attr.integer_part);
            BOOST_TEST(gold.fractional_part == attr.fractional_part);
            BOOST_TEST(gold.exponent == attr.exponent);
        }
    }

}




BOOST_AUTO_TEST_SUITE_END()


