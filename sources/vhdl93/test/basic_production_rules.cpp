/*
 * basic_production_rules.cpp
 *
 *  Created on: 01.03.2017
 *      Author: olaf
 */

#include <boost/test/unit_test.hpp>
#include <boost/core/ignore_unused.hpp>

#include <iostream>

#include "data_set.hpp"
#include "testing_parser.hpp"


BOOST_AUTO_TEST_SUITE( basic_productions )


namespace x3 = boost::spirit::x3;
namespace btt = boost::test_tools;

namespace parser = eda::vhdl93::parser;
namespace ast    = eda::vhdl93::ast;


::x3_test::dataset_loader string_literal_dataset{ "test/string_literal" };
/* FixMe: What about the following string literals:
 * "FIRST PART OF A SEQUENCE OF CHARACTERS " &
 * "THAT CONTINUES ON THE NEXT LINE"
 *
 * "Sequence that includes the" & ACK & "control character"
 */

BOOST_DATA_TEST_CASE( string_literal,
      string_literal_dataset.input()
    ^ string_literal_dataset.expect()
    ^ string_literal_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::string_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::string_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader character_literal_dataset{ "test/character_literal" };

BOOST_DATA_TEST_CASE( character_literal,
      character_literal_dataset.input()
    ^ character_literal_dataset.expect()
    ^ character_literal_dataset.test_file_name(),
    input, expect, file )
{
    using x3_test::testing_parser;

    typedef ast::character_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::character_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader integer_dataset{ "test/integer" };

BOOST_DATA_TEST_CASE( integer,
      integer_dataset.input()
    ^ integer_dataset.expect()
    ^ integer_dataset.test_file_name(),
    input, expect, file )
{
    using x3_test::testing_parser;

    // Note, integer isn't an AST member
    typedef std::string attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::integer);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader integer_failure_dataset{ "test/integer_failure" };

BOOST_DATA_TEST_CASE( integer_failure,    // should fail
      integer_failure_dataset.input()
    ^ integer_failure_dataset.expect()
    ^ integer_failure_dataset.test_file_name(),
    input, expect, file )
{
    using x3_test::testing_parser;

    // Note, integer isn't an AST member
    typedef std::string attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::integer);

    BOOST_TEST(!parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader identifier_dataset{ "test/identifier" };

BOOST_DATA_TEST_CASE( identifier,
      identifier_dataset.input()
    ^ identifier_dataset.expect()
    ^ identifier_dataset.test_file_name(),
    input, expect, file )
{
    using x3_test::testing_parser;

    typedef ast::identifier attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) = parse(input, parser::identifier);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());

}


#if 0
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

#endif

::x3_test::dataset_loader bit_string_literal_dataset{ "test/bit_string_literal" };

BOOST_DATA_TEST_CASE( bit_string_literal,
      bit_string_literal_dataset.input()
    ^ bit_string_literal_dataset.expect()
    ^ bit_string_literal_dataset.test_file_name(),
    input, expect, file )
{
    using x3_test::testing_parser;

    typedef ast::bit_string_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::bit_string_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader abstract_literal_dataset{ "test/abstract_literal" };

BOOST_DATA_TEST_CASE( abstract_literal,
      abstract_literal_dataset.input()
    ^ abstract_literal_dataset.expect()
    ^ abstract_literal_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::abstract_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::abstract_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader physical_literal_dataset{ "test/physical_literal" };

BOOST_DATA_TEST_CASE( physical_literal,
      physical_literal_dataset.input()
    ^ physical_literal_dataset.expect()
    ^ physical_literal_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::physical_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::physical_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader numeric_dataset{ "test/numeric_literal" };

BOOST_DATA_TEST_CASE(numeric_literal,
      numeric_dataset.input()
    ^ numeric_dataset.expect()
    ^ numeric_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::numeric_literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::numeric_literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


::x3_test::dataset_loader literal_dataset{ "test/literal" };

BOOST_DATA_TEST_CASE(literal,
      literal_dataset.input()
    ^ literal_dataset.expect()
    ^ literal_dataset.test_file_name(),
    input, expect, file)
{
    using x3_test::testing_parser;

    typedef ast::literal attribute_type;

    // avoid warning, used in case of error for error message by boost.test
    boost::ignore_unused(file);

    bool parse_ok{ false };
    std::string parse_result {};

    testing_parser<attribute_type> parse;
    std::tie(parse_ok, parse_result) =  parse(input, parser::literal);

    BOOST_TEST(parse_ok);
    BOOST_TEST_INFO("parsed attr (result) = '" << parse_result << "'");
    BOOST_TEST(parse_result == expect, btt::per_element());
}


BOOST_AUTO_TEST_SUITE_END()

