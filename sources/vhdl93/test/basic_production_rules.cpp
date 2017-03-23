/*
 * basic_production_rules.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <eda/vhdl93/parser/grammar_def.hpp>
#include <eda/vhdl93/parser/parser_config.hpp>

#include <eda/exception.hpp>

#include <boost/optional/optional_io.hpp>
#include <iostream>

#include <eda/vhdl93/ast_printer.hpp>

BOOST_AUTO_TEST_SUITE( basic_productions )


namespace btt = boost::test_tools;
namespace x3 = boost::spirit::x3;


namespace x3_test {

    namespace parser = eda::vhdl93::parser;


    struct cerr_redirect {
        cerr_redirect(std::ostream& os)
            : m_bak(std::cerr.rdbuf(os.rdbuf())) // save and redirect
        {  }

        ~cerr_redirect() {
            std::cerr.rdbuf( m_bak );
        }

    private:
        std::streambuf* m_bak;
    };


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
        btt::output_test_stream output; // sink all error handler messages
        {
            cerr_redirect guard(output);

            parser::iterator_type iter = input.begin();
            parser::iterator_type const end = input.end();

            parser::error_handler_type error_handler(iter, end, std::cerr);

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
    }


} // namespace x3_test



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

    uint n = 1;
	for(auto const& str : pass_test_cases) {
	    BOOST_TEST_CONTEXT("'string_literal' test case #" << n++ << " to pass:") {
	        std::string const& input = str.first;
	        std::string const& gold = str.second;
	        std::string attr;
            BOOST_TEST_INFO("input ='" << input << "'");
	        BOOST_TEST(test_attr(input, parser::string_literal, x3::space, attr));
	        BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
	        BOOST_TEST(attr == gold, btt::per_element());
	    }
	}

	n = 1;
    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("'string_literal' test case #" << n++ << " to fail:") {
            std::string attr;
            BOOST_TEST_INFO("with input ='" << str << "'");
            BOOST_TEST(!test_attr(str, parser::string_literal, x3::space, attr));
        }
    }
}


BOOST_AUTO_TEST_CASE( integer )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;
    using x3_test::cerr_redirect;

    typedef std::string attribute_type;

    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        std::make_pair("0", "0"),
        std::make_pair("1", "1"),
        std::make_pair("1_000", "1000"),
        std::make_pair("00_1_000", "001000"),
        std::make_pair("023", "023"),
        std::make_pair("21_47_48_36_46", "2147483646"),
        std::make_pair("2_147_483_647", "2147483647") // int32::max
    };

    std::vector<std::string> const fail_test_cases {
        "_42",
        "42_",
        };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'integer' test case #" << n++ << " to pass:") {
        	auto const& input = str.first;
        	auto const& gold = str.second;
        	attribute_type attr;
        	BOOST_TEST_INFO("input ='" << input << "'");
            BOOST_TEST(test_attr(input, parser::integer, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr == gold, btt::per_element());
        }
    }

    n = 1;
    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("'integer' test case #" << n++ << " to fail:") {
            attribute_type attr;
            BOOST_TEST_INFO("input ='" << str << "'");
            BOOST_TEST(!test_attr(str, parser::integer, x3::space, attr));
        }
    }
}


BOOST_AUTO_TEST_CASE( based_literal )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    typedef ast::based_literal attribute_type;

    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        // Integer literals of value 255:
        std::make_pair("2#1111_1111#", attribute_type {"2", "11111111#"}),
        std::make_pair("16#FF#", attribute_type {"16", "FF#"}),
        std::make_pair("016#0_FF#", attribute_type {"016", "0FF#"}),
        // Integer literals of value 224
        std::make_pair("16#E#E1", attribute_type {"16", "E#E1"}),
        std::make_pair("2#1110_0000#", attribute_type {"2", "11100000#"}),
        // Real literals of value 4095.0
        std::make_pair("16#F.FF#E+2", attribute_type {"16", "F.FF#E+2"}),
        std::make_pair("2#1.1111_1111_111#E11", attribute_type {"2", "1.11111111111#E11"}),
		// others
		std::make_pair("16#E#E123", attribute_type {"16", "E#E123"}),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
    	BOOST_TEST_CONTEXT("'based_literal' test case #" << n++ << " to pass:") {
    		auto const& input = str.first;
    		auto const& gold = str.second;
    		attribute_type attr;
    		BOOST_TEST_INFO("input ='" << input << "'");
            BOOST_TEST(test_attr(input, parser::based_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr.base == gold.base, btt::per_element());
            BOOST_TEST(attr.literal == gold.literal, btt::per_element());
        }
    }
}


BOOST_AUTO_TEST_CASE( decimal_literal )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    typedef ast::decimal_literal attribute_type;

    using tag = attribute_type::tag;

    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        // Integer literals
        std::make_pair("12", attribute_type { "12", tag::integer } ),
        std::make_pair("0",  attribute_type { "0", tag::integer } ),
        std::make_pair("1e6", attribute_type { "1e6", tag::integer } ),
        std::make_pair("123_456", attribute_type { "123456", tag::integer }),
        // Real literals
        std::make_pair("12.0", attribute_type { "12.0", tag::real } ),
        std::make_pair("0.0", attribute_type { "0.0", tag::real } ),
        std::make_pair("0.456", attribute_type { "0.456", tag::real } ),
        std::make_pair("3.14159_26", attribute_type { "3.1415926", tag::real } ),
        // Real literals with exponents
        std::make_pair("1.34E-12", attribute_type { "1.34E-12", tag::real } ),
        std::make_pair("1.0E+6", attribute_type { "1.0E+6", tag::real } ),
        std::make_pair("6.023E+24", attribute_type { "6.023E+24", tag::real } ),
    };

    std::vector<std::string> const pass_with_exception_test_cases {
        //  this is syntactically valid even if it's overflows int32
        "12345678901234567890",
        };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
    	BOOST_TEST_CONTEXT("'decimal_literal' test case #" << n++ << " to pass:") {
    	    auto const& input = str.first;
        	auto const& gold = str.second;
        	attribute_type attr;
        	BOOST_TEST_INFO("input ='" << input << "'");
            BOOST_TEST(test_attr(input, parser::decimal_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr.literal == gold.literal, btt::per_element());
            BOOST_TEST(attr.hint == gold.hint);
        }
    }

    n = 1;
    for(auto const& str : pass_with_exception_test_cases) {
        BOOST_TEST_CONTEXT("'decimal_literal' test case #" << n++ <<
        		           " to fail with overflow exception:") {
            attribute_type attr;
            BOOST_TEST_INFO("input ='" << str << "'");
            BOOST_TEST(test_attr(str, parser::decimal_literal, x3::space, attr));
            BOOST_CHECK_THROW(ast::get<int>(attr), ::eda::range_error);
        }
    }
}


BOOST_AUTO_TEST_CASE( bit_string_literal )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    typedef ast::bit_string_literal attribute_type;

    using tag = attribute_type::tag;

    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        std::make_pair("B\"1111_1111_1111\"", attribute_type {"111111111111", tag::bin}),
        std::make_pair("X\"FFF\"", attribute_type {"FFF", tag::hex}),
        std::make_pair("O\"777\"", attribute_type {"777", tag::oct}),
        std::make_pair("X\"777\"", attribute_type {"777", tag::hex}),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
    	BOOST_TEST_CONTEXT("'bit_string_literal' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input ='" << input << "'");
            BOOST_TEST(test_attr(input, parser::bit_string_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr.literal == gold.literal, btt::per_element());
            BOOST_TEST(attr.hint == gold.hint);
        }
    }
}


BOOST_AUTO_TEST_CASE( abstract_literal )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    typedef ast::abstract_literal attribute_type;

    using d_tag = ast::decimal_literal::tag;

    // {decimal|based}_literal
    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        std::make_pair("1e3", attribute_type { ast::decimal_literal {"1e3", d_tag::integer} }),
        std::make_pair("42.42e-3", attribute_type { ast::decimal_literal {"42.42e-3", d_tag::real} }),
		std::make_pair("16#0_FF#", attribute_type { ast::based_literal {"16", "0FF#"} }),
		std::make_pair("016#0_FF#e-23", attribute_type { ast::based_literal {"16", "0FF#e-23"} }),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
    	BOOST_TEST_CONTEXT("'bit_string_literal' test case #" << n++ << " to pass:") {
    	    auto const& input = str.first;
            auto const& gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input = '" << input << "'");
            BOOST_TEST(test_attr(input, parser::abstract_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
        }
    }

    attribute_type a { ast::based_literal {"16", "0FF#e-23"} };
    std::cerr << "test = '" << a << "'\n";
}


BOOST_AUTO_TEST_CASE( physical_literal )
{
    using namespace eda::vhdl93;
    using x3_test::test_attr;

    typedef ast::physical_literal attribute_type;

#if 0
    using deci_tag = ast::decimal_literal::tag;

    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        std::make_pair("100 fs", attribute_type { ast::decimal_literal{ "12", deci_tag::integer }, "fs" }),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        auto const& input = str.first;
        auto const& gold = str.second;
        attribute_type attr;
        BOOST_TEST_CONTEXT("'physical_literal' test case #" << n++ << " to pass "
                           "input ='" << input << "'") {
            BOOST_TEST(test_attr(input, parser::physical_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            //BOOST_TEST(attr.literal == gold.literal, btt::per_element());
            //BOOST_TEST(attr.hint == gold.hint);
        }
    }
#else
    // FixMe: How to create an ast attribute as reference? It's declared as ast_forward etc.
    std::vector<std::string> const pass_test_cases {
        "100 fs",
		//"ps", FixMe: This results into "Invalid code path" exception in ast/decimal_literal.cpp(71) due to empty abstract_literal
		"16#FF# ns",
		"2#1111_1111# d",
		"10#42# ms",
		"16#AFFE.42#E+69 h",
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        auto const& input = str;
        attribute_type attr;
        BOOST_TEST_CONTEXT("'physical_literal' test case #" << n++ << " to pass "
                           "input ='" << input << "'") {
            BOOST_TEST(test_attr(input, parser::physical_literal, x3::space, attr));
            BOOST_TEST_INFO("attr = '" << attr << "'");
        }
    }

#endif
}


BOOST_AUTO_TEST_SUITE_END()


