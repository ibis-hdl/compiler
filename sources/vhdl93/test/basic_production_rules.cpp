/*
 * basic_production_rules.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>

#include <eda/vhdl93/parser_config.hpp>
#include <eda/vhdl93/grammar_def.hpp>


BOOST_AUTO_TEST_SUITE( basic_productions )


namespace x3_test {

    template <typename Parser, typename Skipper>
    bool test(
          std::string const& input
        , Parser const& parser
        , Skipper const& skipper
        , bool full_match = true)
    {
        typedef std::string::const_iterator iterator_type;

        iterator_type iter = input.begin();
        iterator_type const end = input.end();

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
        typedef std::string::const_iterator iterator_type;

        iterator_type iter = input.begin();
        iterator_type const end = input.end();

        return boost::spirit::x3::phrase_parse(iter, end, parser, skipper, attr)
               && (!full_match || (iter == end));
    }

}


namespace x3 = boost::spirit::x3;


BOOST_AUTO_TEST_CASE( string_literal )
{
	using namespace eda::vhdl93;
	using x3_test::test_attr;

    std::vector<std::string> const pass_test_cases {
        "\"Both S and Q equal to 1\"",
        "\"Characters such as $, %, and } are allowed in string literals.\"",
        "\"& ' ( ) * + , - . / : ; < = > | [ ]\"",
        "\"Quotation: \"\"REPORT...\"\" is also allowed\"",
        "%see \"LRM 13.10\", it's legal VHDL%",
        "%Quotation: %%REPORT...%% is also allowed%",
        };

    std::vector<std::string> const fail_test_cases {
        "\"Both S and Q equal to 1", // missing closing '"'
        };

	auto& parser = parser::string_literal;
	std::string attr;

	for(auto const& str : pass_test_cases) {
	    BOOST_TEST_CONTEXT("test cases to PASS") {
	        BOOST_TEST_INFO("input = '" << str << "'");
	        BOOST_TEST(test_attr(str, parser, x3::space, attr));
	    }
	}

    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("test cases to FAIL") {
            BOOST_TEST_INFO("input = '" << str << "'");
            BOOST_TEST(!test_attr(str, parser, x3::space, attr));
        }
    }

}




BOOST_AUTO_TEST_SUITE_END()


