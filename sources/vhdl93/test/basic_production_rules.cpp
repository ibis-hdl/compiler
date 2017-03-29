/*
 * basic_production_rules.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>

//#include <eda/exception.hpp>

//#include <boost/optional/optional_io.hpp>
#include <iostream>


#include "app_mock.hpp"
#include "data_set.hpp"
#include "parser_test.hpp"


/*----------------------------------------------------------------------------*/
namespace eda { namespace vhdl93 { namespace ast {


template<typename NodeType>
std::ostream& operator<<(std::ostream& os, NodeType const& node)
{
    ast::printer print(os);
    print(node);
    return os;
}


} } } // namespace eda.vhdl93.ast
/*----------------------------------------------------------------------------*/

BOOST_AUTO_TEST_SUITE( basic_productions )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


#if 0
BOOST_AUTO_TEST_CASE( string_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

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
        // empty string literal
        std::make_pair("\"\"", ""),
        // string literals of length 1.
        std::make_pair("\" \"", " "),
        std::make_pair("\"A\"", "A"),
        //std::make_pair("\"\"", "\"\""), // FixMe: This test case fails
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
            BOOST_TEST(parse(input, parser::string_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr == gold, btt::per_element());
        }
    }

    n = 1;
    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("'string_literal' test case #" << n++ << " to fail:") {
            std::string attr;
            BOOST_TEST_INFO("with input ='" << str << "'");
            BOOST_TEST(!parse(str, parser::string_literal, x3::space, attr));
        }
    }
}

BOOST_AUTO_TEST_CASE( character_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

    typedef ast::character_literal attribute_type;

    std::vector<std::pair<std::string, std::string>> const pass_test_cases {
        std::make_pair("'A'", "(character_literal=A)"),
        std::make_pair("'*'", "(character_literal=*)"),
        std::make_pair("'\''", "(character_literal=\')"),
        std::make_pair("' '", "(character_literal= )"),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'character_literal' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input =\"" << input << "\"");
            BOOST_TEST(parse(input, parser::character_literal, x3::space, attr));
            btt::output_test_stream os;
            ast::printer print(os);
            print.verbose(1);
            print(attr);
            BOOST_TEST_INFO("attr = '" << os.str() << "'");
            BOOST_TEST(gold == os.str(), btt::per_element());
        }
    }
}

BOOST_AUTO_TEST_CASE( integer )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

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
            BOOST_TEST(parse(input, parser::integer, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr == gold, btt::per_element());
        }
    }

    n = 1;
    for(auto const& str : fail_test_cases) {
        BOOST_TEST_CONTEXT("'integer' test case #" << n++ << " to fail:") {
            attribute_type attr;
            BOOST_TEST_INFO("input ='" << str << "'");
            BOOST_TEST(!parse(str, parser::integer, x3::space, attr));
        }
    }
}


BOOST_AUTO_TEST_CASE( identifier )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

    typedef ast::identifier attribute_type;

    std::vector<std::pair<std::string, std::string>> const pass_test_cases {
        // basic_identifier
        std::make_pair("X", "(identifier=X)"),
        std::make_pair("X1", "(identifier=X1)"),
        std::make_pair("VHDL93", "(identifier=VHDL93)"),
        std::make_pair("COUNT", "(identifier=COUNT)"),
        std::make_pair("STORE_NEXT_ITEM", "(identifier=STORE_NEXT_ITEM)"),
        std::make_pair("c_out", "(identifier=c_out)"),
        // extended_identifier
        std::make_pair("\\Bus\\", "(identifier=\\Bus\\)"),
        std::make_pair("\\Foo\\\\Bar\\", "(identifier=\\Foo\\\\Bar\\)"),
        std::make_pair("\\Foo\\\\Bar\\\\Baz\\", "(identifier=\\Foo\\\\Bar\\\\Baz\\)"),
        std::make_pair("\\a\\\\b\\", "(identifier=\\a\\\\b\\)"),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'identifier' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input ='" << input << "'");
            BOOST_TEST(parse(input, parser::identifier, x3::space, attr));
            btt::output_test_stream os;
            ast::printer print(os);
            print.verbose(1);
            print(attr);
            BOOST_TEST_INFO("attr = '" << os.str() << "'");
            BOOST_TEST(gold == os.str(), btt::per_element());
        }
    }
}



BOOST_AUTO_TEST_CASE( based_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

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
            BOOST_TEST(parse(input, parser::based_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr.base == gold.base, btt::per_element());
            BOOST_TEST(attr.literal == gold.literal, btt::per_element());
        }
    }
}


BOOST_AUTO_TEST_CASE( decimal_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

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
            BOOST_TEST(parse(input, parser::decimal_literal, x3::space, attr));
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
            BOOST_TEST(parse(str, parser::decimal_literal, x3::space, attr));
            BOOST_CHECK_THROW(ast::get<int>(attr), ::eda::range_error);
        }
    }
}


BOOST_AUTO_TEST_CASE( bit_string_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

    typedef ast::bit_string_literal attribute_type;

    using tag = attribute_type::tag;

    std::vector<std::pair<std::string, attribute_type>> const pass_test_cases {
        std::make_pair("B\"1111_1111_1111\"", attribute_type {"111111111111", tag::bin}),
        std::make_pair("X\"FFF\"",            attribute_type {"FFF", tag::hex}),
        std::make_pair("O\"777\"",            attribute_type {"777", tag::oct}),
        std::make_pair("X\"777\"",            attribute_type {"777", tag::hex}),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'bit_string_literal' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input ='" << input << "'");
            BOOST_TEST(parse(input, parser::bit_string_literal, x3::space, attr));
            //BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
            BOOST_TEST(attr.literal == gold.literal, btt::per_element());
            BOOST_TEST(attr.hint == gold.hint);
        }
    }
}


