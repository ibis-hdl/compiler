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

    template <typename Char, typename Parser, typename Skipper>
    bool test(
          Char const *test_input
        , Parser const& parser
        , Skipper const& skipper
        , bool full_match = true)
    {
        std::string const input { test_input };
        typedef std::string::const_iterator iterator_type;

        iterator_type iter = input.begin();
        iterator_type const end = input.end();

        return boost::spirit::x3::phrase_parse(iter, end, parser, skipper)
               && (!full_match || (iter == end));
    }

}


namespace x3 = boost::spirit::x3;


BOOST_AUTO_TEST_CASE( string_literal )
{
	using namespace eda::vhdl93;
	using x3_test::test;

	auto& parser = parser::string_literal;


    BOOST_TEST(test("\"Both S and Q equal to 1\"",
            parser, x3::space));

    BOOST_TEST(test("\"Characters such as $, %, and } are allowed in string literals.\"",
            parser, x3::space));

    BOOST_TEST(test("\"& ' ( ) * + , - . / : ; < = > | [ ]\"",
            parser, x3::space));

    BOOST_TEST(test("\"Quotation: \"\"REPORT...\"\" is also allowed\"",
            parser, x3::space));

}

#if 0
BOOST_AUTO_TEST_CASE( test_case2 )
{
  BOOST_TEST_REQUIRE( 1 == 2 );
  BOOST_FAIL( "Should never reach this line" );
}
#endif



BOOST_AUTO_TEST_SUITE_END()




#if 0
#include "grammar_api.hpp"


BOOST_AUTO_TEST_SUITE( test_suite1 )

BOOST_AUTO_TEST_CASE( test_case1 )
{
  BOOST_TEST_WARN( sizeof(int) < 4U );
}

BOOST_AUTO_TEST_CASE( test_case2 )
{
  BOOST_TEST_REQUIRE( 1 == 2 );
  BOOST_FAIL( "Should never reach this line" );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( test_suite2 )

BOOST_AUTO_TEST_CASE( test_case3 )
{
  BOOST_TEST( true );
}

BOOST_AUTO_TEST_CASE( test_case4 )
{
  BOOST_TEST( false );
}

BOOST_AUTO_TEST_SUITE_END()
#endif