BOOST_AUTO_TEST_CASE( abstract_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

    typedef ast::abstract_literal attribute_type;

    using d_tag = ast::decimal_literal::tag;

    // {decimal|based}_literal
    std::vector<std::pair<std::string,  attribute_type>> const pass_test_cases {
        std::make_pair("1e3",           attribute_type { ast::decimal_literal {"1e3", d_tag::integer} }),
        std::make_pair("42.42e-3",      attribute_type { ast::decimal_literal {"42.42e-3", d_tag::real} }),
        std::make_pair("16#0_FF#",      attribute_type { ast::based_literal {"16", "0FF#"} }),
        std::make_pair("016#0_FF#e-23", attribute_type { ast::based_literal {"16", "0FF#e-23"} }),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'bit_string_literal' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input = '" << input << "'");
            BOOST_TEST(parse(input, parser::abstract_literal, x3::space, attr));
            BOOST_TEST_INFO("gold = '" << gold << "', attr = '" << attr << "'");
        }
    }
}


BOOST_AUTO_TEST_CASE( physical_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

    typedef ast::physical_literal attribute_type;

    std::vector<std::pair<std::string, std::string>> const pass_test_cases {
        std::make_pair("100 fs",             "(physical_literal={l=(v:abstract_literal=(decimal_literal={l=100, tag=int})), u=fs})"),
        /* This is an interesting test; obviously the integer value equals to
         * 1 (one), even if the ast's integer part empty. To be investigated
         * later  */
        std::make_pair("ps",                 "(physical_literal={l=(v:abstract_literal=(decimal_literal={l=, tag=int})), u=ps})"),
        std::make_pair("16#FF# ns",          "(physical_literal={l=(v:abstract_literal=(based_literal={b=16, n=FF#})), u=ns})"),
        std::make_pair("2#1111_1111# d",     "(physical_literal={l=(v:abstract_literal=(based_literal={b=2, n=11111111#})), u=d})"),
        std::make_pair("10#42# ms",          "(physical_literal={l=(v:abstract_literal=(based_literal={b=10, n=42#})), u=ms})"),
        std::make_pair("016#AFFE.42#E+69 h", "(physical_literal={l=(v:abstract_literal=(based_literal={b=016, n=AFFE.42#E+69})), u=h})")
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'physical_literal' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold  = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input = '" << input << "'");
            BOOST_TEST(parse(input, parser::physical_literal, x3::space, attr));
            btt::output_test_stream os;
            ast::printer print(os);
            print.verbose(1);
            print(attr);
            BOOST_TEST_INFO("attr = '" << os.str() << "'");
            BOOST_TEST(gold == os.str(), btt::per_element());
        }
    }
}

BOOST_AUTO_TEST_CASE( numeric_literal )
{
    using namespace eda::vhdl93;
    using x3_test::parse;

    typedef ast::numeric_literal attribute_type;

    std::vector<std::pair<std::string, std::string>> const pass_test_cases {
        // abstract_literal := decimal_literal | based_literal
        std::make_pair("1e3",             "(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=1e3, tag=int})))"),
        std::make_pair("42.42e-3",        "(v:numeric_literal=(v:abstract_literal=(decimal_literal={l=42.42e-3, tag=double})))"),
        std::make_pair("16#0_FF#",        "(v:numeric_literal=(v:abstract_literal=(based_literal={b=16, n=0FF#})))"),
        std::make_pair("016#0_FF#e-23",   "(v:numeric_literal=(v:abstract_literal=(based_literal={b=016, n=0FF#e-23})))"),
        // physical_literal
        std::make_pair("100 fs",          "(v:numeric_literal=(physical_literal={l=(v:abstract_literal=(decimal_literal={l=100, tag=int})), u=fs}))"),
        std::make_pair("16#FF# ns",       "(v:numeric_literal=(physical_literal={l=(v:abstract_literal=(based_literal={b=16, n=FF#})), u=ns}))"),
        std::make_pair("2#1111_1111# d",  "(v:numeric_literal=(physical_literal={l=(v:abstract_literal=(based_literal={b=2, n=11111111#})), u=d}))"),
        std::make_pair("10#42# ms",       "(v:numeric_literal=(physical_literal={l=(v:abstract_literal=(based_literal={b=10, n=42#})), u=ms}))"),
    };

    uint n = 1;
    for(auto const& str : pass_test_cases) {
        BOOST_TEST_CONTEXT("'numeric_literal' test case #" << n++ << " to pass:") {
            auto const& input = str.first;
            auto const& gold  = str.second;
            attribute_type attr;
            BOOST_TEST_INFO("input = '" << input << "'");
            BOOST_TEST(parse(input, parser::numeric_literal, x3::space, attr));
            btt::output_test_stream os;
            ast::printer print(os);
            print.verbose(1);
            print(attr);
            BOOST_TEST_INFO("attr = '" << os.str() << "'");
            BOOST_TEST(gold == os.str(), btt::per_element());
        }
    }
}
#endif



::x3_test::dataset_loader literal_dataset{ R"(/home/olaf/work/CXX/IBIS_SOURCE/sources/vhdl93/test/literal)" };


BOOST_DATA_TEST_CASE(literal,
literal_dataset.input() ^ literal_dataset.expect(),
    input, expect)
{
    using namespace eda::vhdl93;
    using x3_test::testing_parser;

    typedef ast::literal attribute_type;

    bool parse_ok{ false };
	std::string parse_result {};
	attribute_type attr;

	testing_parser<attribute_type> parse;
	std::tie(parse_ok, parse_result) =  parse(input, parser::literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("attr = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}



BOOST_AUTO_TEST_SUITE_END()

